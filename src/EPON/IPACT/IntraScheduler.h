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

#ifndef INTRASCHEDULER_H_
#define INTRASCHEDULER_H_
#include <Scheduler.h>
#include <Queue.h>

class IntraScheduler : public Scheduler {
public:
    IntraScheduler();
    virtual ~IntraScheduler();

    virtual void initialize() override;
    virtual void finish() override;

    virtual void handleSelfMessage(cMessage* msg) override;
    virtual void sendMPCP();
    virtual void handleMessageFromSplitter(cMessage* msg) override;
    virtual void handleMessageFromHost(cMessage* msg) override;

    virtual void handleGateFast(MPCPGate* gate);
    virtual void handleGate(MPCPGate* gate);
    virtual void handleDataFromSplitter(Frame* data);
    virtual void handleDataFromHost(Frame* data);
    virtual cPacket* getNextDataFrame() override;
    virtual cPacket* popNextDataFrame() override;
    //query
    virtual int getLLID();
    //intra scheduling
    //enum IntraSchduling{STRICT,NONSTRICT};
protected:
    //parameter
    simtime_t tStart,tWindow;

    //components
    Queue* queue;
};

#endif /* INTRASCHEDULER_H_ */
