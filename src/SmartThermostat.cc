#include <omnetpp.h>
#include <string>
#include <cmath>  // For sine wave function
using namespace omnetpp;

class SmartThermostat : public cSimpleModule {
  private:
    double coLimit; // CO limit for Carbon Monoxide levels
    double coBaseLevel; // Base CO level (e.g., from environment)
    double coAmplitude; // Amplitude for fluctuation
    double coFrequency; // Frequency of fluctuation (time-based)
    simtime_t lastTime; // Time of the last CO level update

  protected:
    virtual void initialize() override {
        // Initialize CO limit and environment factors (can be customized in .ini file)
        coLimit = par("coLimit").doubleValue();
        coBaseLevel = par("coBaseLevel").doubleValue();
        coAmplitude = par("coAmplitude").doubleValue();
        coFrequency = par("coFrequency").doubleValue();

        // Schedule thermostat action
        lastTime = simTime();
        scheduleAt(simTime() + uniform(1, 5), new cMessage("SmartThermostatAction"));
    }

    virtual void handleMessage(cMessage *msg) override {
        if (std::string(msg->getName()) == "SmartThermostatAction") {
            // Simulate CO levels with fluctuation over time based on environmental factors
            double timeElapsed = (simTime() - lastTime).dbl();  // Time since last update
            double fluctuatedCO = coBaseLevel + coAmplitude * sin(coFrequency * timeElapsed);

            // Ensure the CO level is within a reasonable range
            fluctuatedCO = std::max(0.0, std::min(fluctuatedCO, 100.0));  // Clamp between 0 and 100 ppm

            EV << "Current CO level (simulated): " << fluctuatedCO << " ppm" << endl;

            // Send SmartThermostatOn message to CentralHub with the fluctuated CO level
            cMessage *outMsg = new cMessage("SmartThermostatOn");
            outMsg->addPar("COlevel") = fluctuatedCO;
            send(outMsg, "gate$o", 0);

            // Reschedule thermostat action after a random time (5 to 15 seconds)
            scheduleAt(simTime() + uniform(5, 15), msg);
            lastTime = simTime();  // Update last time for the next fluctuation
        }
    }
};

Define_Module(SmartThermostat);
