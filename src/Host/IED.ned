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
package omnetcom.Host;
import omnetcom.Common.*;

module IED
{
    parameters:
        int IEDaddr;
        string IncludeInTopo = default("yes");
    gates:
        inout port;
    submodules:
        trans: Sink {
            @display("p=267,162");
        }
        simapp: App {
            @display("p=152,162");
        }
        queue: L2Queue {
            parameters:
                @display("p=267,62,row");
        }
    connections:
        port$i --> simapp.in;
        simapp.out --> queue.in;
        simapp.tp --> trans.in;
        queue.out --> port$o;
}


