#include "SocketApp.h"
#include <omnetpp.h>

using namespace omnetpp;

#include "Packet_m.h"
#include "MinimalEnv.cc"
#include "SimApp.h"
#include "modelconfig.h"

/**
 * Emulates an empty omnetpp.ini, causing config options' default values
 * to be used.
 */
class EmptyConfig : public cConfiguration
{
  protected:
    class NullKeyValue : public KeyValue {
      public:
        virtual const char *getKey() const override {return nullptr;}
        virtual const char *getValue() const override {return nullptr;}
        virtual const char *getBaseDirectory() const override {return nullptr;}
    };
    NullKeyValue nullKeyValue;

  protected:
    virtual const char *substituteVariables(const char *value) override {return value;}

  public:
    virtual const char *getConfigValue(const char *key) const override {return nullptr;}
    virtual const KeyValue& getConfigEntry(const char *key) const override {return nullKeyValue;}
    virtual const char *getPerObjectConfigValue(const char *objectFullPath, const char *keySuffix) const override {return nullptr;}
    virtual const KeyValue& getPerObjectConfigEntry(const char *objectFullPath, const char *keySuffix) const override {return nullKeyValue;}
};

SimApp devSimApp;

void simulate(const char *networkName, simtime_t limit)
{
    // set up the network
    cModuleType *networkType = cModuleType::find(networkName);
    if (networkType == nullptr) {
        printf("No such network: %s\n", networkName);
        return;
    }
    getSimulation()->setupNetwork(networkType); //XXX may throw exception
    getSimulation()->setSimulationTimeLimit(limit);

    // prepare for running it
    getSimulation()->callInitialize();

    // run the simulation
    std::cout << "-----SIM RUN------------------" << endl;

    int pos = 0;
    for (cModule::SubmoduleIterator it(getSimulation()->getSystemModule ()); !it.end(); ++it)
    {
        cModule *submodp = it();
        int addr = submodp->par("IEDaddr");
        std::cout << "SubModule::" << submodp->getFullName() << "::" << addr << "::" << submodp->getId() << endl;

        for (cModule::SubmoduleIterator itsp(submodp); !itsp.end(); ++itsp)
        {
            cModule *simplemodp = itsp();
            std::cout << "SubModule::" << simplemodp->getFullName() << "::" << simplemodp->getId() << endl;

            std::string fname(simplemodp->getFullName());
            if(fname.compare("simapp")==0)
            {
                std::cout << "Found IED Module::" << fname << "::" << simplemodp->getId() << "::" << addr << endl;
                devSimApp.IEDname[pos] = fname;
                devSimApp.IEDmodule[pos] = simplemodp;
                devSimApp.IEDnumber[pos] = addr;
                pos++;
            }
        }
    }
    devSimApp.IEDcnt = pos;
    devSimApp.SetSimulation(getSimulation());

    /*
    Packet *msg = new Packet("ExternalEvent");
    msg->setSrcAddr(20);
    msg->setDestAddr(22);
    msg->setLen(60);
    msg->setDataArraySize(60);
    for(int j=0;j<60;j++)
        msg->setData(j,j);

    cModule *cmp = devSimApp.findmodule(20);
    if(cmp != 0)
    {
        msg->setSentFrom(cmp, -1, simTime());
        msg->setArrival(cmp->getId(), -1, simTime());
        getSimulation()->insertEvent(msg);
    }*/

    int res;
    double evttime, nowtime;
    bool ok = true;
    try {
        while (true) {
            //-------------------------------------------------------------
            res = devSimApp.server_rece();
            if(res<0)
                break;
            /*evttime = getSimulation()->guessNextSimtime().dbl();
            nowtime = simTime().dbl();
            //-------------------------------------------------------------
            cEvent *event = getSimulation()->takeNextEvent();
            if (!event)
                break;  //XXX
            getSimulation()->executeEvent(event);
            //-------------------------------------------------------------
            if(evttime != nowtime)
            {
                //std::cout << "-----------------------" << endl;
                std::cout << "Current sim time::" << nowtime << endl;
                std::cout << "-----------------------" << endl;
            }*/
            //-------------------------------------------------------------
        }
    }
    catch (cTerminationException& e) {
        printf("Finished: %s\n", e.what());
    }
    catch (std::exception& e) {
        ok = false;
        printf("ERROR: %s\n", e.what());
    }

    if (ok)
        getSimulation()->callFinish();  //XXX may throw exception

    // finish the simulation and clean up the network
    getSimulation()->deleteNetwork();
}

ModelConfig devModelConfig;

int main(int argc, char *argv[])
{
    int res,rlen,slen;
    char rbuf[512],sbuf[512];

    std::cout << "OMNeT++ init." << endl;
    //init
    devModelConfig.config();
    devSimApp.init();

    // the following line MUST be at the top of main()
    cStaticFlag dummy;

    std::cout << "Initializations\n" << endl;
    CodeFragments::executeAll(CodeFragments::STARTUP);
    SimTime::setScaleExp(-12);

    std::cout << "set up an environment for the simulation\n" << endl;
    cEnvir *env = new MinimalEnv(argc, argv, new EmptyConfig());

    cSimulation *sim = new cSimulation("simulation", env);
    cSimulation::setActiveSimulation(sim);

    std::cout << "load NED files. Path= " << getcwd(NULL, NULL) << "\n" << endl;
    cSimulation::loadNedSourceFolder("src");
    cSimulation::doneLoadingNedFiles();

    std::cout << "set up and run a simulation model.\n" << endl;
    simulate("omnetcom.CoCoSim", 999999);

    std::cout << "exit.\n" << endl;
    cSimulation::setActiveSimulation(nullptr);
    delete sim;

    std::cout << "deallocate registration lists, loaded NED files, etc.\n" << endl;
    CodeFragments::executeAll(CodeFragments::SHUTDOWN);

    return 0;
}
