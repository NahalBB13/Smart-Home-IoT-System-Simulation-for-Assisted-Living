package iot;
simple SmartDoor
{
    parameters:
        double openDuration @unit(seconds);
    gates:
        inout gate[];
}
