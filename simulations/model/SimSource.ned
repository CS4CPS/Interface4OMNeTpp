
package omnetcom.simulations.model;

simple SimSource
{
    parameters:
        volatile double SendInterval @unit(s) = default(1s);
        int bitlenPacket = default(128);
        @display("i=block/source");
    gates:
        output out;
}


