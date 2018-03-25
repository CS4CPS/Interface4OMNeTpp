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

#include "InterScheduler.h"

Define_Module(InterScheduler);

InterScheduler::InterScheduler() {

}

InterScheduler::~InterScheduler() {

}

void InterScheduler::initialize() {
    Scheduler::initialize();

    //parameters
    tAvailable = simTime();
    tMPCP = getTransmissionTime(intpar("bitlenMPCP"));
    tCycleStart = 0;
    tCycleRemain = 0;
    tStart.assign(intpar("numONUs"),simTime());
    tWindow.assign(intpar("numONUs"),0);
    tRequired.assign(intpar("numONUs"),0);
    RTT.assign(intpar("numONUs"), 2*timepar("tCycle")/intpar("numONUs"));
    Distance.assign(intpar("numONUs"),0);
    currentONU = 0;

    //components
    queue = check_and_cast<MultiQueue*>(getParentModule()->getSubmodule("queue"));

    //initial schedule
    for(int i = 0;i < intpar("numONUs");i++) bandwidthAlloc(i,0,0);
}

void InterScheduler::finish() {
    Scheduler::finish();

    delete queue;
}

void InterScheduler::handleSelfMessage(cMessage* msg) {
    //std::cerr << "OLT::handleSelfMessage t=" << simTime() << endl;

    if(msg->getKind() == intpar("SendMPCP"))
    {
        //Downstream transmission window start
        currentONU = int(msg->par("LLID"));
        sendMPCP(int(msg->par("LLID")));
        scheduled.pop_back();
        scheduleDownstream();
    }else
        delete msg;
}

void InterScheduler::sendMPCP(int LLID) {

    MPCPGate* gate = new MPCPGate("gate");
    gate->setDST(LLID+intpar("LLID_BASE"));
    gate->setBitLength(intpar("bitlenMPCP"));
    gate->setStartTime(tStart[LLID]);
    gate->setLength(tWindow[LLID]);
    if(Distance[LLID] == 0)
        gate->setKind(intpar("RTT"));
    send(gate,"txSplitter");
}

void InterScheduler::scheduleDownstream() {
    switch(intpar("downstreamScheduling"))
    {
    case FIFO:
        if(scheduled.size() > 0)
            sendDataUntil(tStart[scheduled.back()] - tMPCP - RTT[scheduled.back()] / 2);
        else
            sendDataUntil(tAvailable - tMPCP - timepar("tProp") * 2);
        break;
    case TDM:
        //std::cout << " tstart " << tStart[currentONU]
        //          << " twindow " << tWindow[currentONU]
        //          << " tguard " << timepar("tGuard")
        //          << " RTT " << (RTT[currentONU] / 2)
        //          << "\n";
        simtime_t tg = timepar("tGuard");
        sendDataUntil(tStart[currentONU] + tWindow[currentONU] + tg - RTT[currentONU] / 2);
        break;
    }
}

void InterScheduler::handleMessageFromSplitter(cMessage* msg) {
    Frame* frame = check_and_cast<Frame*>(msg);
    if(frame->getKind() == intpar("MPCP"))
    {
        handleMPCP(msg);
        delete msg;
    }else if(frame->getKind() == intpar("RTT"))
    {
        MPCPReport* report = check_and_cast<MPCPReport*>(msg);
        simtime_t R = report->getStartTime();
        R = (simTime() - R - tMPCP)*2;
        int src = report->getSRC() - intpar("LLID_BASE");
        RTT[src] = R;
        Distance[src] = 1;
        std::cout << " Distance[" << src << "]= " << R << ".\n";
        handleMPCP(msg);
        delete msg;
    }else if(msg->getKind() > intpar("MPCP") && msg->getKind() < intpar("FramePriorities"))
    {
        cMessage *msgp = UnPackMessage(frame);
        send(msgp,"txHost");
    }else
        delete frame;
}

void InterScheduler::handleMPCP(cMessage* msg) {
    MPCPReport* report = check_and_cast<MPCPReport*>(msg);
    int src = report->getSRC() - intpar("LLID_BASE");
    int gb = report->getRequiredBandwidth();
    int gbl = queue->getBitLength(src);
    bandwidthAlloc(src, gb, gbl);
}

void InterScheduler::handleMessageFromHost(cMessage* msg) {
    cPacket *cp = check_and_cast<cPacket*>(msg);
    queue->insert(cp);
    scheduleDownstream();
}

void InterScheduler::bandwidthAlloc(int LLID,int upRequiredBitlength,int downRequiredBitlength) {
    //time point of cycle start
    //for elastic service to count remain bandwidth in this cycle

    if(LLID == 0)
    {
        tCycleStart = simTime();
        tCycleRemain = timepar("tCycle");
    }

    //required bandwidth
    tRequired[LLID] = getTransmissionTime(upRequiredBitlength);
    simtime_t tDownRequired = getTransmissionTime(downRequiredBitlength);
    if(intpar("downstreamScheduling") == TDM)
        tRequired[LLID] = std::max(tDownRequired,tRequired[LLID]);

    //update tStart and tWindow
    simtime_t tNextAvailable = simTime() + RTT[LLID] + tMPCP;
    if(tAvailable < tNextAvailable)
        tAvailable = tNextAvailable;
    tStart[LLID] = tAvailable - RTT[LLID] / 2;

    //inter scheduling service
    simtime_t tCredit;
    switch(intpar("interScheduling"))
    {
    case FIXED:
        tWindow[LLID] = getOnlineMaxWindow();
        break;
    case GATED:
        tWindow[LLID] = tRequired[LLID];
        break;
    case LIMITED:
        tWindow[LLID] = tRequired[LLID] <= getOnlineMaxWindow() ? tRequired[LLID] : getOnlineMaxWindow();
        break;
    case CONSTANT:
        tCredit = tRequired[LLID] + getTransmissionTime(intpar("credit"));
        tWindow[LLID] = tCredit <= getOnlineMaxWindow() ? tCredit : getOnlineMaxWindow();
        break;
    case LINEAR:
        tCredit = tRequired[LLID] * (1 + dblpar("credit"));
        tWindow[LLID] = tCredit <= getOnlineMaxWindow() ? tCredit : getOnlineMaxWindow();
        break;
    case ELASTIC:
        tWindow[LLID] = tRequired[LLID] <= tCycleRemain ? tRequired[LLID] : tCycleRemain;
        tCycleRemain -= tWindow[LLID];
        break;
    }
    tAvailable += tWindow[LLID] + tMPCP + timepar("tGuard");

    //schedule to send gate
    cMessage* msg = new cMessage("SendGate",intpar("SendMPCP"));
    cMsgPar* par = new cMsgPar("LLID");
    par->setLongValue(LLID);
    msg->addPar(par);
    scheduleAt(tStart[LLID] - tMPCP - RTT[LLID] / 2,msg);
    scheduled.insert(scheduled.begin(),LLID);
/*
    std::cout << " OLT::LLID " << LLID
              << " OLTStart " << (tStart[LLID] - tMPCP - RTT[LLID] / 2)
              << " tStart " << tStart[LLID]
              << " tWindow " << tWindow[LLID]
              << " tRequired " << tRequired[LLID]
              << " tAvailable " << tAvailable
              << "\n";*/
}

bool InterScheduler::queueEmpty() {
    switch(intpar("downstreamScheduling"))
    {
        case FIFO:
            return Scheduler::queueEmpty();
            break;
        case TDM:
            return queue->isEmpty(currentONU);
            break;
    }
    throw cRuntimeError("[%s::getNextDataFrame] undefined downstream scheduling mode");
}

cPacket* InterScheduler::getNextDataFrame() {
    switch(intpar("downstreamScheduling"))
    {
        case FIFO:
            return getNextDataFrameFIFO();
            break;
        case TDM:
            return getNextDataFrameTDM();
            break;
    }
    throw cRuntimeError("[%s::getNextDataFrame] undefined downstream scheduling mode");
}

cPacket* InterScheduler::getNextDataFrameFIFO() {
    return Scheduler::getNextDataFrame();
}

cPacket* InterScheduler::getNextDataFrameTDM() {
    return queue->front(currentONU);
}

cPacket* InterScheduler::popNextDataFrame() {
    return queue->pop(currentONU);
}
