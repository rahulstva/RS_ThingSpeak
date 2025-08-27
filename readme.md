# RS_ThingSpeak

A lightweight Arduino library for **ThingSpeak IoT Platform**.  
Supports ESP32/ESP8266 with easy methods to:

- Send data to multiple fields
- Read data from multiple fields
- Read a specific TalkBack command by ID (without executing)

## 📂 Folder Structure
RS_ThingSpeak/
├── examples/
│   ├── SendData/
│   │   └── SendData.ino
│   ├── ReadData/
│   │   └── ReadData.ino
│   ├── TalkBackReadByID/
│   │   └── TalkBackReadByID.ino
├── src/
│   ├── RS_ThingSpeak.h
│   └── RS_ThingSpeak.cpp
├── keywords.txt
├── library.properties
├── LICENSE
└── README.md



## 🚀 Getting Started

### Install
1. Clone or download this repo into your Arduino `libraries/` folder.
2. Open Arduino IDE → Sketch → Include Library → Add .ZIP Library (if zipped).

### Usage

```cpp
#include <WiFi.h>
#include "RS_ThingSpeak.h"
#include "secrets.h"

RS_ThingSpeak ts;
ThingSpeakKeys keys;

void setup() {
  Serial.begin(115200);
  WiFi.begin(SECRET_SSID, SECRET_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  keys.writeApiKey   = "YOUR_WRITE_KEY";
  keys.readApiKey    = "YOUR_READ_KEY";
  keys.talkBackApiKey= "YOUR_TALKBACK_KEY";
  keys.talkBackID    = "YOUR_TALKBACK_ID";
  keys.channelID     = "YOUR_CHANNEL_ID";

  ts.begin(keys);

  // Example: Send to 2 fields
  int fields[2] = {1, 2};
  String values[2] = {"25.5", "60.2"};
  ts.sendData(fields, values, 2);
}

See examples/ for full sketches.

