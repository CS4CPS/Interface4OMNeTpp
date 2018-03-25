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
#include "SDH_Packet_m.h"

using namespace omnetpp;

/**
 * Point-to-point interface module. While one frame is transmitted,
 * additional frames get queued up; see NED file for more info.
 */
class SDH_Queue : public L2Queue
{
private:
  double ProcessDelay;
  double ThroughDelay;
  int divisionline;

protected:
  virtual void initialize() override;
  virtual cMessage *UnPackMessage(cMessage *msg) override;

};

Define_Module(SDH_Queue);

void SDH_Queue::initialize()
{
    //std::cout << " 11 " << getParentModule()->getFullPath() << endl;
    //std::cout << " 22 " << getParentModule()->par("ProcessDelay").doubleValue() << endl;

    ProcessDelay = getParentModule()->par("ProcessDelay").doubleValue();
    ThroughDelay = getParentModule()->par("ThroughDelay").doubleValue();

    //std::cout << " elecportNum: " << getParentModule()->gateSize("elecport") << endl;
    //std::cout << " optiportNum: " << getParentModule()->gateSize("optiport") << endl;
    divisionline = getParentModule()->gateSize("elecport");

    L2Queue::initialize();
}

cMessage *SDH_Queue::UnPackMessage(cMessage *msg)
{
    SDH_Packet *sdhp = check_and_cast<SDH_Packet *>(msg);
    int inid = sdhp->getInType();
    int outid = this->getIndex();
    if((inid >= divisionline) && (outid >= divisionline))
    {
        setDelay(ThroughDelay);
    }else
    {
        setDelay(ProcessDelay);
    }

    return sdhp->decapsulate();
}
