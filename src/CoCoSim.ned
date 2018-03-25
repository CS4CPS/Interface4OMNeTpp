
package omnetcom;

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
        //int numONUs = 3;

        double tCycle @unit(s) = 0.001s;
        double tGuard @unit(s) = 0.000001s;
        int MPCPSize @unit(b) = 512b;

        @display("bgb=1700,800");
    types:
        channel Fiber155M extends DatarateChannel
        {
            double length = default(0.1);
            double speed @unit(s) = 0.000005s;
            delay = length * speed;
            datarate = 155.52Mbps;
            //datarate = 622.08Mbps;
            //datarate = 2488.32Mbps;
            //datarate = 9953.28Mbps;
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
            double length = default(0.01);
            double speed @unit(s) = 0.000005s;
            delay = length * speed;
            datarate = 100Mbps;
        }
    submodules:
        server: IED {
            IEDaddr = 20;
            @display("i=device/server;is=l;p=57.2,672.1");
        }
        ADM1: SDH_ADM {
            IEDaddr = 100;
            ProcessDelay = 0.0002;
            ThroughDelay = 0.0001;
            @display("p=55.899998,565.5;is=l");
        }
        ADM2: SDH_ADM {
            IEDaddr = 101;
            ProcessDelay = 0.0002;
            ThroughDelay = 0.0001;
            @display("p=863.2,566.8;is=l");
        }
        //------------------------------------------------------------------
        olt1: OLT {
            IEDaddr = 102;
            LLID = 5;
            LLID_BASE = 21;
            numONUs = 5;
            ProcessDelay = 0.0002;
            @display("p=57.2,456.3");
        }
        splitter00: Splitter {
            IEDaddr = 210;
            numONUs = 2;
            @display("p=127.4,456.3");
        }
        onu00: ONU {
            IEDaddr = 211;
            LLID = 21;
            @display("p=127.4,380.9");
        }
        Tm800: IED {
            IEDaddr = 21;
            @display("i=device/cpu;p=127.4,315.9");
        }
        splitter02: Splitter {
            IEDaddr = 220;
            numONUs = 2;
            @display("p=196.3,456.3");
        }
        onu02: ONU {
            IEDaddr = 221;
            LLID = 22;
            @display("p=196.3,380.9");
        }
        Tm802: IED {
            IEDaddr = 22;
            @display("i=device/cpu;p=196.3,315.9");
        }
        splitter06: Splitter {
            IEDaddr = 230;
            numONUs = 2;
            @display("p=266.5,455");
        }
        onu06: ONU {
            IEDaddr = 231;
            LLID = 23;
            @display("p=266.5,380.9");
        }
        Tm806: IED {
            IEDaddr = 23;
            @display("i=device/cpu;p=266.5,317.19998");
        }
        splitter08: Splitter {
            IEDaddr = 240;
            numONUs = 2;
            @display("p=340.6,456.3");
        }
        onu08: ONU {
            IEDaddr = 241;
            LLID = 24;
            @display("p=340.6,380.9");
        }
        Tm808: IED {
            IEDaddr = 24;
            @display("i=device/cpu;p=340.6,317.19998");
        }
        splitter10: Splitter {
            IEDaddr = 250;
            numONUs = 1;
            @display("p=300.3,617.5");
        }
        onu10: ONU {
            IEDaddr = 251;
            LLID = 25;
            @display("p=234,616.2");
        }
        Tm810: IED {
            IEDaddr = 25;
            @display("i=device/cpu;p=163.8,616.2");
        }
        //------------------------------------------------------------------        
        olt2: OLT {
            IEDaddr = 103;
            LLID = 12;
            LLID_BASE = 26;
            numONUs = 12;
            ProcessDelay = 0.0002;
            @display("p=1015.3,566.8");
        }
        splitter12: Splitter {
            IEDaddr = 260;
            numONUs = 1;
            @display("p=409.5,456.3");
        }
        onu12: ONU {
            IEDaddr = 261;
            LLID = 26;
            @display("p=409.5,380.9");
        }
        Tm812: IED {
            IEDaddr = 26;
            @display("i=device/cpu;p=409.5,317.19998");
        }
        splitter14: Splitter {
            IEDaddr = 270;
            numONUs = 2;
            @display("p=499.19998,456.3");
        }
        onu14: ONU {
            IEDaddr = 271;
            LLID = 27;
            @display("p=499.19998,380.9");
        }
        Tm814: IED {
            IEDaddr = 27;
            @display("i=device/cpu;p=504.4,317.19998");
        }
        splitter50: Splitter {
            IEDaddr = 280;
            numONUs = 2;
            @display("p=586.3,456.3");
        }
        onu50: ONU {
            IEDaddr = 281;
            LLID = 28;
            @display("p=586.3,380.9");
        }
        Tm850: IED {
            IEDaddr = 28;
            @display("i=device/cpu;p=586.3,317.19998");
        }
        splitter16: Splitter {
            IEDaddr = 290;
            numONUs = 3;
            @display("p=677.3,456.3");
        }
        onu16: ONU {
            IEDaddr = 291;
            LLID = 29;
            @display("p=577.2,523.89996");
        }
        Tm816: IED {
            IEDaddr = 29;
            @display("i=device/cpu;p=521.3,523.89996");
        }
        splitter18: Splitter {
            IEDaddr = 300;
            numONUs = 2;
            @display("p=677.3,382.19998");
        }
        onu18: ONU {
            IEDaddr = 301;
            LLID = 30;
            @display("p=767,351");
        }
        Tm818: IED {
            IEDaddr = 30;
            @display("i=device/cpu;p=852.8,351");
        }
        splitter20: Splitter {
            IEDaddr = 310;
            numONUs = 2;
            @display("p=677.3,297.69998");
        }
        onu20: ONU {
            IEDaddr = 311;
            LLID = 31;
            @display("p=767,267.8");
        }
        Tm820: IED {
            IEDaddr = 31;
            @display("i=device/cpu;p=852.8,267.8");
        }
        splitter22: Splitter {
            IEDaddr = 320;
            numONUs = 1;
            @display("p=677.3,218.4");
        }
        onu22: ONU {
            IEDaddr = 321;
            LLID = 32;
            @display("p=767,193.7");
        }
        Tm822: IED {
            IEDaddr = 32;
            @display("i=device/cpu;p=852.8,193.7");
        }
        splitter24: Splitter {
            IEDaddr = 330;
            numONUs = 3;
            @display("p=774.8,456.3");
        }
        onu24: ONU {
            IEDaddr = 331;
            LLID = 33;
            @display("p=716.3,523.89996");
        }
        Tm824: IED {
            IEDaddr = 33;
            @display("i=device/cpu;p=655.2,523.89996");
        }
        splitter26: Splitter {
            IEDaddr = 340;
            numONUs = 1;
            @display("p=864.5,456.3");
        }
        onu26: ONU {
            IEDaddr = 341;
            LLID = 34;
            @display("p=941.2,401.69998");
        }
        Tm826: IED {
            IEDaddr = 34;
            @display("i=device/cpu;p=941.2,317.19998");
        }
        splitter28: Splitter {
            IEDaddr = 350;
            numONUs = 2;
            @display("p=774.8,637");
        }
        onu28: ONU {
            IEDaddr = 351;
            LLID = 35;
            @display("p=798.2,695.5");
        }
        Tm828: IED {
            IEDaddr = 35;
            @display("i=device/cpu;p=863.2,695.5");
        }
        splitter30: Splitter {
            IEDaddr = 360;
            numONUs = 2;
            @display("p=932.1,635.7");
        }
        onu30: ONU {
            IEDaddr = 361;
            LLID = 36;
            @display("p=978.89996,695.5");
        }
        Tm830: IED {
            IEDaddr = 36;
            @display("i=device/cpu;p=1050.4,695.5");
        }
        splitter54: Splitter {
            IEDaddr = 370;
            numONUs = 2;
            @display("p=1106.2999,635.7");
        }
        onu54: ONU {
            IEDaddr = 371;
            LLID = 37;
            @display("p=1158.2999,695.5");
        }
        Tm854: IED {
            IEDaddr = 37;
            @display("i=device/cpu;p=1233.7,695.5");
        }
        //------------------------------------------------------------------
        olt3: OLT {
            IEDaddr = 104;
            LLID = 15;
            LLID_BASE = 38;
            numONUs = 15;
            ProcessDelay = 0.0002;
            @display("p=1015.3,455");
        }
        splitter56: Splitter {
            IEDaddr = 380;
            numONUs = 2;
            @display("p=1205.1,635.7");
        }
        onu56: ONU {
            IEDaddr = 381;
            LLID = 38;
            @display("p=1288.2999,634.39996");
        }
        Tm856: IED {
            IEDaddr = 38;
            @display("i=device/cpu;p=1366.2999,634.39996");
        }
        splitter52: Splitter {
            IEDaddr = 390;
            numONUs = 2;
            @display("p=1166.1,538.2");
        }
        onu52: ONU {
            IEDaddr = 391;
            LLID = 39;
            @display("p=1257.1,538.2");
        }
        Tm852: IED {
            IEDaddr = 39;
            @display("i=device/cpu;p=1315.6,581.1");
        }
        splitter32: Splitter {
            IEDaddr = 400;
            numONUs = 2;
            @display("p=1166.1,435.5");
        }
        onu32: ONU {
            IEDaddr = 401;
            LLID = 40;
            @display("p=1257.1,434.19998");
        }
        Tm832: IED {
            IEDaddr = 40;
            @display("i=device/cpu;p=1315.6,495.3");
        }
        splitter58: Splitter {
            IEDaddr = 410;
            numONUs = 3;
            @display("p=1166.1,317.19998");
        }
        onu58: ONU {
            IEDaddr = 411;
            LLID = 41;
            @display("p=1088.1,315.9");
        }
        Tm858: IED {
            IEDaddr = 41;
            @display("i=device/cpu;p=1015.3,315.9");
        }
        splitter64: Splitter {
            IEDaddr = 420;
            numONUs = 1;
            @display("p=1166.1,240.5");
        }
        onu64: ONU {
            IEDaddr = 421;
            LLID = 42;
            @display("p=1089.4,239.2");
        }
        Tm864: IED {
            IEDaddr = 42;
            @display("i=device/cpu;p=1015.3,239.2");
        }
        splitter34: Splitter {
            IEDaddr = 430;
            numONUs = 3;
            @display("p=1296.1,317.19998");
        }
        onu34: ONU {
            IEDaddr = 431;
            LLID = 43;
            @display("p=1307.7999,379.6");
        }
        Tm834: IED {
            IEDaddr = 43;
            @display("i=device/cpu;p=1354.6,436.8");
        }
        splitter60: Splitter {
            IEDaddr = 440;
            numONUs = 2;
            @display("p=1423.5,317.19998");
        }
        onu60: ONU {
            IEDaddr = 441;
            LLID = 44;
            @display("p=1423.5,379.6");
        }
        Tm860: IED {
            IEDaddr = 44;
            @display("i=device/cpu;p=1423.5,434.19998");
        }
        splitter36: Splitter {
            IEDaddr = 450;
            numONUs = 3;
            @display("p=1505.4,317.19998");
        }
        onu36: ONU {
            IEDaddr = 451;
            LLID = 45;
            @display("p=1505.4,249.59999");
        }
        Tm836: IED {
            IEDaddr = 45;
            @display("i=device/cpu;p=1505.4,192.4");
        }
        splitter40: Splitter {
            IEDaddr = 460;
            numONUs = 1;
            @display("p=1595.1,317.19998");
        }
        onu40: ONU {
            IEDaddr = 461;
            LLID = 46;
            @display("p=1595.1,249.59999");
        }
        Tm840: IED {
            IEDaddr = 46;
            @display("i=device/cpu;p=1595.1,192.4");
        }
        splitter62: Splitter {
            IEDaddr = 470;
            numONUs = 2;
            @display("p=1505.4,401.69998");
        }
        onu62: ONU {
            IEDaddr = 471;
            LLID = 47;
            @display("p=1576.9,434.19998");
        }
        Tm862: IED {
            IEDaddr = 47;
            @display("i=device/cpu;p=1576.9,495.3");
        }
        splitter38: Splitter {
            IEDaddr = 480;
            numONUs = 1;
            @display("p=1505.4,484.9");
        }
        onu38: ONU {
            IEDaddr = 481;
            LLID = 48;
            @display("p=1505.4,565.5");
        }
        Tm838: IED {
            IEDaddr = 48;
            @display("i=device/cpu;p=1505.4,634.39996");
        }
        splitter42: Splitter {
            IEDaddr = 490;
            numONUs = 2;
            @display("p=1296.1,240.5");
        }
        onu42: ONU {
            IEDaddr = 491;
            LLID = 49;
            @display("p=1374.1,239.2");
        }
        Tm842: IED {
            IEDaddr = 49;
            @display("i=device/cpu;p=1449.5,239.2");
        }
        splitter44: Splitter {
            IEDaddr = 500;
            numONUs = 2;
            @display("p=1296.1,179.4");
        }
        onu44: ONU {
            IEDaddr = 501;
            LLID = 50;
            @display("p=1374.1,178.09999");
        }
        Tm844: IED {
            IEDaddr = 50;
            @display("i=device/cpu;p=1449.5,178.09999");
        }
        splitter46: Splitter {
            IEDaddr = 510;
            numONUs = 2;
            @display("p=1296.1,120.9");
        }
        onu46: ONU {
            IEDaddr = 511;
            LLID = 51;
            @display("p=1374.1,119.6");
        }
        Tm846: IED {
            IEDaddr = 51;
            @display("i=device/cpu;p=1449.5,119.6");
        }
        splitter48: Splitter {
            IEDaddr = 520;
            numONUs = 1;
            @display("p=1296.1,54.6");
        }
        onu48: ONU {
            IEDaddr = 521;
            LLID = 52;
            @display("p=1374.1,53.3");
        }
        Tm848: IED {
            IEDaddr = 52;
            @display("i=device/cpu;p=1449.5,53.3");
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

        splitter08.ONU++ <--> Fiber1G {  length = 1.8; } <--> splitter10.OLT;
        splitter10.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu10.Splitter;
        onu10.Host <--> Cable <--> Tm810.port;


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

        splitter24.ONU++ <--> Fiber1G {  length = 0.9; } <--> splitter26.OLT;
        splitter26.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu26.Splitter;
        onu26.Host <--> Cable <--> Tm826.port;

        splitter24.ONU++ <--> Fiber1G {  length = 3.1; } <--> splitter16.OLT;
        splitter16.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu16.Splitter;
        onu16.Host <--> Cable <--> Tm816.port;

        splitter16.ONU++ <--> Fiber1G {  length = 0.5; } <--> splitter18.OLT;
        splitter18.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu18.Splitter;
        onu18.Host <--> Cable <--> Tm818.port;

        splitter18.ONU++ <--> Fiber1G {  length = 14.6; } <--> splitter20.OLT;
        splitter20.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu20.Splitter;
        onu20.Host <--> Cable <--> Tm820.port;

        splitter20.ONU++ <--> Fiber1G {  length = 4.2; } <--> splitter22.OLT;
        splitter22.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu22.Splitter;
        onu22.Host <--> Cable <--> Tm822.port;

        splitter16.ONU++ <--> Fiber1G {  length = 0.1; } <--> splitter50.OLT;
        splitter50.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu50.Splitter;
        onu50.Host <--> Cable <--> Tm850.port;

        splitter50.ONU++ <--> Fiber1G {  length = 0.1; } <--> splitter14.OLT;
        splitter14.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu14.Splitter;
        onu14.Host <--> Cable <--> Tm814.port;

        splitter14.ONU++ <--> Fiber1G {  length = 9.1; } <--> splitter12.OLT;
        splitter12.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu12.Splitter;
        onu12.Host <--> Cable <--> Tm812.port;

		//----------------------------------------------------------------------
        ADM2.elecport++ <--> Cable <--> olt3.Host;

        olt3.Splitter <--> Fiber1G {  length = 7.1; } <--> splitter56.OLT;
        splitter56.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu56.Splitter;
        onu56.Host <--> Cable <--> Tm856.port;

        splitter56.ONU++ <--> Fiber1G {  length = 11.2; } <--> splitter52.OLT;
        splitter52.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu52.Splitter;
        onu52.Host <--> Cable <--> Tm852.port;

        splitter52.ONU++ <--> Fiber1G {  length = 0.1; } <--> splitter32.OLT;
        splitter32.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu32.Splitter;
        onu32.Host <--> Cable <--> Tm832.port;

        splitter32.ONU++ <--> Fiber1G {  length = 1.5; } <--> splitter58.OLT;
        splitter58.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu58.Splitter;
        onu58.Host <--> Cable <--> Tm858.port;

        splitter58.ONU++ <--> Fiber1G {  length = 0.5; } <--> splitter64.OLT;
        splitter64.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu64.Splitter;
        onu64.Host <--> Cable <--> Tm864.port;

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

        splitter36.ONU++ <--> Fiber1G {  length = 0.1; } <--> splitter62.OLT;
        splitter62.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu62.Splitter;
        onu62.Host <--> Cable <--> Tm862.port;

        splitter62.ONU++ <--> Fiber1G {  length = 1.5; } <--> splitter38.OLT;
        splitter38.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu38.Splitter;
        onu38.Host <--> Cable <--> Tm838.port;

        splitter34.ONU++ <--> Fiber1G {  length = 0.1; } <--> splitter42.OLT;
        splitter42.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu42.Splitter;
        onu42.Host <--> Cable <--> Tm842.port;

        splitter42.ONU++ <--> Fiber1G {  length = 0.4; } <--> splitter44.OLT;
        splitter44.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu44.Splitter;
        onu44.Host <--> Cable <--> Tm844.port;

        splitter44.ONU++ <--> Fiber1G {  length = 1.1; } <--> splitter46.OLT;
        splitter46.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu46.Splitter;
        onu46.Host <--> Cable <--> Tm846.port;

        splitter46.ONU++ <--> Fiber1G {  length = 0.2; } <--> splitter48.OLT;
        splitter48.ONU++ <--> Fiber1G {  length = 0.1; } <--> onu48.Splitter;
        onu48.Host <--> Cable <--> Tm848.port;


		//----------------------------------------------------------------------
}
