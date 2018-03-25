
package omnetcom.simulations;

import ned.DatarateChannel;
import omnetcom.Common.*;
import omnetcom.SDH.*;
import omnetcom.EPON.*;
import omnetcom.Host.*;

network SmartGrid_EPON_Sources
{
    types:
        channel C extends DatarateChannel
        {
            double length = default(0.1);
    		double speed @unit(s) = 0.1s;
    		delay = length * speed;
    		datarate = 1Mbps;
        }
    submodules:
        server: Server {
            IEDaddr = 20;
            @display("i=device/server;p=49,50");
        }
        ADMHead: SDH_ADM {
            IEDaddr = 100;
            ProcessDelay = 2;
    		ThroughDelay = 1;
            @display("p=259,50");
        }
        ADMMid: SDH_ADM {
            IEDaddr = 101;
            ProcessDelay = 2;
    		ThroughDelay = 1;            
            @display("p=152,145");
        }
        ADMTail: SDH_ADM {
            IEDaddr = 102;
            ProcessDelay = 2;
    		ThroughDelay = 1;            
            @display("p=49,232");
        }
        Tm802: host {
            IEDaddr = 21;
            IEDSendInterval = 10s;
            @display("p=259,232");
        }
    connections:
        server.port <--> C{length=0.1;} <--> ADMHead.elecport++;
        ADMHead.optiport++ <--> C{length=3;} <--> ADMMid.optiport++;
        ADMMid.optiport++ <--> C{length=4;} <--> ADMTail.optiport++;
        ADMTail.elecport++ <--> C{length=0.1;} <--> Tm802.port;
}


