package iot;
simple SmartThermostat
{
    parameters:
        double coLimit @unit("ppm") = 50 ppm;
        double coBaseLevel @unit("ppm") = 10 ppm;    // Base level for CO
        double coAmplitude @unit("ppm") = 30 ppm;    // Amplitude of fluctuation
        double coFrequency @unit("Hz") = 0.1 Hz;    // Frequency of fluctuation
    gates:
        inout gate[];
}
