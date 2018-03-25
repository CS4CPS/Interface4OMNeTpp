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

class BaseChannel : public cDatarateChannel
{

  protected:
      virtual void initialize() override;
};

Register_Class(BaseChannel);

void BaseChannel::initialize()
{
    setDelay(par("length").doubleValue()*par("speed").doubleValue());

    cDatarateChannel::initialize();
}

