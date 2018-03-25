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
#include "L2Queue.h"

using namespace omnetpp;

/**
 * Point-to-point interface module. While one frame is transmitted,
 * additional frames get queued up; see NED file for more info.
 */
class EPON_Queue : public L2Queue
{
private:
  double ProcessDelay;

protected:
  virtual void initialize() override;
  virtual cMessage *UnPackMessage(cMessage *msg) override;

};

Define_Module(EPON_Queue);

void EPON_Queue::initialize()
{
    ProcessDelay = getParentModule()->par("ProcessDelay").doubleValue();

    L2Queue::initialize();
}

cMessage *EPON_Queue::UnPackMessage(cMessage *msg)
{
    setDelay(ProcessDelay);

    return msg;
}
