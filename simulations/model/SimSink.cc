//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include <omnetpp.h>

using namespace omnetpp;

class SimSink : public cSimpleModule
{

  protected:
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(SimSink);

void SimSink::handleMessage(cMessage *msg)
{

    delete msg;
}



