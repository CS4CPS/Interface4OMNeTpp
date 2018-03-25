
package omnetcom.simulations;

import ned.DatarateChannel;
import omnetcom.Common.*;
import omnetcom.SDH.*;
import omnetcom.EPON.*;
import omnetcom.Host.*;
import omnetcom.simulations.model.*;

network CoSim
{
    parameters:
        //scheduler events
        int SendUntil = default(0);
        int SendMPCP = default(1);
        int CheckMPCP = default(2);
        int WakeUp = default(3);
        int StartSend = default(4);
        int StartSleep = default(5);
        int Forward = default(6);
        int Interrupt = default(7);

        //frame priorities including MPCP
        int FramePriorities = default(4);
        int MPCP = default(0);
        int EF = default(1);
        int AF = default(2);
        int BE = default(3);
        int RTT = default(4);

		//parameters
        //int numONUs = 3;

        double tCycle @unit(s) = 0.001s;
        double tGuard @unit(s) = 0.000001s;
        int MPCPSize @unit(b) = 512b;

        @display("bgb=1600,800");
    types:
        channel Fiber155M extends DatarateChannel
        {
            double length = default(0.1);
            double speed @unit(s) = 0.000005s;
            delay = length * speed;
            datarate = 155.52Mbps;
        }
        channel Fiber1G extends ned.DatarateChannel
        {
            double length = default(5);
            double speed @unit(s) = 0.000005s;
            delay = length * speed;
            datarate = 1Gbps;
        }
        channel Cable extends ned.DatarateChannel
        {
            delay = 0;
            datarate = 100Mbps;
        }
    submodules:
        server: IED {
            IEDaddr = 20;
            @display("i=device/server;is=l;p=61.18,345.80002");
        }
        //------------------------------------------------------------------
        olt1: OLT {
            IEDaddr = 102;
            LLID = 4;
            LLID_BASE = 21;
            numONUs = 4;
            @display("p=139.65,242.06");
        }
        splitter00: Splitter {
            IEDaddr = 210;
            numONUs = 2;
            @display("p=227.43001,242.06");
        }
        onu00: ONU {
            IEDaddr = 211;
            LLID = 21;
            @display("p=227.43001,167.58");
        }
        Tm800: IED {
            IEDaddr = 21;
            @display("i=device/cpu;p=227.43001,103.74");
        }
        splitter02: Splitter {
            IEDaddr = 220;
            numONUs = 2;
            @display("p=312.55,242.06");
        }
        onu02: ONU {
            IEDaddr = 221;
            LLID = 22;
            @display("p=312.55,167.58");
        }
        Tm802: IED {
            IEDaddr = 22;
            @display("i=device/cpu;p=312.55,103.74");
        }
        splitter06: Splitter {
            IEDaddr = 230;
            numONUs = 2;
            @display("p=399,242.06");
        }
        onu06: ONU {
            IEDaddr = 231;
            LLID = 23;
            @display("p=399,167.58");
        }
        Tm806: IED {
            IEDaddr = 23;
            @display("i=device/cpu;p=399,103.74");
        }
        splitter08: Splitter {
            IEDaddr = 240;
            numONUs = 1;
            @display("p=482.79,242.06");
        }
        onu08: ONU {
            IEDaddr = 241;
            LLID = 24;
            @display("p=482.79,167.58");
        }
        Tm808: IED {
            IEDaddr = 24;
            @display("i=device/cpu;p=482.79,103.74");
        }
    connections:
        server.port <--> Cable <--> olt1.Host;
        olt1.Splitter <--> Fiber1G {  length = 0.1; } <--> splitter00.OLT;
        splitter00.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu00.Splitter;
        onu00.Host <--> Cable <--> Tm800.port;

        splitter00.ONU++ <--> Fiber1G {  length = 0.8; } <--> splitter02.OLT;
        splitter02.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu02.Splitter;
        onu02.Host <--> Cable <--> Tm802.port;

        splitter02.ONU++ <--> Fiber1G {  length = 0.5; } <--> splitter06.OLT;
        splitter06.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu06.Splitter;
        onu06.Host <--> Cable <--> Tm806.port;

        splitter06.ONU++ <--> Fiber1G {  length = 9.8; } <--> splitter08.OLT;
        splitter08.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu08.Splitter;
        onu08.Host <--> Cable <--> Tm808.port;
}


