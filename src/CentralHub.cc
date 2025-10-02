#include <omnetpp.h>
#include <string>
using namespace omnetpp;

class CentralHub : public cSimpleModule {
  protected:
    virtual void initialize() override {
        EV << "Central Hub initialized and ready to communicate." << endl;
    }

    virtual void handleMessage(cMessage *msg) override {
        bool msgHandled = false;
        std::string msgName = msg->getName();

        if (msgName == "HealthCheckRequest") {
            for (int i = 0; i < gateSize("gate"); ++i) {
                if (std::string(gate("gate$o", i)->getNextGate()->getOwnerModule()->getFullName()) == "healthMonitor") {
                    cMessage *forwardMsg = msg->dup();
                    send(forwardMsg, "gate$o", i);
                    delete msg;  // Delete the original message after forwarding

                    EV << "Forwarded HealthCheckRequest to HealthMonitor at gate[" << i << "]" << endl;
                    msgHandled = true;
                    break;
                }
            }
        } else if (msgName == "HealthCheckResponse") {
            EV << "CentralHub received HealthCheckResponse from HealthMonitor" << endl;

            // Forward response to the user
            for (int i = 0; i < gateSize("gate"); ++i) {
                if (std::string(gate("gate$o", i)->getNextGate()->getOwnerModule()->getFullName()) == "user") {
                    cMessage *responseMsg = msg->dup();
                    send(responseMsg, "gate$o", i);
                    EV << "Forwarded HealthCheckResponse to User at gate[" << i << "]" << endl;
                    delete msg;  // Delete the original message after forwarding

                    msgHandled = true;
                    break;
                }
            }
        } else if (msgName == "SmartDoorStatus") {
            EV << "NOTIFICATION: Smart Door Status Check" << endl;

            bool doorUnlocked = msg->par("doorUnlocked").boolValue();
            if (doorUnlocked) {
                EV << "ALERT: The door is unlocked, notifying the user!" << endl;
                cMessage *alertMsg = new cMessage("SmartDoorAlert");
                alertMsg->setName("SmartDoorAlert");
                send(alertMsg, "gate$o", 0); // Forward alert to user

            } else {
                EV << "The door is locked (closed)." << endl;
            }
            delete msg;  // Delete the original message after forwarding

            msgHandled = true;

        } else if (msgName == "SecurityCameraOn") {
            EV << "NOTIFICATION: Security Camera Action - ";

            std::string cameraDetails = msg->par("details").stringValue();
            if (cameraDetails == "VideoAudioCaptured") {
                EV << "Video and Audio captured successfully." << endl;
            } else if (cameraDetails == "LiveFeedActive") {
                EV << "Live feed is being streamed to user's smartphone." << endl;
            } else if (cameraDetails == "HomeStatusChange") {
                bool isHome = msg->par("isHome").boolValue();
                EV << "User is now " << (isHome ? "home." : "away.") << endl;
            } else {
                EV << "Unknown action received from Security Camera." << endl;
            }

        } else if (msgName == "SecurityCheckRequest") {
            EV << "CentralHub received SecurityCheckRequest from User..." << endl;

            // Forward message to Security Camera
            for (int i = 0; i < gateSize("gate"); ++i) {
                if (std::string(gate("gate$o", i)->getNextGate()->getOwnerModule()->getFullName()) == "securityCamera") {
                    cMessage *forwardMsg = msg->dup();
                    send(forwardMsg, "gate$o", i);
                    EV << "Forwarded SecurityCheckRequest to Security Camera at gate[" << i << "]" << endl;
                    msgHandled = true;
                    break;
                }
            }
        } else if (msgName == "SecurityCheckResponse") {
            EV << "CentralHub received SecurityCheckResponse from Security Camera" << endl;

            // Forward response to the user
            for (int i = 0; i < gateSize("gate"); ++i) {
                if (std::string(gate("gate$o", i)->getNextGate()->getOwnerModule()->getFullName()) == "user") {
                    cMessage *responseMsg = msg->dup();
                    send(responseMsg, "gate$o", i);
                    EV << "Forwarded SecurityCheckResponse to User at gate[" << i << "]" << endl;
                    msgHandled = true;
                    break;
                }
            }
        } else if (msgName == "SmartThermostatOn") {
            EV << "NOTIFICATION: Smart Thermostat Action" << endl;

            double coLevel = msg->par("COlevel").doubleValue();
            if (coLevel > 0) {
                if (coLevel > 50) {
                    EV << "ALERT: Carbon Monoxide level is too high! Current level: " << coLevel << " ppm" << endl;
                } else {
                    EV << "Carbon Monoxide level is normal. Current level: " << coLevel << " ppm" << endl;
                }
            }

        }else if (msgName == "DoorbellPressed") {
            EV << "NOTIFICATION: Doorbell Sensor Action " << endl;

            // Simulate the logic when the doorbell is pressed
            // This should implement further interactions like face recognition or IoT communication.
            // Let's assume it's notifying the user and taking some action

            // Check for the face recognition status
            bool isPersonRegistered = true; // For simulation, assume the person is registered
            if (isPersonRegistered) {
                EV << "Doorbell detected a registered person, greeting them!" << endl;
                // Here you would add more logic like sending an image, greeting, etc.
            } else {
                EV << "Doorbell detected an unregistered person." << endl;
                // In real system, you'd show image and allow the owner to ask questions
                // You can simulate a reply by the owner here
            }
        } else if (msgName == "MotionDetected") {
            EV << "NOTIFICATION: Motion Sensor Action " << endl;

            bool unusualMotion = msg->par("unusualMotion").boolValue();
            if (unusualMotion) {
                EV << "ALERT: Unusual motion detected, notifying the user!" << endl;
                cMessage *alertMsg = new cMessage("ActivityAlert");
                alertMsg->setName("ActivityAlert");
                send(alertMsg, "gate$o", 0); // Forward alert to user
            } else {
                EV << "Motion detected, but activity is normal." << endl;
            }
            delete msg;  // Delete the original message after forwarding

            msgHandled = true;

        } else if (msgName == "SmartLightOn") {
            EV << "NOTIFICATION: Smart Light Action" << endl;

            if (static_cast<int>(simTime().dbl()) % 60 < 30) {
                EV << "ALERT: Lights have been dimmed for night mode." << endl;
            } else {
                EV << "ALERT: Light strip colors adjusted for TV viewing." << endl;
            }

        } else if (msgName == "TemperatureUpdate") {
            EV << "NOTIFICATION: Temperature Update Sensor Action" << endl;

            double temperature = msg->par("temperature").doubleValue();
            EV << "Current Temperature: " << temperature << "°C" << endl;

            if (temperature >= 25 && temperature <= 27) {
                EV << "Temperature is normal." << endl;
            } else {
                if (temperature < 25) {
                    EV << "ALERT: Temperature too low (" << temperature << "°C). Adjusting back to normal (25°C)." << endl;
                    temperature = 25;
                } else {
                    EV << "ALERT: Temperature too high (" << temperature << "°C). Adjusting back to normal (25°C)." << endl;
                    temperature = 25;
                }
            }

            msg->addPar("temperature") = temperature;
            send(msg, "gate$o", 0);
            msgHandled = true;
        } else {
            EV << "Handling other logic." << endl;
        }

        if (!msgHandled) {
            delete msg;
        }
    }
};

Define_Module(CentralHub);
