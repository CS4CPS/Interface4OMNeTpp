#include "Routing.h"

Define_Module(Routing);

void Routing::initialize()
{
    myAddress = getParentModule()->par("IEDaddr");

    dropSignal = registerSignal("drop");
    outputIfSignal = registerSignal("outputIf");

    //
    // Brute force approach -- every node does topology discovery on its own,
    // and finds routes to all other nodes independently, at the beginning
    // of the simulation. This could be improved: (1) central routing database,
    // (2) on-demand route calculation
    //
    cTopology *topo = new cTopology("topo");

    //std::vector<std::string> nedTypes;
    //nedTypes.push_back(getParentModule()->getNedTypeName());
    //topo->extractByNedTypeName(nedTypes);
    topo->extractByParameter("IncludeInTopo");
    std::cout << myAddress << " cTopology found " << topo->getNumNodes() << " nodes\n";

    cTopology::Node *thisNode = topo->getNodeFor(getParentModule());

    // find and store next hops
    for (int i = 0; i < topo->getNumNodes(); i++) {
        if (topo->getNode(i) == thisNode)
            continue;  // skip ourselves
        topo->calculateUnweightedSingleShortestPathsTo(topo->getNode(i));

        if (thisNode->getNumPaths() == 0)
            continue;  // not connected

        cGate *parentModuleGate = thisNode->getPath(0)->getLocalGate();
        int gateIndex = parentModuleGate->getPathStartGate()->getOwnerModule()->getIndex();
        int address = topo->getNode(i)->getModule()->par("IEDaddr");
        rtable[address] = gateIndex;
        std::cout << "  address " << address
                  << " gateName " << parentModuleGate->getPathStartGate()->getOwnerModule()->getFullPath()
                  << " gateIndex " << gateIndex
                  << " with " << thisNode->getDistanceToTarget() << "hops."
                  << endl;
    }
    delete topo;
}

void Routing::handleMessage(cMessage *msg)
{
    Packet *pk = check_and_cast<Packet *>(msg);
    int destAddr = pk->getDestAddr();

    if (destAddr == myAddress) {
        std::cout << "Routing" << myAddress << "::" << "local delivery of packet " << pk->getName() << endl;
        send(pk, "localOut");
        emit(outputIfSignal, -1);  // -1: local
        return;
    }

    RoutingTable::iterator it = rtable.find(destAddr);
    if (it == rtable.end()) {
        std::cout << "Routing" << myAddress << "::" << "address " << destAddr << " unreachable, discarding packet " << pk->getName() << endl;
        emit(dropSignal, (long)pk->getByteLength());
        delete pk;
        return;
    }

    int outGateIndex = (*it).second;
    std::cout << "Routing" << myAddress << "::" << "forwarding packet " << pk->getName() << " on gate index " << outGateIndex << endl;
    pk->setHopCount(pk->getHopCount()+1);
    emit(outputIfSignal, outGateIndex);

    cMessage *msgp = PackMessage((cMessage*)pk);
    send(msgp, "out", outGateIndex);

}

cMessage *Routing::PackMessage(cMessage *msg)
{
    return msg;
}

