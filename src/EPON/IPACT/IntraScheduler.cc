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

#include "IntraScheduler.h"

Define_Module(IntraScheduler);

IntraScheduler::IntraScheduler() {

}

IntraScheduler::~IntraScheduler() {

}

void IntraScheduler::initialize() {
    Scheduler::initialize();

    //parameters
    tStart = simTime();
    tWindow = 0;

    //components
    queue = check_and_cast<Queue*>(getParentModule()->getSubmodule("queue"));
}

void IntraScheduler::finish() {
    Scheduler::finish();
    delete queue;
}

void IntraScheduler::handleSelfMessage(cMessage* msg) {

    if(msg->getKind() == intpar("SendMPCP")) sendMPCP();
    delete msg;
}

void IntraScheduler::sendMPCP() {
    MPCPReport* report = new MPCPReport("report",intpar("MPCP"));
    report->setBitLength(intpar("bitlenMPCP"));
    report->setSRC(getLLID());
    report->setDST(getLLID());
    report->setRequiredBandwidth(queue->getBitLength());
    send(report,"txSplitter");
}

void IntraScheduler::handleMessageFromSplitter(cMessage* msg) {
    Frame* frame = check_and_cast<Frame*>(msg);
    std::cout << "[IntraScheduler" << getLLID() << "::handleMessageFromSplitter] frame.LLID=" << frame->getDST() << endl;
    if(frame->getDST() == getLLID())
    {
        if(frame->getKind() == intpar("MPCP"))
        {
            MPCPGate* gate = check_and_cast<MPCPGate*>(frame);
            handleGate(gate);
            delete gate;
        }else if(frame->getKind() == intpar("RTT"))
        {
            MPCPGate* gate = check_and_cast<MPCPGate*>(frame);
            handleGateFast(gate);
            delete gate;
        }else if(msg->getKind() > intpar("MPCP") && msg->getKind() < intpar("FramePriorities"))
            handleDataFromSplitter(frame);
        else
            delete frame;
    }
    else
        delete frame;
}

void IntraScheduler::handleMessageFromHost(cMessage* msg) {
    handleDataFromHost(check_and_cast<DataFrame*>(msg));
    sendDataUntil(tStart + tWindow);
}

void IntraScheduler::handleGateFast(MPCPGate* gate) {

    //update tStart and tWindow
    tStart = gate->getStartTime();
    tWindow = gate->getLength();

    MPCPReport* report = new MPCPReport("report",intpar("RTT"));
    report->setBitLength(intpar("bitlenMPCP"));
    report->setSRC(getLLID());
    report->setDST(getLLID());
    report->setRequiredBandwidth(queue->getBitLength());
    report->setStartTime(simTime());
    send(report,"txSplitter");
}

void IntraScheduler::handleGate(MPCPGate* gate) {

    //update tStart and tWindow
    tStart = gate->getStartTime();
    tWindow = gate->getLength();
    std::cout << " tStart " << tStart << " tWindow " << tWindow << " TEnd " << (tStart + tWindow) << endl;
    sendDataUntil(tStart + tWindow);
    scheduleAt(tStart + tWindow,new cMessage("SendReport",intpar("SendMPCP")));
}

void IntraScheduler::handleDataFromSplitter(Frame* data) {

    cMessage *msg = UnPackMessage(data);
    send(msg,"txHost");
}

void IntraScheduler::handleDataFromHost(Frame* data) {
    //std::cout << " DataLen " << data->getBitLength() << endl;
    queue->insert(data);
    std::cout << "IntraScheduler.queue.getLength " << queue->getLength() << "." << endl;
    //cPacket* qtmp  = queue->front();
    //if(qtmp == NULL)
    //    std::cout << " queue is empty." << endl;
    //else
    //    std::cout << " queueLen " << qtmp->getBitLength() << endl;
}

int IntraScheduler::getLLID() {
    return getParentModule()->par("LLID");
}

cPacket* IntraScheduler::getNextDataFrame() {
    return queue->front();
}

cPacket* IntraScheduler::popNextDataFrame() {
    return queue->pop();
}

