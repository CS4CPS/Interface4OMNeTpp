//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

//package omnetcom.model;

//
// Interface for network traffic generator modules that
// can be used in Node.
//
package omnetcom.SDH;
import omnetcom.Common.*;

module SDH_ADM
{
    parameters:
        int IEDaddr;
        string IncludeInTopo = default("yes");
        double ProcessDelay = default(0);
    	double ThroughDelay = default(0);
        @display("i=device/mainframe");
    gates:
        inout elecport[];
        inout optiport[];
    submodules:
        man: Manager {
            @display("p=109,324");
        }
        routing: SDH_Routing {
            parameters:
                @display("p=109,224");
            gates:
                in[sizeof(elecport)+sizeof(optiport)];
                out[sizeof(elecport)+sizeof(optiport)];
        }
        queue[sizeof(elecport)+sizeof(optiport)]: SDH_Queue {
            parameters:
                @display("p=365,224,row");
        }
    connections:
        routing.localOut --> man.in;
        routing.localIn <-- man.out;
        for i=0..(sizeof(elecport)-1) {
            elecport$i[i] --> routing.in[i];
            routing.out[i] --> queue[i].in;
            queue[i].out --> elecport$o[i];
        }
        for i=sizeof(elecport)..(sizeof(elecport)+sizeof(optiport)-1) {
            optiport$i[i-sizeof(elecport)] --> routing.in[i];
            routing.out[i] --> queue[i].in;
            queue[i].out --> optiport$o[i-sizeof(elecport)];
        }
}


