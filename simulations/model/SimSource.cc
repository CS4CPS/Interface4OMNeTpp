
#include <omnetpp.h>

using namespace omnetpp;

#include "Packet_m.h"

class SimSource : public cSimpleModule
{
  private:
    cMessage *sendMessageEvent;
    cChannel *txChannel;
    int myAddress;
    int DataDest;
    int DataCnt;
    int bitlenPacket;

  public:
    SimSource();
    virtual ~SimSource();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual Packet *generateMessage();
};

Define_Module(SimSource);

SimSource::SimSource()
{
    sendMessageEvent = nullptr;
}

SimSource::~SimSource()
{
    cancelAndDelete(sendMessageEvent);
}

void SimSource::initialize()
{
    sendMessageEvent = new cMessage("sendMessageEvent");
    txChannel = gate("out")->getTransmissionChannel();

    myAddress = getParentModule()->par("IEDaddr");
    DataDest = getParentModule()->par("DES");
    DataCnt = getParentModule()->par("DATALENBYTES");
    bitlenPacket = par("bitlenPacket");

    scheduleAt(simTime()+par("SendInterval").doubleValue(), sendMessageEvent);
}

void SimSource::handleMessage(cMessage *msg)
{
    std::cout << "Sorce::receive message:" << msg << "::" <<msg->getName() << "." << endl;
    if(msg == sendMessageEvent)
    {
        simtime_t txFinishTime = txChannel->getTransmissionFinishTime();
        std::cout << "txFinishTime:" << txFinishTime << "SimTime:" << simTime() << "." << endl;
        if(txFinishTime <= simTime())
        {
            Packet *newmsg = generateMessage();
            std::cout << "Sorce::Generating message:" << newmsg << endl;
            send(newmsg, "out");

            scheduleAt(simTime()+par("SendInterval").doubleValue(), sendMessageEvent);
        }else
        {
            scheduleAt(txFinishTime, sendMessageEvent);
        }


    }else
    {
        delete msg;
    }
}

Packet *SimSource::generateMessage()
{
    char msgname[20];
    sprintf(msgname, "msg-s-to-%d", DataDest);

    Packet *msg = new Packet(msgname);
    msg->setSrcAddr(myAddress);
    msg->setDestAddr(DataDest);
    msg->setDataArraySize(DataCnt);
    for(int i=0;i<DataCnt;i++)
        msg->setData(i,'a');
    msg->setLen(DataCnt);
    msg->setBitLength(DataCnt*8+bitlenPacket);

    return msg;
}
