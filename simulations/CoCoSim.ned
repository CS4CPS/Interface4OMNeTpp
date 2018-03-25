
package omnetcom.simulations;

import ned.DatarateChannel;
import omnetcom.Common.*;
import omnetcom.SDH.*;
import omnetcom.EPON.*;
import omnetcom.Host.*;

network CoCoSim
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
        int numONUs = 3;

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
        ADM1: SDH_ADM {
            IEDaddr = 100;
            ProcessDelay = 0.00017;
            ThroughDelay = 0.0001;
            @display("p=138.32,345.80002;is=l");
        }
        ADM2: SDH_ADM {
            IEDaddr = 101;
            ProcessDelay = 0.00017;
            ThroughDelay = 0.0001;
            @display("p=856.52,429.59;is=l");
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
        //------------------------------------------------------------------        
        olt2: OLT {
            IEDaddr = 103;
            LLID = 6;
            LLID_BASE = 25;
            numONUs = 6;
            @display("p=953.61,530.67");
        }
        splitter14: Splitter {
            IEDaddr = 250;
            numONUs = 1;
            @display("p=591.85,242.06");
        }
        onu14: ONU {
            IEDaddr = 251;
            LLID = 25;
            @display("p=591.85,167.58");
        }
        Tm814: IED {
            IEDaddr = 25;
            @display("i=device/cpu;p=591.85,103.74");
        }
        splitter16: Splitter {
            IEDaddr = 260;
            numONUs = 2;
            @display("p=686.28,242.06");
        }
        onu16: ONU {
            IEDaddr = 261;
            LLID = 26;
            @display("p=686.28,167.58");
        }
        Tm816: IED {
            IEDaddr = 26;
            @display("i=device/cpu;p=686.28,103.74");
        }
        splitter24: Splitter {
            IEDaddr = 270;
            numONUs = 2;
            @display("p=775.39,242.06");
        }
        onu24: ONU {
            IEDaddr = 271;
            LLID = 27;
            @display("p=775.39,167.58");
        }
        Tm824: IED {
            IEDaddr = 27;
            @display("i=device/cpu;p=775.39,103.74");
        }
        splitter28: Splitter {
            IEDaddr = 280;
            numONUs = 2;
            @display("p=775.39,610.47003");
        }
        onu28: ONU {
            IEDaddr = 281;
            LLID = 28;
            @display("p=686.28,609.14");
        }
        Tm828: IED {
            IEDaddr = 28;
            @display("i=device/cpu;p=591.85,609.14");
        }
        splitter30: Splitter {
            IEDaddr = 290;
            numONUs = 2;
            @display("p=903.07,610.47003");
        }
        onu30: ONU {
            IEDaddr = 291;
            LLID = 29;
            @display("p=903.07,708.89");
        }
        Tm830: IED {
            IEDaddr = 29;
            @display("i=device/cpu;p=1046.71,708.89");
        }
        splitter54: Splitter {
            IEDaddr = 300;
            numONUs = 2;
            @display("p=1046.71,610.47003");
        }
        onu54: ONU {
            IEDaddr = 301;
            LLID = 30;
            @display("p=1153.11,609.14");
        }
        Tm854: IED {
            IEDaddr = 30;
            @display("i=device/cpu;p=1247.54,609.14");
        }
        //------------------------------------------------------------------
        olt3: OLT {
            IEDaddr = 104;
            LLID = 9;
            LLID_BASE = 31;
            numONUs = 9;
            @display("p=953.61,429.59");
        }
        splitter52: Splitter {
            IEDaddr = 310;
            numONUs = 2;
            @display("p=1046.71,429.59");
        }
        onu52: ONU {
            IEDaddr = 311;
            LLID = 31;
            @display("p=1153.11,509.39");
        }
        Tm852: IED {
            IEDaddr = 31;
            @display("i=device/cpu;p=1247.54,509.39");
        }
        splitter32: Splitter {
            IEDaddr = 320;
            numONUs = 2;
            @display("p=1046.71,333.83002");
        }
        onu32: ONU {
            IEDaddr = 321;
            LLID = 32;
            @display("p=953.61,240.73");
        }
        Tm832: IED {
            IEDaddr = 32;
            @display("i=device/cpu;p=953.61,158.27");
        }
        splitter58: Splitter {
            IEDaddr = 330;
            numONUs = 2;
            @display("p=1046.71,242.06");
        }
        onu58: ONU {
            IEDaddr = 331;
            LLID = 33;
            @display("p=1046.71,158.27");
        }
        Tm858: IED {
            IEDaddr = 33;
            @display("i=device/cpu;p=1046.71,67.83");
        }
        splitter34: Splitter {
            IEDaddr = 340;
            numONUs = 3;
            @display("p=1153.11,242.06");
        }
        onu34: ONU {
            IEDaddr = 341;
            LLID = 34;
            @display("p=1153.11,332.5");
        }
        Tm834: IED {
            IEDaddr = 34;
            @display("i=device/cpu;p=1153.11,404.32");
        }
        splitter60: Splitter {
            IEDaddr = 350;
            numONUs = 2;
            @display("p=1247.54,242.06");
        }
        onu60: ONU {
            IEDaddr = 351;
            LLID = 35;
            @display("p=1247.54,332.5");
        }
        Tm860: IED {
            IEDaddr = 35;
            @display("i=device/cpu;p=1247.54,404.32");
        }
        splitter36: Splitter {
            IEDaddr = 360;
            numONUs = 2;
            @display("p=1333.99,242.06");
        }
        onu36: ONU {
            IEDaddr = 361;
            LLID = 36;
            @display("p=1333.99,332.5");
        }
        Tm836: IED {
            IEDaddr = 36;
            @display("i=device/cpu;p=1333.99,404.32");
        }
        splitter40: Splitter {
            IEDaddr = 370;
            numONUs = 1;
            @display("p=1424.43,242.06");
        }
        onu40: ONU {
            IEDaddr = 371;
            LLID = 37;
            @display("p=1424.43,332.5");
        }
        Tm840: IED {
            IEDaddr = 37;
            @display("i=device/cpu;p=1424.43,404.32");
        }
        splitter42: Splitter {
            IEDaddr = 380;
            numONUs = 2;
            @display("p=1153.11,159.6");
        }
        onu42: ONU {
            IEDaddr = 381;
            LLID = 38;
            @display("p=1238.23,158.27");
        }
        Tm842: IED {
            IEDaddr = 38;
            @display("i=device/cpu;p=1314.04,158.27");
        }
        splitter44: Splitter {
            IEDaddr = 390;
            numONUs = 1;
            @display("p=1153.11,69.16");
        }
        onu44: ONU {
            IEDaddr = 391;
            LLID = 39;
            @display("p=1238.23,67.83");
        }
        Tm844: IED {
            IEDaddr = 39;
            @display("i=device/cpu;p=1314.04,67.83");
        }
    connections:
        server.port <--> Cable <--> ADM1.elecport++;
        ADM1.optiport++ <--> Fiber155M {  length = 41.5; } <--> ADM2.optiport++;

        ADM1.elecport++ <--> Cable <--> olt1.Host;
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

		//----------------------------------------------------------------------
        ADM2.elecport++ <--> Cable <--> olt2.Host;
        olt2.Splitter <--> Fiber1G {  length = 0.1; } <--> splitter54.OLT;
        splitter54.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu54.Splitter;
        onu54.Host <--> Cable <--> Tm854.port;

        splitter54.ONU++ <--> Fiber1G {  length = 0.2; } <--> splitter30.OLT;
        splitter30.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu30.Splitter;
        onu30.Host <--> Cable <--> Tm830.port;

        splitter30.ONU++ <--> Fiber1G {  length = 6.2; } <--> splitter28.OLT;
        splitter28.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu28.Splitter;
        onu28.Host <--> Cable <--> Tm828.port;

        splitter28.ONU++ <--> Fiber1G {  length = 0.3; } <--> splitter24.OLT;
        splitter24.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu24.Splitter;
        onu24.Host <--> Cable <--> Tm824.port;

        splitter24.ONU++ <--> Fiber1G {  length = 3.1; } <--> splitter16.OLT;
        splitter16.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu16.Splitter;
        onu16.Host <--> Cable <--> Tm816.port;

        splitter16.ONU++ <--> Fiber1G {  length = 0.1; } <--> splitter14.OLT;
        splitter14.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu14.Splitter;
        onu14.Host <--> Cable <--> Tm814.port;

		//----------------------------------------------------------------------
        ADM2.elecport++ <--> Cable <--> olt3.Host;
        olt3.Splitter <--> Fiber1G {  length = 11.2; } <--> splitter52.OLT;
        splitter52.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu52.Splitter;
        onu52.Host <--> Cable <--> Tm852.port;

        splitter52.ONU++ <--> Fiber1G {  length = 0.1; } <--> splitter32.OLT;
        splitter32.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu32.Splitter;
        onu32.Host <--> Cable <--> Tm832.port;

        splitter32.ONU++ <--> Fiber1G {  length = 1.5; } <--> splitter58.OLT;
        splitter58.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu58.Splitter;
        onu58.Host <--> Cable <--> Tm858.port;

        splitter58.ONU++ <--> Fiber1G {  length = 1.8; } <--> splitter34.OLT;
        splitter34.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu34.Splitter;
        onu34.Host <--> Cable <--> Tm834.port;

        splitter34.ONU++ <--> Fiber1G {  length = 0.6; } <--> splitter60.OLT;
        splitter60.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu60.Splitter;
        onu60.Host <--> Cable <--> Tm860.port;

        splitter60.ONU++ <--> Fiber1G {  length = 1.8; } <--> splitter36.OLT;
        splitter36.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu36.Splitter;
        onu36.Host <--> Cable <--> Tm836.port;

        splitter36.ONU++ <--> Fiber1G {  length = 0.3; } <--> splitter40.OLT;
        splitter40.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu40.Splitter;
        onu40.Host <--> Cable <--> Tm840.port;

        splitter34.ONU++ <--> Fiber1G {  length = 0.1; } <--> splitter42.OLT;
        splitter42.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu42.Splitter;
        onu42.Host <--> Cable <--> Tm842.port;

        splitter42.ONU++ <--> Fiber1G {  length = 0.4; } <--> splitter44.OLT;
        splitter44.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu44.Splitter;
        onu44.Host <--> Cable <--> Tm844.port;
}



