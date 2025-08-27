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


## 🔧 Installation
1. Download the library as ZIP or clone the repo.  
2. In Arduino IDE: `Sketch` → `Include Library` → `Add .ZIP Library...`  
3. Select the ZIP.  

## 🚀 Usage
Include in your sketch:
```cpp
#include <WiFi.h>
#include <RS_ThingSpeak.h>
#include "secrets.h"


Provide your credentials in secrets.h (only the ones you need):
const char* WIFI_SSID     = "your-ssid";
const char* WIFI_PASSWORD = "your-password";
const char* WRITE_API_KEY = "your-write-api-key";   // For sending
const char* READ_API_KEY  = "your-read-api-key";    // For reading
const char* TALKBACK_API_KEY = "your-talkback-api-key"; // For TalkBack
const char* TALKBACK_ID      = "your-talkback-id";
const char* CHANNEL_ID       = "your-channel-id";

See examples inside the examples/ folder.
