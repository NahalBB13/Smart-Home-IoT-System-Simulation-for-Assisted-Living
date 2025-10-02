#include <omnetpp.h>
#include <string>
using namespace omnetpp;

class SmartDoor : public cSimpleModule {
  protected:
    virtual void initialize() override {
        scheduleAt(simTime() + uniform(1, 5), new cMessage("SmartDoorAction"));
    }

    virtual void handleMessage(cMessage *msg) override {
        cMessage *outMsg = new cMessage("SmartDoorStatus");
        bool doorUnlocked = uniform(0, 1) < 0.1; // 10% chance of door being unlocked
        outMsg->addPar("doorUnlocked") = doorUnlocked;
        send(outMsg, "gate$o", 0);
        scheduleAt(simTime() + uniform(5, 15), msg);
    }
};

Define_Module(SmartDoor);
