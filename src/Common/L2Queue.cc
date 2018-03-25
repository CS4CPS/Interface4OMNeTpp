#include "L2Queue.h"

Define_Module(L2Queue);

L2Queue::L2Queue()
{
    endTransmissionEvent = nullptr;
    TransmissionDelay = nullptr;
}

L2Queue::~L2Queue()
{
    cancelAndDelete(endTransmissionEvent);
    cancelAndDelete(TransmissionDelay);
}

void L2Queue::initialize()
{
    queue.setName("queue");
    delayqueue.setName("delayqueue");

    endTransmissionEvent = new cMessage("endTxEvent");
    TransmissionDelay = new cMessage("TransmissionDelay");

    frameCapacity = par("frameCapacity");

    qlenSignal = registerSignal("qlen");
    busySignal = registerSignal("busy");
    queueingTimeSignal = registerSignal("queueingTime");
    dropSignal = registerSignal("drop");
    txBytesSignal = registerSignal("txBytes");
    rxBytesSignal = registerSignal("rxBytes");

    emit(qlenSignal, queue.getLength());
    emit(busySignal, false);
    isBusy = false;

    delay = 0;
}

void L2Queue::startTransmitting(cMessage *msg)
{
    std::cout << "Starting transmission of " << msg << endl;
    std::cout << " TimeNow: " << simTime() << " delay: " << delay << endl;
    isBusy = true;
    int64_t numBytes = check_and_cast<cPacket *>(msg)->getByteLength();
    //sendDelayed(msg, delay, "out");
    send(msg, "out");

    emit(txBytesSignal, (long)numBytes);

    // Schedule an event for the time when last bit will leave the gate.
    simtime_t endTransmission = gate("out")->getTransmissionChannel()->getTransmissionFinishTime();
    //endTransmission += delay;
    scheduleAt(endTransmission, endTransmissionEvent);
}

void L2Queue::handleMessage(cMessage *msg)
{
    cMessage *msgp;
    if(msg->arrivedOn("in"))
    {
        msgp = UnPackMessage(msg);
    }else
    {
        msgp = msg;
    }

    if (strcmp(msgp->getName(), "TransmissionDelay")==0)
    {
        delete msgp;
        msgp = (cMessage *)delayqueue.pop();
        simtime_t endTransmission = gate("out")->getTransmissionChannel()->getTransmissionFinishTime();
        std::cout << " TimeNow: " << simTime() << " TimeFin: " << endTransmission << endl;
        if (endTransmissionEvent->isScheduled()) {
            // We are currently busy, so just queue up the packet.
            if (frameCapacity && queue.getLength() >= frameCapacity) {
                std::cout << "Received " << msgp << " but transmitter busy and queue full: discarding\n" << endl;
                emit(dropSignal, (long)check_and_cast<cPacket *>(msgp)->getByteLength());
                delete msgp;
            }
            else {
                std::cout << "Received " << msgp << " but transmitter busy: queueing up\n" << endl;
                msgp->setTimestamp();
                queue.insert(msgp);
                int myAddress = getParentModule()->par("IEDaddr");
                std::cout << myAddress << "::L2Queue.queue.getLength " << queue.getLength() << "." << endl;
                emit(qlenSignal, queue.getLength());
            }
        }else
        {
            // We are idle, so we can start transmitting right away.
            std::cout << "Received " << msgp << endl;
            emit(queueingTimeSignal, SIMTIME_ZERO);
            startTransmitting(msgp);
            emit(busySignal, true);
        }
    }else if (msgp == endTransmissionEvent)
    {
        // Transmission finished, we can start next one.
        std::cout << "Transmission finished.\n" << endl;
        isBusy = false;
        if (queue.isEmpty()) {
            emit(busySignal, false);
        }
        else {
            msgp = (cMessage *)queue.pop();
            emit(queueingTimeSignal, simTime() - msgp->getTimestamp());
            emit(qlenSignal, queue.getLength());
            startTransmitting(msgp);
        }
    }else
    {  // arrived on gate "in"
        std::cout << "Received " << msgp << " and save in delayqueue.\n" << endl;
        //msgp->setTimestamp();
        delayqueue.insert(msgp);
        //int myAddress = getParentModule()->par("IEDaddr");
        //std::cout << myAddress << "::L2Queue.queue.getLength " << queue.getLength() << "." << endl;
        //emit(qlenSignal, queue.getLength());
        cMessage *msgdelay = new cMessage("TransmissionDelay");
        scheduleAt(simTime()+delay, msgdelay);
    }
}

cMessage *L2Queue::UnPackMessage(cMessage *msg)
{
    return msg;
}
