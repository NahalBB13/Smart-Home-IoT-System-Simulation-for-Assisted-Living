package iot;
simple HealthMonitor
{
    parameters:
        double heartbeat @unit(bpm);
        double oxygenLevel @unit(percentage);
    gates:
        inout gate[];
}
