# 🏠 IoT Smart Home Simulation in OMNeT++

This project is a **Smart Home IoT Simulation** built in **OMNeT++ 6.0.3**, designed to model an intelligent home environment with **automation, security, and elderly assistance**.  

It simulates the interaction of **sensors, actuators, and a central hub** to improve safety, comfort, and monitoring for elderly residents.  
The system also integrates **health monitoring, smart lighting, door security, thermostat control, and security cameras**.

---

## 📌 Features
- 🔔**Motion Detection** (Kitchen, Bedroom, Bathroom, Living Room)  
  - Detects activity in rooms.  
  - Adjusts lighting based on room and time of day.  
  - Detects unusual movement and sends alerts.  

- 💡**Smart Light**  
  - Dynamically adjusts brightness and colors depending on context.  

- 🖥️**Central Hub (Controller)**  
  - Core of the system; receives messages and coordinates devices.  
  - Sends alerts to the user when abnormal conditions are detected.  

- 🕵️‍♂️**Security System**  
  - **Smart Door** → detects locked/unlocked state, auto-locks if left open.  
  - **Security Camera** → provides live feed, detects registered/unregistered visitors.  

- 📶**Health Monitoring**  
  - Performs elderly health checks and sends alerts if abnormal readings are found.  

- 🌡️**Smart Thermostat & CO Sensor**  
  - Maintains safe temperature and CO levels.  
  - Notifies user of unsafe conditions and auto-adjusts environment.  

---

## 🎯 Scenarios Simulated
1. **Normal daily activity** → Sensors activate, lights adjust.  
2. **Unusual motion detection** → Alert triggered.  
3. **Elderly health check** → Random normal/abnormal results.  
4. **Smart door security** → Auto-lock, monitoring door for locked/unlocked state.  
5. **Doorbell event** → Notifies the user and identifies visitors.
6. **Security camera live feed** → Visual monitoring.  
7. **Thermostat & CO sensor alerts** → Maintains safe temperature and air quality; alerts if unsafe.

---

## 🛠️ Technical Details
- **Simulator:** OMNeT++ 6.0.3  
- **Language:** C++ (`cSimpleModule`, `cMessage`)  
- **Random event generation** for realistic testing (`uniform()` and probability-based triggers).  
- **Message passing** via `gate$o` and `gate$i` connections.  
- **Parameters** used in messages (`msg->addPar("room").setStringValue("Kitchen")`).  

---

## 🚀 Running the Simulation
1. Open the project in **OMNeT++ IDE**.  
2. Build the project.  
3. Run `omnetpp.ini` configuration.  
4. Observe simulation events in the console or graphical animation.  

---

## 📊 Example Output
- *“Motion detected in Kitchen → Lights adjusted”*  
- *“Unusual activity in Bedroom → ALERT sent to user”*  
- *“Temperature too low (22°C) → Adjusting back to normal”*  
- *“Door left open too long → Auto-locked by system”*  

---

## 📷 Architecture diagram
👉   

