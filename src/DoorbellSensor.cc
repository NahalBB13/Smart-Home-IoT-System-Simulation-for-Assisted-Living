#include <omnetpp.h>
#include <string>
using namespace omnetpp;

class DoorbellSensor : public cSimpleModule {
  protected:
    virtual void initialize() override {
        // Schedule the first doorbell sensor action at a random time
        scheduleAt(simTime() + uniform(1, 5), new cMessage("DoorbellSensorAction"));
    }

    virtual void handleMessage(cMessage *msg) override {
        std::string msgName = msg->getName();

        if (msgName == "DoorbellSensorAction") {
            // Simulate the doorbell press
            cMessage *outMsg = new cMessage("DoorbellPressed");
            send(outMsg, "gate$o", 0);  // Send the doorbell press message

            // Simulate the person detection and registration check
            bool isPersonRegistered = simulateFaceRecognition();

            if (isPersonRegistered) {
                EV << "Doorbell detected a registered person, greeting them!" << endl;

                // Simulate notifying the owner via IoT (you can extend this logic with actual IoT message sending)
                // For example, send an image or message to the owner via IoT system

            } else {
                EV << "Doorbell detected an unregistered person." << endl;

                // In a real system, you would show the image and allow the owner to ask a question/reply via IoT
                // For now, simulate that interaction
                simulateOwnerInteraction();
            }

            // Re-schedule the doorbell action to occur later
            scheduleAt(simTime() + uniform(5, 15), msg);
        }
    }

  private:
    // Simulate face recognition
    bool simulateFaceRecognition() {
        // For now, we randomly decide if the person is registered
        // In a real-world scenario, this would involve actual face recognition logic
        return uniform(0, 1) > 0.5;  // 50% chance of the person being registered
    }

    // Simulate the interaction with the owner when the person is unregistered
    void simulateOwnerInteraction() {
        EV << "Simulating owner interaction via IoT: Question/Reply options." << endl;
        // Here you could simulate options for the owner to choose from via IoT interface
        // For example, text-to-speech or sending a reply back
    }
};

Define_Module(DoorbellSensor);
