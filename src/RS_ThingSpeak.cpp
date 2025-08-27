#include "RS_ThingSpeak.h"

RS_ThingSpeak::RS_ThingSpeak() {
    _keys.writeApiKey = "";
    _keys.readApiKey = "";
    _keys.talkBackApiKey = "";
    _keys.talkBackID = "";
    _keys.channelID = "";
    _baseURL = "https://api.thingspeak.com";
}

void RS_ThingSpeak::begin(const ThingSpeakKeys &keys) {
    _keys = keys;
}

// ----------- SEND DATA -----------
bool RS_ThingSpeak::sendData(const int *fieldNumbers, const String *fieldValues, int fieldCount) {
    if (_keys.writeApiKey == "") {
        Serial.println("Error: Write API Key not set.");
        return false;
    }

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = _baseURL + "/update?api_key=" + _keys.writeApiKey;

        for (int i = 0; i < fieldCount; i++) {
            url += "&field" + String(fieldNumbers[i]) + "=" + fieldValues[i];
        }

        http.begin(url);
        int httpResponseCode = http.GET();

        Serial.print("Final URL: ");
        Serial.println(url);
        Serial.print("Response code: ");
        Serial.println(httpResponseCode);

        http.end();
        return (httpResponseCode == 200);
    }
    Serial.println("WiFi not connected.");
    return false;
}

// ----------- READ DATA -----------
bool RS_ThingSpeak::readData(const int *fieldNumbers, String *fieldValues, int fieldCount) {
    if (_keys.readApiKey == "" || _keys.channelID == "") {
        Serial.println("Error: Read API Key or Channel ID not set.");
        return false;
    }

    if (WiFi.status() == WL_CONNECTED) {
        for (int i = 0; i < fieldCount; i++) {
            HTTPClient http;
            String url = _baseURL + "/channels/" + _keys.channelID +
                         "/fields/" + String(fieldNumbers[i]) +
                         "/last.json?api_key=" + _keys.readApiKey;

            Serial.print("Requesting: ");
            Serial.println(url);

            http.begin(url);
            int httpResponseCode = http.GET();

            if (httpResponseCode == 200) {
                String payload = http.getString();
                Serial.print("Payload: ");
                Serial.println(payload);

                // Parse JSON
                DynamicJsonDocument doc(256);
                DeserializationError error = deserializeJson(doc, payload);
                if (!error) {
                    String fieldName = "field" + String(fieldNumbers[i]);
                    fieldValues[i] = doc[fieldName].as<String>();
                    Serial.print("Field ");
                    Serial.print(fieldNumbers[i]);
                    Serial.print(": ");
                    Serial.println(fieldValues[i]);
                } else {
                    Serial.println("JSON parse error");
                    fieldValues[i] = "";
                }
            } else {
                Serial.print("HTTP Error code: ");
                Serial.println(httpResponseCode);
                fieldValues[i] = "";
            }
            http.end();
        }
        return true;
    }
    Serial.println("WiFi not connected.");
    return false;
}

// ----------- READ SPECIFIC TALKBACK COMMAND -----------
bool RS_ThingSpeak::readTalkBackCommandByID(const String &commandID, String &command) {
    if (_keys.talkBackApiKey == "" || _keys.talkBackID == "") {
        Serial.println("Error: TalkBack API Key or ID not set.");
        return false;
    }

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = _baseURL + "/talkbacks/" + _keys.talkBackID +
                     "/commands/" + commandID + ".json?api_key=" + _keys.talkBackApiKey;

        Serial.print("Requesting TalkBack Command ID: ");
        Serial.println(url);

        http.begin(url);
        int httpResponseCode = http.GET();

        if (httpResponseCode == 200) {
            String payload = http.getString();
            Serial.print("Payload: ");
            Serial.println(payload);

            DynamicJsonDocument doc(512);
            DeserializationError error = deserializeJson(doc, payload);

            if (!error) {
                command = doc["command_string"].as<String>();
                Serial.print("TalkBack Command[");
                Serial.print(commandID);
                Serial.print("]: ");
                Serial.println(command);
                http.end();
                return true;
            } else {
                Serial.println("JSON parse error");
                command = "";
            }
        } else {
            Serial.print("HTTP Error code: ");
            Serial.println(httpResponseCode);
            command = "";
        }
        http.end();
        return false;
    }
    Serial.println("WiFi not connected.");
    return false;
}