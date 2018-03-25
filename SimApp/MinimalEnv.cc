#include "SocketApp.h"
#include <omnetpp.h>

using namespace omnetpp;

#include "Packet_m.h"

/**
 * Defines a minimal environment for the simulation. Module parameters get
 * initialized to their default values (causing an error if there's no
 * default); module log messages (EV<<) get printed on the standard output;
 * calls to record results will be ignored.
 */
class MinimalEnv : public cNullEnvir
{
  public:
    typedef std::map<std::string, double> StringDoubleMap;
    StringDoubleMap scalarResults;
    std::string iaTime;
    int numHosts;

    // constructor
    MinimalEnv(int ac, char **av, cConfiguration *c) : cNullEnvir(ac, av, c) {}

    void setParameters(int numHosts, std::string iaTime)
    {
        this->iaTime = iaTime;
        this->numHosts = numHosts;
    }

    double getStatistic(std::string name)
    {
        return scalarResults[name];
    }

    // model parameters
    virtual void readParameter(cPar *par) override
    {
        if (par->containsValue())
            par->acceptDefault();
        else
            throw cRuntimeError("no value for parameter %s", par->getFullPath().c_str());
    }

    virtual void recordScalar(cComponent *component, const char *name, double value, opp_string_map *attributes = nullptr) override
    {
        // store all reported scalar results into a map for later use
        scalarResults[component->getFullPath()+"."+name] = value;
    }

    virtual void notifyLifecycleListeners(SimulationLifecycleEventType eventType, cObject *details) override
    {

        std::vector<cISimulationLifecycleListener *> copy = listeners;
        for (int i = 0; i < (int)copy.size(); i++) {
            try {
                copy[i]->lifecycleEvent(eventType, details);
            }
            catch (std::exception& e) {  // XXX perhaps we shouldn't hide the exception!!!! just re-throw? then all notifyLifecycleListeners() calls MUST be surrounded with try-catch!!!!
                // XXX const char *eventName = cISimulationLifecycleListener::getSimulationLifecycleEventName(eventType);
                // XXX printfmsg("Error in %s listener: %s", eventName, e.what());
                //displayException(e);
                cRuntimeError("no value for parameter.");
            }
        }
    }

    // dump any scalar result gathered by the simulation model
    void dumpResults()
    {
        if (!scalarResults.empty()) {
            ::printf("Scalar statistics:\n");
            for (StringDoubleMap::const_iterator it = scalarResults.begin(); it != scalarResults.end(); ++it)
                ::printf("  %s: %lf\n", it->first.c_str(), it->second);
        }
    }

};
