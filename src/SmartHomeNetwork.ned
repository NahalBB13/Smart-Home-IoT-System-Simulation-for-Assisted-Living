package iot;
network SmartHomeNetwork
{
    @display("bgb=865,464");
    submodules:
        user: User {
            @display("i=IOT/user;p=170.54124,150.98875");
        }
        motionSensor: MotionSensor {
            @display("i=IOT/sensor;p=373,46");
        }
        tempSensor: TemperatureSensor {
            @display("i=IOT/temperature-sensor;p=627.8525,112.97");
        }
        healthMonitor: HealthMonitor {
            @display("i=IOT/health;p=236,228");
        }
        smartLock: SmartDoor {
            @display("i=IOT/door-handle;p=363,289");
        }
        doorbellSensor: DoorbellSensor {
            @display("i=IOT/doorbell;p=627.8525,217.25");
        }
        securityCam: SecurityCamera {
            @display("i=IOT/cctv;p=527.9175,280.2525");
        }
        smartLight: SmartLight {
            @display("i=IOT/smartlight (2);p=243.32,79.29625");
        }
        smartThermostat: SmartThermostat {
            @display("i=IOT/thermostat (3);p=528,56");
        }
        centralHub: CentralHub {
            @display("i=device/hub;p=434.5,187.92125");
        }
    connections allowunconnected:
        user.gate++ <--> centralHub.gate++;
        motionSensor.gate++ <--> centralHub.gate++;
        tempSensor.gate++ <--> centralHub.gate++;
        healthMonitor.gate++ <--> centralHub.gate++;
        smartLock.gate++ <--> centralHub.gate++;
        doorbellSensor.gate++ <--> centralHub.gate++;
        securityCam.gate++ <--> centralHub.gate++;
        smartLight.gate++ <--> centralHub.gate++;
        smartThermostat.gate++ <--> centralHub.gate++;
}
