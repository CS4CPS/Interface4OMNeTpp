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

package omnetcom.EPON;
import omnetcom.EPON.IPACT.IntraScheduler;
import omnetcom.EPON.Queue.Queue;

module ONU
{
    parameters:
        int IEDaddr;
        string IncludeInTopo = default("yes");
        int LLID;
        double tEFDC @unit(s) = default(0);
        double tAFDC @unit(s) = default(0);
        double tBEDC @unit(s) = default(0);
        double pActive @unit(W) = default(0);
        double pSleep @unit(W) = default(0);
        double tOverhead @unit(s) = default(0); 
        int bitlenMPCP = default(512);     
        double ProcessDelay = default(0); 
        @display("i=device/smallrouter");
    gates:
        inout Host;
        inout Splitter;
    submodules:
        scheduler: IntraScheduler {
            LLID = LLID; 
            @display("p=234,39");
        }
        queue: Queue {
            @display("p=151,39");
        }
        outqueue: EPON_Queue {

            @display("p=234,55");
        }        
    connections:
        //connections to OLT
        Splitter$i --> scheduler.rxSplitter;
        scheduler.txSplitter --> Splitter$o;

        //connections to user
        Host$i --> scheduler.rxHost;
        scheduler.txHost --> outqueue.in;
        outqueue.out --> Host$o;
}
