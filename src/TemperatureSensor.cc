#include <omnetpp.h>
#include <string>
using namespace omnetpp;

class TemperatureSensor : public cSimpleModule {
  protected:
    virtual void initialize() override {
        scheduleAt(simTime() + 30, new cMessage("TemperatureSensorAction"));
    }

    virtual void handleMessage(cMessage *msg) override {
        if (std::string(msg->getName()) == "TemperatureSensorAction") {
            // Generate a random temperature between 20 and 30°C
            double temperature = uniform(20, 30);
            EV << "Generated New Temperature: " << temperature << "°C" << endl;

            // Create and send the TemperatureUpdate message
            cMessage *temperatureUpdateMsg = new cMessage("TemperatureUpdate");
            temperatureUpdateMsg->addPar("temperature") = temperature;
            send(temperatureUpdateMsg, "gate$o", 0);

            // Reschedule the next temperature change after 30 seconds
            scheduleAt(simTime() + 30, new cMessage("TemperatureSensorAction"));

            // Delete the current message after handling it
            delete msg;
        } else {
            // Ensure that any other messages are also deleted
            delete msg;
        }
    }
};

Define_Module(TemperatureSensor);
