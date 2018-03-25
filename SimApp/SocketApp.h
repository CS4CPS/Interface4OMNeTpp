#ifndef SIMAPP_SOCKETAPP_H_
#define SIMAPP_SOCKETAPP_H_

#include<iostream>
#include <winsock2.h>
//#include <omnetpp/platdep/sockets.h>
//#include <omnetpp/platdep/timeutil.h>
#include <omnetpp.h>
#include "sysconfig.h"

using namespace omnetpp;

class SocketApp {
public:
    SocketApp();
    virtual ~SocketApp();

    int32 sa_init(const char *ipv4, uint32 port);
    int32 sa_send(uint32 addr, uint8 *buf, uint32 len);
    int32 sa_rece(uint32 addr, uint8 *buf, uint32 len);

    int port;

    cModule *module;
    cMessage *notificationMsg;
    char *recvBuffer;
    int recvBufferSize;
    int *numBytesPtr;

    // state
    timeval baseTime;
    SOCKET listenerSocket;
    SOCKET connSocket;
};

#endif /* SIMAPP_SOCKETAPP_H_ */
