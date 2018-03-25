
package omnetcom.Common;

simple Source
{
    parameters:
        volatile double SendInterval @unit(s) = default(1s);
        int bitlenPacket = default(128);
        @display("i=block/source");
    gates:
        output out;
}


