# 🏠 ESP8266 Firebase IoT Home Automation System

**Control Appliances via Web Dashboard, Manual Switch & EEPROM**

---

## 📌 Project Description

This project demonstrates a **complete IoT-based Smart Home Automation System** using **ESP8266 NodeMCU**, **Firebase Realtime Database**, and a **responsive Web Dashboard hosted on GitHub Pages** — **no mobile app required**.

The system allows you to control **4 electrical appliances** using:

* 🌐 Web browser (remote control)
* 🔘 Manual push buttons or latched switches
* 💾 EEPROM memory to restore relay states after power failure

All relay states are **synchronized in real-time** with Firebase, ensuring reliability and seamless control from anywhere in the world.

---

## 🚀 Key Features

* ✅ ESP8266 NodeMCU with Wi-Fi connectivity
* 🔥 Firebase Realtime Database integration
* 🌍 Web dashboard (PC & Mobile friendly)
* 🔘 Manual control using push buttons or latched switches
* 💾 EEPROM-based relay state recovery
* 🔐 Firebase Email/Password Authentication
* 💡 Wi-Fi & Firebase connection status LED
* ⚡ Active-LOW relay logic
* 🔁 Real-time sync between hardware & cloud

---

## 🧠 How the System Works

1. ESP8266 connects to **Wi-Fi**
2. Firebase is initialized using **Email/Password authentication**
3. On boot:

   * Relay states are restored from **EEPROM**
4. User controls relays via:

   * Web Dashboard
   * Physical switches
5. Any change:

   * Updates Firebase instantly
   * Syncs back to ESP8266
6. After power failure:

   * Last relay state is restored automatically

---

## 🧰 Required Components

| Component                           | Quantity    |
| ----------------------------------- | ----------- |
| ESP8266 NodeMCU                     | 1           |
| 5V 4-Channel Relay Module (SPDT)    | 1           |
| Push Buttons or Latched Switches    | 4           |
| 5V 5A Mobile Charger (Power Supply) | 1           |
| Jumper Wires                        | As required |

⚠ **Safety Note:**
Always take proper precautions while working with **AC appliances**.

---

## 🔌 GPIO Pin Configuration

### Relay Connections (Active LOW)

| Relay   | ESP8266 Pin | GPIO    |
| ------- | ----------- | ------- |
| Relay 1 | D1          | GPIO-5  |
| Relay 2 | D2          | GPIO-4  |
| Relay 3 | D5          | GPIO-14 |
| Relay 4 | D6          | GPIO-12 |

### Manual Switch Connections

| Switch   | ESP8266 Pin | GPIO    |
| -------- | ----------- | ------- |
| Switch 1 | SD3         | GPIO-10 |
| Switch 2 | D3          | GPIO-0  |
| Switch 3 | D7          | GPIO-13 |
| Switch 4 | RX          | GPIO-3  |

---

## 🔘 INPUT_PULLUP Explained

This project uses **`INPUT_PULLUP`**, so:

* No external pull-up resistors are required
* Default state is **HIGH**
* Button press connects pin to **GND (LOW)**

```cpp
pinMode(SwitchPin1, INPUT_PULLUP);
```

---

## 🔄 Relay Logic (Active LOW)

| Signal | Relay State |
| ------ | ----------- |
| LOW    | ON          |
| HIGH   | OFF         |

---

## 🔧 Firebase Configuration (Step-by-Step)

### 1️⃣ Create Firebase Project

* Go to **Firebase Console**
* Click **Add Project**

### 2️⃣ Enable Realtime Database

* Build → Realtime Database
* Create Database → Start in test mode

### 3️⃣ Enable Authentication

* Build → Authentication → Sign-in Method
* Enable **Email/Password**

### 4️⃣ Create a User

* Authentication → Users → Add User

### 5️⃣ Get Credentials

* Project Settings → General
* Copy **Web API Key**
* Copy **Database URL**

### 6️⃣ Update Database Rules

```json
{
  "rules": {
    ".read": "auth != null",
    ".write": "auth != null"
  }
}
```

🔐 Only authenticated users can access the database.

---

## 🧑‍💻 Arduino IDE Setup

### Board Manager URLs

```
https://dl.espressif.com/dl/package_esp32_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

### ESP8266 Board Version

* **ESP8266 Board v3.1.2**

### Required Libraries

| Library                      | Version |
| ---------------------------- | ------- |
| Firebase_ESP_Client (Mobizt) | 4.4.17  |
| ArduinoJson                  | 7.4.1   |
| AceButton                    | 1.10.1  |

---

## 🔑 Code Configuration

Update the following fields:

```cpp
// Wi-Fi
const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";

// Firebase
#define API_KEY "YourFirebaseWebAPIKey"
#define DATABASE_URL "https://your-project-id.firebasedatabase.app/"
#define USER_EMAIL "firebase-user-email"
#define USER_PASSWORD "firebase-user-password"
```

---

## ⚙ Feature Flags

```cpp
bool useEEPROM = true;        // Enable state recovery
bool useLatchedSwitch = true; // true = latched, false = push button
```

---

## 💾 EEPROM Functionality

* Stores relay ON/OFF state
* Automatically restores after restart or power failure
* Address-based storage for each relay

---

## 🔘 Button Handling (AceButton)

* Debounced & event-based
* Supports:

  * Latched switches
  * Momentary push buttons
* Syncs manual actions with Firebase

---

## 🔁 Firebase Synchronization

* First connection:

  * EEPROM → Firebase
* Continuous operation:

  * Firebase → Relay
  * Button → Firebase

---

## 🌐 Deploy Web Dashboard (GitHub Pages)

1. Create GitHub repo
2. Upload `index.html`
3. Settings → Pages
4. Source → `main` / root
5. Access your dashboard:

```
https://username.github.io/repository-name/
```

---

## 🧪 Testing Checklist

* ✅ Wi-Fi connects successfully
* ✅ Firebase authentication works
* ✅ Relay toggles via dashboard
* ✅ Manual switch control works
* ✅ EEPROM restores state after reboot

---

## 🛠 Troubleshooting

* Firebase not connecting → check API key & auth
* Relay not switching → confirm Active-LOW logic
* Button not responding → verify INPUT_PULLUP wiring

---

## 🔮 Future Improvements

* Google Assistant / Alexa integration
* Mobile app version
* Energy monitoring
* OTA firmware updates

---

# 📘 Detailed Source Code Explanation

This section explains the complete ESP8266 NodeMCU source code used in this IoT Home Automation project, covering **Wi-Fi**, **Firebase**, **EEPROM**, **relay control**, and **manual switch handling**.

---

## 📚 Library Includes & Namespace

```cpp
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <AceButton.h>
#include <EEPROM.h>

using namespace ace_button;
```

### Explanation:

* **ESP8266WiFi.h** → Enables Wi-Fi connectivity for NodeMCU
* **Firebase_ESP_Client.h** → Firebase Realtime Database operations
* **AceButton.h** → Reliable button handling with debounce & events
* **EEPROM.h** → Stores relay states permanently
* `using namespace ace_button;` → Simplifies AceButton usage

---

## 🌐 Wi-Fi & Firebase Credentials

```cpp
const char* ssid = "";
const char* password = "";

#define API_KEY ""
#define DATABASE_URL ""
#define USER_EMAIL ""
#define USER_PASSWORD ""
```

### Explanation:

* Stores Wi-Fi credentials
* Firebase **Web API Key**, **Database URL**, and **Authentication credentials**
* These values must match your Firebase project

---

## ⚙ Feature Flags

```cpp
bool useEEPROM = true;
bool useLatchedSwitch = true;
```

### Explanation:

* `useEEPROM` → Enables relay state recovery after power loss
* `useLatchedSwitch`:

  * `true` → Toggle switch
  * `false` → Push button

---

## 📌 Firebase State Flags

```cpp
bool firebaseInitialized = false;
bool firebaseWasReady = false;
```

### Explanation:

* Tracks Firebase initialization
* Ensures EEPROM → Firebase sync happens **only once**

---

## 🔌 GPIO Pin Definitions

```cpp
#define RELAY1 5
#define RELAY2 4
#define RELAY3 14
#define RELAY4 12

#define SwitchPin1 10
#define SwitchPin2 0
#define SwitchPin3 13
#define SwitchPin4 3

#define wifiLed 16
```

### Explanation:

* Relay pins are **Active LOW**
* Switch pins use **INPUT_PULLUP**
* `wifiLed` indicates Wi-Fi & Firebase status

---

## 🔥 Firebase Objects & Button Setup

```cpp
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
```

### Explanation:

* `fbdo` → Firebase data handler
* `auth` → Email/Password authentication
* `config` → API key & database URL

---

## 🔘 AceButton Configuration

```cpp
ButtonConfig config1, config2, config3, config4;

AceButton button1(&config1, SwitchPin1);
AceButton button2(&config2, SwitchPin2);
AceButton button3(&config3, SwitchPin3);
AceButton button4(&config4, SwitchPin4);
```

### Explanation:

* Each switch has its own configuration
* AceButton handles debounce automatically

---

## 💾 EEPROM Address Allocation

```cpp
#define EEPROM_SIZE 10
#define RELAY1_ADDR 0
#define RELAY2_ADDR 1
#define RELAY3_ADDR 2
#define RELAY4_ADDR 3
```

### Explanation:

* Each relay state is stored in EEPROM
* EEPROM size is sufficient for future expansion

---

## ✍ EEPROM Write Function

```cpp
void writeRelayStateToEEPROM(uint8_t addr, bool state) {
  if (useEEPROM) {
    EEPROM.write(addr, state ? 1 : 0);
    EEPROM.commit();
  }
}
```

### Explanation:

* Stores relay ON/OFF state
* `commit()` ensures data is saved permanently

---

## 📖 EEPROM Read Function

```cpp
bool readRelayStateFromEEPROM(uint8_t addr) {
  return EEPROM.read(addr) == 1;
}
```

### Explanation:

* Reads last stored relay state
* Returns `true` for ON, `false` for OFF

---

## ⚡ Relay Control Function

```cpp
void setRelay(int relayPin, int eepromAddr, bool state) {
  digitalWrite(relayPin, state ? LOW : HIGH);
  writeRelayStateToEEPROM(eepromAddr, state);
}
```

### Explanation:

* **LOW → Relay ON**
* **HIGH → Relay OFF**
* Saves state to EEPROM

---

## 🔘 Button Event Handler (Core Logic)

```cpp
void handleEvent(AceButton* button, uint8_t eventType, uint8_t) {
```

### Latched Switch Mode

```cpp
if (useLatchedSwitch) {
  newState = (eventType == AceButton::kEventPressed);
}
```

### Push Button Mode

```cpp
if (eventType == AceButton::kEventReleased) {
  newState = !(digitalRead(RELAY1) == LOW);
}
```

### Explanation:

* Supports **two switch types**
* Determines relay state dynamically
* Prevents false triggers

---

## 🔁 Manual → Firebase Sync

```cpp
Firebase.RTDB.setBool(&fbdo, "/relay1", newState);
```

### Explanation:

* Any manual action updates Firebase instantly
* Keeps web dashboard synchronized

---

## 🛠 setup() Function

### Serial & EEPROM Init

```cpp
Serial.begin(115200);
EEPROM.begin(EEPROM_SIZE);
```

### Relay Initialization

```cpp
pinMode(RELAY1, OUTPUT);
digitalWrite(RELAY1, HIGH);
```

### Restore EEPROM State

```cpp
setRelay(RELAY1, RELAY1_ADDR, readRelayStateFromEEPROM(RELAY1_ADDR));
```

### INPUT_PULLUP Setup

```cpp
pinMode(SwitchPin1, INPUT_PULLUP);
```

---

## 🌐 Wi-Fi Connection

```cpp
waitForWiFi();
```

### Explanation:

* Tries Wi-Fi for 10 seconds
* Restarts ESP if failed

---

## 🔐 Firebase Initialization

```cpp
Firebase.begin(&config, &auth);
Firebase.reconnectWiFi(true);
```

### Explanation:

* Starts Firebase securely
* Auto-reconnect enabled

---

## 🔄 loop() Function

### Wi-Fi Status Indicator

```cpp
digitalWrite(wifiLed, wifiConnected ? LOW : HIGH);
```

### EEPROM → Firebase Sync (First Time)

```cpp
Firebase.RTDB.setBool(&fbdo, "/relay1", readRelayStateFromEEPROM(RELAY1_ADDR));
```

### Firebase → Relay Sync

```cpp
Firebase.RTDB.getBool(&fbdo, "/relay1");
```

### Button Monitoring

```cpp
button1.check();
```
---

## 👨‍💻 Author

**Prakash Kumar Sahoo**
📧 Email: **[codewithprakash.dev@gmail.com](mailto:codewithprakash.dev@gmail.com)**

---

## ⭐ Support

If you like this project:

* ⭐ Star the repository
* 🍴 Fork it
* 📢 Share with others
