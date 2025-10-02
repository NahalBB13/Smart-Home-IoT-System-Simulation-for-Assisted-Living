#include <omnetpp.h>
#include <string>
using namespace omnetpp;

class HealthMonitor : public cSimpleModule {
  private:
    double heartbeat;
    double oxygenLevel;

  protected:
    virtual void initialize() override {
        heartbeat = par("heartbeat");
        oxygenLevel = par("oxygenLevel");
    }

    virtual void handleMessage(cMessage *msg) override {
        std::string msgName = msg->getName();

        if (msgName == "HealthCheckRequest") {
            EV << "HealthMonitor received HealthCheckRequest from CentralHub" << endl;

            // Simulate checking health
            randomizeHealthValues();
            checkHealth();

            // Create a response message
            cMessage *responseMsg = new cMessage("HealthCheckResponse");
            responseMsg->addPar("heartbeat") = heartbeat;
            responseMsg->addPar("oxygenLevel") = oxygenLevel;

            // Send response back to CentralHub
            send(responseMsg, "gate$o", 0);

            delete msg; // Clean up request message
        } else {
            delete msg;
        }
    }

    void randomizeHealthValues() {
        heartbeat = uniform(40, 130);
        oxygenLevel = uniform(85, 100);
    }

    void checkHealth() {
        if (heartbeat > 120) {
            EV << "ALERT: Heartbeat too high!" << endl;
        } else if (heartbeat < 50) {
            EV << "ALERT: Heartbeat too low!" << endl;
        } else {
            EV << "Heartbeat is normal." << endl;
        }

        if (oxygenLevel < 90) {
            EV << "ALERT: Oxygen level too low!" << endl;
        } else {
            EV << "Oxygen level is normal." << endl;
        }
    }
};

Define_Module(HealthMonitor);
