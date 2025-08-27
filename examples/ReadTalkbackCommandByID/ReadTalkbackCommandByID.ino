#include <WiFi.h>
#include "RS_ThingSpeak.h"
#include "secrets.h"

RS_ThingSpeak ts;
ThingSpeakKeys keys;

void setup() {
  Serial.begin(115200);
  WiFi.begin(SECRET_SSID, SECRET_PASS);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  keys.talkBackApiKey = SECRET_TALKBACK_APIKEY;
  keys.talkBackID  = SECRET_TALKBACK_ID;

  ts.begin(keys);
  
}

void loop() {
  String cmd;
  if (ts.readTalkBackCommandByID(SECRET_COMMAND_ID, cmd)) {
    if (cmd != "") {
      Serial.print("Command string is: ");
      Serial.println(cmd);
    } else {
      Serial.println("Command not found or empty.");
    }
  }
  delay(2000);
}