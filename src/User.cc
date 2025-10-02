#include <omnetpp.h>
using namespace omnetpp;

class User : public cSimpleModule {
  private:
    cMessage *healthCheckTimer;
    cMessage *securityCheckTimer;
    cMessage *mobileAlertTimer;


  protected:
    virtual void initialize() override {
        healthCheckTimer = new cMessage("HealthCheckTimer");
        securityCheckTimer = new cMessage("SecurityCheckTimer");

        scheduleAt(simTime() + 20, healthCheckTimer);
        scheduleAt(simTime() + 10, securityCheckTimer);
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg == healthCheckTimer) {
            EV << "User sending HealthCheckRequest to CentralHub..." << endl;
            cMessage *healthCheckMsg = new cMessage("HealthCheckRequest");
            send(healthCheckMsg, "gate$o", 0); // Send via first gate

            // Reschedule next health check
            scheduleAt(simTime() + 20, healthCheckTimer);
        }
        else if (msg == securityCheckTimer) {
            EV << "User sending SecurityCheckRequest to CentralHub..." << endl;
            cMessage *securityCheckMsg = new cMessage("SecurityCheckRequest");
            send(securityCheckMsg, "gate$o", 0); // Send via second gate

            // Reschedule next security check
            scheduleAt(simTime() + 70, securityCheckTimer);
        }
        else if (strcmp(msg->getName(), "ActivityAlert") == 0) {
                   EV << "ALERT: Something is not right with the activity level!" << endl;
                   // Send message to user.ned to alert them
                   cMessage *alertMsg = new cMessage("ActivityAlert");
                   alertMsg->setName("ActivityAlert");
                   send(alertMsg, "gate$o", 0); // Forward alert to user.ned
                   delete msg;
        }
        else if (strcmp(msg->getName(), "SmartDoorStatus") == 0) {
                    EV << "ALERT: Checking Smart Door status!" << endl;
                    bool doorUnlocked = msg->par("doorUnlocked").boolValue();
                    if (doorUnlocked) {
                        EV << "ALERT: The door is unlocked, notifying user!" << endl;
                        cMessage *alertMsg = new cMessage("SmartDoorAlert");
                        alertMsg->setName("SmartDoorAlert");
                        send(alertMsg, "gate$o", 0); // Forward alert to user
                    } else {
                        EV << "The door is locked (closed)." << endl;
                    }
                    delete msg;
        }
        else {
            EV << "User received response: " << msg->getName() << endl;
            delete msg;
        }
    }

    virtual void finish() override {
        cancelAndDelete(healthCheckTimer);
        cancelAndDelete(securityCheckTimer);
    }
};

Define_Module(User);
