//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Point-to-point interface module. While one frame is transmitted,
 * additional frames get queued up; see NED file for more info.
 */
class L2Queue : public cSimpleModule
{
  private:

    long frameCapacity;

    cQueue queue;
    cQueue delayqueue;
    cMessage *endTransmissionEvent;
    cMessage *TransmissionDelay;
    bool isBusy;

    simsignal_t qlenSignal;
    simsignal_t busySignal;
    simsignal_t queueingTimeSignal;
    simsignal_t dropSignal;
    simsignal_t txBytesSignal;
    simsignal_t rxBytesSignal;

    double delay;

  public:
    L2Queue();
    virtual ~L2Queue();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void startTransmitting(cMessage *msg);
    virtual cMessage *UnPackMessage(cMessage *msg);
    virtual double getDelay(){return delay;}
    virtual void setDelay(double s){delay=s;}
};
