//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include <cTDMPON.h>
#include "mpcp_m.h"
#include "../Common/Packet_m.h"

using namespace omnetpp;

class Scheduler : public cTDMPON
{
public:
    virtual void initialize() override;

    void handleMessage(cMessage* msg) override;
    virtual void handleSelfMessage(cMessage* msg);
    virtual void handleMessageFromSplitter(cMessage* msg);
    virtual void handleMessageFromHost(cMessage* msg);

    virtual void send(cMessage* msg,const char *gatename);
    virtual void sendDataUntil(simtime_t tUntil);

    virtual void handleDataBeforeSend(DataFrame* data);

    //query
    virtual simtime_t getTransmissionTime(int bitLength);
    virtual bool isTxSplitterBusy();
    virtual simtime_t getTxSplitterSchedTime();
    int getLLID();
    virtual cPacket* getNextDataFrame();
    virtual cPacket* popNextDataFrame();
    virtual bool queueEmpty();

    //set
    virtual void setRxTimeStamp(DataFrame* data);
    virtual void setTxTimeStamp(DataFrame* data,simtime_t txTimeStamp);
    virtual cMessage *PackMessage(cMessage *msg);
    virtual cMessage *UnPackMessage(cMessage *msg);
    //components
    cDatarateChannel* txSplitter;
protected:
    //parameters
    simtime_t tMPCP,tGuard,RTT;

    //components
    cMessage* msgSendUntil;
};

#endif /* SCHEDULER_H_ */
