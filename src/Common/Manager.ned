//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//
package omnetcom.Common;
//
// Destroys the packets and collects statistics
//
simple Manager
{
    parameters:
        @display("i=device/cpu");
    gates:
        input in;
        output out;
}

