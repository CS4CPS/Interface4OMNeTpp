//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package omnetcom.simulations;
import omnetcom.Common.*;
import omnetcom.EPON.*;
import omnetcom.Host.*;

network test
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

        double credit = default(0);

        double tCycle @unit(s) = 0.001s;

        double tGuard @unit(s) = 0.000001s;

        double tProp @unit(s) = 0.0001s;

        double tDBA @unit(s) = default(0);

        int MPCPSize @unit(b) = 512b;

        int bufferSize @unit(b) = 8388608b;

        @display("bgb=460,460");
    types:
        channel Fiber extends ned.DatarateChannel
        {
            double length = default(5);
            double speed @unit(s) = 0.00001s;
            delay = length * speed;
            datarate = 1Gbps;
        }
        //channel FiberBetweenONUAndSplitter extends ned.DatarateChannel
        //{
        //    delay = 0s;
        //    datarate = 1Gbps;
        //}
        channel Cable extends ned.DatarateChannel
        {
            delay = 0;
            datarate = 100Mbps;
        }
    submodules:
        server: Server {
            IEDaddr = 20;
            IEDSendInterval = 0.001s;
            @display("i=device/server;p=49,50");
        }
        olt: OLT {
            LLID = numONUs;
            LLID_BASE = 21;
            numONUs = numONUs;
            @display("p=315,50");
        }
        splitter: Splitter {
            numONUs = numONUs;
            @display("p=179,140");
            gates:
                ONU[numONUs];
        }
        onu0: ONU {
            LLID = 21;
            @display("p=49,140");
        }
        onu1: ONU {
            LLID = 22;
            @display("p=315,140");
        }
        onu2: ONU {
            LLID = 23;
            @display("p=179,228");
        }
        user0: host {
            IEDaddr = 21;
            DES = 20;
            IEDSendInterval = 0.003s;
            @display("p=49,228");
        }
        user1: host {
            IEDaddr = 22;
            DES = 20;
            IEDSendInterval = 0.003s;
            @display("p=315,228");
        }
        user2: host {
            IEDaddr = 23;
            DES = 20;
            IEDSendInterval = 0.003s;
            @display("p=179,321");
        }
    connections:
        server.port <--> Cable <--> olt.Host;

        olt.Splitter <--> Fiber {  length = 5; } <--> splitter.OLT;

        onu0.Splitter <--> Fiber {  length = 5; } <--> splitter.ONU[0];

        onu1.Splitter <--> Fiber {  length = 10; } <--> splitter.ONU[1];

        onu2.Splitter <--> Fiber {  length = 15; } <--> splitter.ONU[2];

        user0.port$o --> Cable --> onu0.Host$i;
        user0.port$i <-- Cable <-- onu0.Host$o;

        user1.port$o --> Cable --> onu1.Host$i;
        user1.port$i <-- Cable <-- onu1.Host$o;

        user2.port$o --> Cable --> onu2.Host$i;
        user2.port$i <-- Cable <-- onu2.Host$o;

}
