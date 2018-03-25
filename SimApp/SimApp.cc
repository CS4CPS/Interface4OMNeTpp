#include <SimApp.h>

SimApp::SimApp() {
}

SimApp::~SimApp() {
}

int SimApp::init(void)
{
    int res;

    res = tcpserver.sa_init("123", 123);
    if(res<0)
    {
        std::cout << "SA_init failed." << endl;
        return 0;
    }
    //sstp
    inst_sstp.init(DRV_SSTP_SLAYER, ID_POWERFACTORY);

    IEDcnt = 0;
    devSIEDDcnt = 0;

    return 0;
}

void SimApp::SetSimulation(cSimulation* csim)
{
    devSim = csim;
}

int SimApp::server_rece(void)
{
    int32 resrece,resprot,resdata,ressend;
    uint8 buf[512],sbuf[512];
    drv_sstp_head shead;

    resrece = tcpserver.sa_rece(0,buf,512);
    if(resrece > 0)
    {
        //std::cout << "Rece Data.." << resrece << endl;
        resprot = inst_sstp.resolve(buf,resrece);
        if(resprot > 0)
        {
            //std::cout << "Resolve OK.." << endl;
            resdata = response(inst_sstp.headbuf, inst_sstp.outbuf, buf);

            if(resdata > 0)
            {
                shead.des = inst_sstp.headbuf.sor;
                shead.sor = inst_sstp.headbuf.des;
                shead.type = inst_sstp.headbuf.type | 0x80;
                shead.flag = inst_sstp.headbuf.flag;
                shead.len = resdata;

                ressend = inst_sstp.fill(sbuf, &shead, buf);
                if(ressend > 0)
                {
                    tcpserver.sa_send(0,sbuf,ressend);
                }
            }
        }else
            std::cout << "Resolve ERR.." << endl;
        return 0;
    }else if(resrece < 0)
    {
        return -1;
    }else
        return 0;
}

int32 SimApp::response(drv_sstp_head shead, uint8 *inbuf, uint8 *outbuf)
{
    uint8 *data;
    uint32 datapl[4];
    int32 res,i;
    uint32 blk,para[4],len;

    data = &inbuf[DRV_SSTP_IDXDL];
    for(i=0;i<4;i++)
        datapl[i] = (inbuf[i*4+3]<<24) | (inbuf[i*4+2]<<16) | (inbuf[i*4+1]<<8) | (inbuf[i*4+0]);
    res = -1;

    uint32 *cmdp = (uint32*)outbuf;

    std::cout << "cosim_Time:: --- " << simTime() << " ---" << endl;
    switch(shead.type)
    {
        case DRV_SSTP_CMD_CSET:
            switch(datapl[SQUEUE_DEF_CMD_POS])
            {
            case SSTP_DEF_CMD_INIT:
                cmdp[SQUEUE_DEF_CMD_POS] = datapl[SQUEUE_DEF_CMD_POS];
                cmdp[1] = 0;
                cmdp[2] = 0;
                cmdp[DRV_SSTP_RSP_POS] = DRV_SSTP_RSP_OK;
                res = DRV_SSTP_IDXDL;
                break;
            case SSTP_DEF_CMD_RST:
                cmdp[SQUEUE_DEF_CMD_POS] = datapl[SQUEUE_DEF_CMD_POS];
                cmdp[1] = 0;
                cmdp[2] = 0;
                cmdp[DRV_SSTP_RSP_POS] = DRV_SSTP_RSP_OK;
                res = DRV_SSTP_IDXDL;
                break;
            case SSTP_DEF_PAR_NEXT:
                res = cosim_next(shead, datapl, inbuf, outbuf);
                break;
            case SSTP_DEF_PAR_STEP:
                res = cosim_step(shead, datapl, inbuf, outbuf);
                break;
            case SSTP_DEF_PAR_PROCESS:
                res = cosim_process(shead, datapl, inbuf, outbuf);
                break;
            default:
                cmdp[SQUEUE_DEF_CMD_POS] = datapl[SQUEUE_DEF_CMD_POS];
                outbuf[1] = 0;
                outbuf[2] = 0;
                outbuf[DRV_SSTP_RSP_POS] = DRV_SSTP_RSP_ERR;
                res = DRV_SSTP_IDXDL;
            }
            break;
        case DRV_SSTP_CMD_RDATA:
            res = cosim_rdata(shead, datapl, inbuf, outbuf);
            break;
        case DRV_SSTP_CMD_WDATA:
            res = cosim_wdata(shead, datapl, inbuf, outbuf);
            break;
    }
    return res;
}

int32 SimApp::cosim_next(drv_sstp_head shead, uint32 *datapl, uint8 *inbuf, uint8 *outbuf)
{
    std::cout << "cosim_next::-----------------" << endl;
    //cEvent *event = devSim->guessNextEvent();
    int evtlen = devSim->getFES()->getLength();
    cEvent *event;
    simtime_t evttime = 99;
    int trigger = 0;
    for(int i=0;i<evtlen;i++)
    {
        event = devSim->getFES()->get(i);
        //std::cout << " event " << i << " name: " << event->getFullName() << " time: " << event->getArrivalTime() << " simTime: " << simTime() << endl;

        std::string fname(event->getFullName());
        if(fname.compare("ExternalEvent")==0 || fname.compare("EPONHead")==0)
        {
            trigger = 1;
            simtime_t evttimet = event->getArrivalTime();
            if(evttime > evttimet)
                evttime = evttimet;
            //Packet *ttmsg = check_and_cast<Packet *>(event);
            //std::cout << " Found event " << i << endl;
            break;
        }
    }

    double evttimesim;
    if(trigger == 1)
    {
        //simtime_t evttime = devSim->guessNextSimtime();
        double evttimef = evttime.dbl();
        evttimesim = evttimef*10000;
        if(evttimesim>999999)
            evttimesim = 999999;

    }else
        evttimesim = 999999;

    int evtint = (int)evttimesim;
    //std::cout << "cosim_next_step::----- " << evttime << " -- " << evttimesim << " -- " << evtint << endl;
    if(devSIEDDcnt > 0)
    {
        evtint = GT_timei;
    }else
    {
        if(evtint <= GT_timei)
        evtint += 1;
    }

    uint32 *cmdp = (uint32*)outbuf;
    cmdp[SQUEUE_DEF_CMD_POS] = datapl[SQUEUE_DEF_CMD_POS];
    cmdp[1] = 0;
    cmdp[2] = evtint;
    cmdp[DRV_SSTP_RSP_POS] = DRV_SSTP_RSP_OK;
    return DRV_SSTP_IDXDL;
}

int32 SimApp::cosim_step(drv_sstp_head shead, uint32 *datapl, uint8 *inbuf, uint8 *outbuf)
{
    uint32 *cmdp = (uint32*)outbuf;
    cmdp[SQUEUE_DEF_CMD_POS] = datapl[SQUEUE_DEF_CMD_POS];
    cmdp[1] = 0;
    cmdp[2] = 0;
    cmdp[DRV_SSTP_RSP_POS] = DRV_SSTP_RSP_OK;
    return DRV_SSTP_IDXDL;
}

int32 SimApp::cosim_process(drv_sstp_head shead, uint32 *datapl, uint8 *inbuf, uint8 *outbuf)
{
    std::cout << "cosim_process::-----------------" << endl;
    GT_timei = datapl[2];
    //double timef = datapl[2];
    //SimTime time_cref;
    //time_cref = timef/10000;
    //GT_time = time_cref;

    eventprocess();

    uint32 *cmdp = (uint32*)outbuf;
    cmdp[SQUEUE_DEF_CMD_POS] = datapl[SQUEUE_DEF_CMD_POS];
    cmdp[1] = 0;
    cmdp[2] = devSIEDDcnt;
    cmdp[DRV_SSTP_RSP_POS] = DRV_SSTP_RSP_OK;
    return DRV_SSTP_IDXDL;
}

int32 SimApp::cosim_rdata(drv_sstp_head shead, uint32 *datapl, uint8 *inbuf, uint8 *outbuf)
{
    std::cout << "cosim_rdata::-----------------" << endl;
    uint32 *cmdp = (uint32*)outbuf;
    int iedcnt = devSIEDDcnt - 1;
    int datalen = devSIEDD[iedcnt].msgdatalen;
    cmdp[0] = devSIEDD[iedcnt].msgsor;
    cmdp[1] = devSIEDD[iedcnt].msgdes;
    cmdp[2] = datalen;
    cmdp[3] = devSIEDDcnt;

    for(int i=0;i<datalen;i++)
        outbuf[16+i] = devSIEDD[iedcnt].msgdata[i];

    devSIEDDcnt--;

    return (DRV_SSTP_IDXDL+datalen);
}

int32 SimApp::cosim_wdata(drv_sstp_head shead, uint32 *datapl, uint8 *inbuf, uint8 *outbuf)
{
    std::cout << "cosim_wdata::-----------------" << endl;
    int sor = datapl[0];
    int des = datapl[1];
    int datalen = datapl[2];
    int msgtime = datapl[3];

    GT_timei = msgtime;
    double timef = msgtime;
    SimTime time_cref;
    time_cref = timef/10000;

    Packet *msg = new Packet("ExternalEvent");
    msg->setSrcAddr(sor);
    msg->setDestAddr(des);
    msg->setLen(datalen);
    msg->setDataArraySize(datalen);
    for(int j=0;j<datalen;j++)
        msg->setData(j,inbuf[16+j]);

    cModule *cmp = findmodule(sor);
    if(cmp != 0)
    {
        msg->setSentFrom(cmp, -1, time_cref);
        msg->setArrival(cmp->getId(), -1, time_cref);
        devSim->insertEvent(msg);
        std::cout << "SimSys  ::" << msg << " at " << GT_timei << endl;

        eventprocess();
    }else
    {
        std::cout << "SimSys  :: No module" << endl;
    }

    uint32 *cmdp = (uint32*)outbuf;
    cmdp[SQUEUE_DEF_CMD_POS] = datapl[SQUEUE_DEF_CMD_POS];
    cmdp[1] = 0;
    cmdp[2] = 0;
    cmdp[DRV_SSTP_RSP_POS] = DRV_SSTP_RSP_OK;

    return DRV_SSTP_IDXDL;
}

void SimApp::eventprocess(void)
{
    int evttimei, nowtimei;
    double evttimef, nowtimef;
    simtime_t evttime, nowtime;
    while(1)
    {
        evttime = devSim->guessNextSimtime();
        evttimef = evttime.dbl()*10000;
        evttimei = evttimef;
        nowtimef = simTime().dbl()*10000;
        nowtimei = simTime().dbl()*10000;
        //std::cout << "SimSys  ::" << GT_timei << "-" << evttimef << "(" << simTime() << ")" << endl;
        if(evttimef <= GT_timei)
        {
            cEvent *event = devSim->takeNextEvent();
            if (!event)
                break;  //XXX
            std::string fname(event->getName());
            if(fname.compare("CompletedEvent")==0)
                addmsg(event);
            devSim->executeEvent(event);
        }else
        {
            //std::cout << "SimSys  ::" << " End " << GT_timei << "-" << evttimef << "(" << simTime() << ")" << endl;
            break;
        }
    }
}

void SimApp::addmsg(cEvent *event)
{
    Packet *ttmsg = check_and_cast<Packet *>(event);
    devSIEDD[devSIEDDcnt].msgsor = ttmsg->getSrcAddr();
    devSIEDD[devSIEDDcnt].msgdes = ttmsg->getDestAddr();
    int datalen = ttmsg->getLen();
    devSIEDD[devSIEDDcnt].msgdatalen = datalen;
    for(int j=0;j<datalen;j++)
        devSIEDD[devSIEDDcnt].msgdata[j] = ttmsg->getData(j);
    devSIEDDcnt++;

    std::cout << "SimSys  :: AddMsg " << ttmsg->getSrcAddr() << "-" << ttmsg->getDestAddr() << ".(" << devSIEDDcnt << ")-" << simTime() << endl;
}

cModule* SimApp::findmodule(int number)
{
    for(int i=0;i<IEDcnt;i++)
    {
        if(IEDnumber[i] == number)
            return IEDmodule[i];
    }

    return 0;
}
