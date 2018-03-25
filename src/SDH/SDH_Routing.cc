//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <map>
#include <omnetpp.h>
#include "Packet_m.h"
#include "Routing.h"
#include "SDH_Packet_m.h"

using namespace omnetpp;

class SDH_Routing : public Routing
{
private:
    int divisionline;

protected:
    virtual void initialize() override;
    virtual cMessage *PackMessage(cMessage *msg) override;

};

Define_Module(SDH_Routing);

void SDH_Routing::initialize()
{
    divisionline = getParentModule()->gateSize("elecport");

    Routing::initialize();
}

cMessage *SDH_Routing::PackMessage(cMessage *msg)
{
    Packet *pk = check_and_cast<Packet *>(msg);
    SDH_Packet *sdhp = new SDH_Packet("SDHHead");
    sdhp->encapsulate(pk);
    int gateid = pk->getArrivalGate()->getIndex();
    sdhp->setInType(gateid);

    std::cout << getmyAddress() << " Pack: " << gateid << " :: " << sdhp->getInType() << endl;

    return sdhp;
}
