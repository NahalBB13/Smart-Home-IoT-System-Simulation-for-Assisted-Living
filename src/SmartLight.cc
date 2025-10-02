#include <omnetpp.h>
#include <string>
#include <cmath> // for fmod
using namespace omnetpp;

class SmartLight : public cSimpleModule {
  protected:
    virtual void initialize() override {
        // Schedule the first event (SmartLightAction) after a random time between 1 and 5 seconds.
        scheduleAt(simTime() + uniform(1, 5), new cMessage("SmartLightAction"));
    }

    virtual void handleMessage(cMessage *msg) override {
        // Generate random behavior every 30 seconds (based on time)
        if (fmod(simTime().dbl(), 10.0) < 1.0) {
            // Check if it is night time (within first 30 seconds of each minute)
            if (static_cast<int>(simTime().dbl()) % 60 < 30) {
                EV << "Dimmed the lights since it's night" << endl;
                // Send message to SmartLight to indicate the light is on
                cMessage *outMsg = new cMessage("SmartLightOn");
                send(outMsg, "gate$o", 0);
            }
            // Daytime or another condition - change light strip colors for better TV view
            else {
                EV << "Changed light strip colors for better TV view" << endl;
                // Send message to SmartLight to indicate the light is on
                cMessage *outMsg = new cMessage("SmartLightOn");
                send(outMsg, "gate$o", 0);
            }
        }

        // Schedule the next action after a random time between 5 and 15 seconds
        scheduleAt(simTime() + uniform(5, 15), msg);
    }
};

Define_Module(SmartLight);
