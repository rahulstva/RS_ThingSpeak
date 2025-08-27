#include <WiFi.h>
#include "RS_ThingSpeak.h"
#include "secrets.h"   // Your WiFi + ThingSpeak credentials

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

  // Initialize only read keys
  keys.channelID   = SECRET_CHANNEL_ID;
  keys.readApiKey  = SECRET_READ_APIKEY;


  ts.begin(keys);
}

void loop() {
  int fields[] = {1, 2};
  String values[2];

  if (ts.readData(fields, values, 2)) {
    Serial.println("Latest Data:");
    for (int i = 0; i < 2; i++) {
      Serial.print("Field ");
      Serial.print(fields[i]);
      Serial.print(": ");
      Serial.println(values[i]);
    }
  }
  delay(15000); // ThingSpeak limit
}
