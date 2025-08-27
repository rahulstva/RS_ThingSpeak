#ifndef RS_THINGSPEAK_H
#define RS_THINGSPEAK_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

struct ThingSpeakKeys {
    String writeApiKey;
    String readApiKey;
    String talkBackApiKey;
    String talkBackID;
    String channelID;
};

class RS_ThingSpeak {
public:
    RS_ThingSpeak();
    void begin(const ThingSpeakKeys &keys);

    bool sendData(const int *fieldNumbers, const String *fieldValues, int fieldCount);
    bool readData(const int *fieldNumbers, String *fieldValues, int fieldCount);

    // ✅ Read specific TalkBack command by ID (without executing)
    bool readTalkBackCommandByID(const String &commandID, String &command);

private:
    ThingSpeakKeys _keys;
    String _baseURL;
};

#endif
