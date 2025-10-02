#include <omnetpp.h>
#include <string>
using namespace omnetpp;

// MotionSensor Implementation
class MotionSensor : public cSimpleModule {
  protected:
    virtual void initialize() override {
        scheduleAt(simTime() + uniform(1, 5), new cMessage("MotionSensorAction"));
    }

    virtual void handleMessage(cMessage *msg) override {
        cMessage *outMsg = new cMessage("MotionDetected");
        bool unusualMotion = uniform(0, 1) < 0.1; // 10% chance of unusual motion
        outMsg->addPar("unusualMotion") = unusualMotion;
        send(outMsg, "gate$o", 0);
        scheduleAt(simTime() + uniform(5, 15), msg);
    }
};

Define_Module(MotionSensor);
