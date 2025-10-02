#include <omnetpp.h>
#include <string>
using namespace omnetpp;

class SecurityCamera : public cSimpleModule {
  private:
    bool isHome; // Flag to determine if the user is home or away

  protected:
    virtual void initialize() override {
        isHome = true; // Assume the user starts at home
        scheduleAt(simTime() + uniform(1, 5), new cMessage("SecurityCameraAction"));
        scheduleAt(simTime() + 30, new cMessage("ToggleHomeStatus")); // Toggle home status every 30 seconds
    }

    virtual void handleMessage(cMessage *msg) override {
        std::string msgName = msg->getName();

        if (msgName == "SecurityCameraAction") {
            // Simulate video/audio capture and live feed
            cMessage *outMsg = new cMessage("SecurityCameraOn");
            outMsg->addPar("details") = "VideoAudioCaptured";
            send(outMsg, "gate$o", 0);

            if (!isHome) {
                cMessage *liveFeedMsg = new cMessage("SecurityCameraOn");
                liveFeedMsg->addPar("details") = "LiveFeedActive";
                send(liveFeedMsg, "gate$o", 0);
            }

            scheduleAt(simTime() + uniform(5, 15), msg); // Reschedule action

        } else if (msgName == "ToggleHomeStatus") {
            // Toggle home/away status
            isHome = !isHome;
            cMessage *homeStatusMsg = new cMessage("SecurityCameraOn");
            homeStatusMsg->addPar("details") = "HomeStatusChange";
            homeStatusMsg->addPar("isHome") = isHome;
            send(homeStatusMsg, "gate$o", 0);

            EV << "Security Camera: User status toggled. Now " << (isHome ? "home." : "away.") << endl;
            scheduleAt(simTime() + 30, msg); // Reschedule home status toggle

        } else if (msgName == "SecurityCheckRequest") {
            // Handle Security Check request from the User
            EV << "Security Camera: Received SecurityCheckRequest from User." << endl;

            // Respond with a Security Check Response
            cMessage *securityCheckResponse = new cMessage("SecurityCheckResponse");
            securityCheckResponse->addPar("isHome") = isHome;
            send(securityCheckResponse, "gate$o", 0);
            EV << "Security Camera: Sent SecurityCheckResponse to CentralHub/User." << endl;
        }
    }
};

Define_Module(SecurityCamera);
