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

package omnetcom.Host;
import omnetcom.Common.*;

//
// TODO auto-generated type
//
module host
{
    parameters:
        int IEDaddr;
        int DES;
        int DATALENBYTES = default(20);
        string IncludeInTopo = default("yes");
        double IEDSendInterval @unit(s) = default(1s);
    gates:
        inout port;

    submodules:
        InstSource: Source {
            SendInterval = IEDSendInterval;
            @display("p=219,64");
        }
        InstSink: Sink {
            @display("p=123,123");
        }
    connections:
        InstSource.out --> port$o;
        port$i --> InstSink.in;
}
