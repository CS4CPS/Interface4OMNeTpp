
#include <omnetpp.h>

using namespace omnetpp;

#include "Packet_m.h"

class App : public cSimpleModule
{
  private:
    int myAddress;
    int bitlenPacket;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(App);

void App::initialize()
{
    //myAddress = par("APPaddr").longValue();
    myAddress = getParentModule()->par("IEDaddr");
    bitlenPacket = 16;
}

void App::handleMessage(cMessage *msg)
{
    Packet *ttmsg = check_and_cast<Packet *>(msg);

    std::cout << "App" << myAddress << "::" << "Message " << ttmsg << " arrived after " << ttmsg->getHopCount() << " hops."<< endl;

    std::string fname(ttmsg->getName());
    if(fname.compare("ExternalEvent")==0)
    {
        if(ttmsg->getDestAddr() != myAddress)
        {
            //char msgname[20];
            std::cout << "App" << myAddress << ":: " << fname << " SimEvent-" << ttmsg->getSrcAddr() << "-to-"<< ttmsg->getDestAddr() << endl;

            Packet *simmsg = new Packet("ExternalEvent");
            simmsg->setSrcAddr(ttmsg->getSrcAddr());
            simmsg->setDestAddr(ttmsg->getDestAddr());
            int datalen = ttmsg->getLen();
            simmsg->setLen(datalen);
            simmsg->setDataArraySize(datalen);
            for(int j=0;j<datalen;j++)
                simmsg->setData(j,ttmsg->getData(j));
            simmsg->setBitLength(datalen*8+bitlenPacket);

            send(simmsg, "out");
            std::cout << "App" << myAddress << "::" << simmsg->getName() << " arrive at " << simmsg->getArrivalTime() << "."<< endl;
            delete msg;
        }else
        {
            std::cout << "App" << myAddress << ":: " << fname << " CompletedEvent-" << ttmsg->getSrcAddr() << "-to-"<< ttmsg->getDestAddr() << endl;
            Packet *finmsg = new Packet("CompletedEvent");
            finmsg->setSrcAddr(ttmsg->getSrcAddr());
            finmsg->setDestAddr(ttmsg->getDestAddr());
            int datalen = ttmsg->getLen();
            finmsg->setLen(datalen);
            finmsg->setDataArraySize(datalen);
            for(int j=0;j<datalen;j++)
                finmsg->setData(j,ttmsg->getData(j));

            send(finmsg, "tp");
            delete msg;
        }
    }else
        delete msg;
}


