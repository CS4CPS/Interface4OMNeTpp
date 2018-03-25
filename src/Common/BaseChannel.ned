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
channel BaseChannel extends ned.DatarateChannel
{
    double length = default(10);
    double speed @unit(s) = default(0.1s);
    datarate = default(1Mbps);
}

