#ifndef SIMAPP_SIMAPP_H_
#define SIMAPP_SIMAPP_H_

#include <omnetpp.h>
#include "SocketApp.h"
#include "drv_sstp.h"
#include "sstp_def.h"
#include "../src/Common/Packet_m.h"

using namespace omnetpp;

typedef struct
{
    int msgsor;
    int msgdes;
    int msgdatalen;
    char msgdata[512];
}SimIEDData;

class SimApp {
public:
    SimApp();
    virtual ~SimApp();

    int init(void);
    int server_rece(void);
    int32 response(drv_sstp_head shead, uint8 *inbuf, uint8 *outbuf);
    void SetSimulation(cSimulation* csim);

    SocketApp tcpserver;
    drv_sstp inst_sstp;
    cSimulation* devSim;

    int IEDcnt;
    cModule *IEDmodule[128];
    int IEDnumber[128];
    std::string IEDname[128];

    SimTime GT_time;
    int GT_timei;
    SimIEDData devSIEDD[128];
    int devSIEDDcnt;

    int32 cosim_next(drv_sstp_head shead, uint32 *datapl, uint8 *inbuf, uint8 *outbuf);
    int32 cosim_step(drv_sstp_head shead, uint32 *datapl, uint8 *inbuf, uint8 *outbuf);
    int32 cosim_process(drv_sstp_head shead, uint32 *datapl, uint8 *inbuf, uint8 *outbuf);
    int32 cosim_rdata(drv_sstp_head shead, uint32 *datapl, uint8 *inbuf, uint8 *outbuf);
    int32 cosim_wdata(drv_sstp_head shead, uint32 *datapl, uint8 *inbuf, uint8 *outbuf);

    void eventprocess(void);
    void addmsg(cEvent *event);
    cModule* findmodule(int number);
};

#endif /* SIMAPP_SIMAPP_H_ */
