#include <WiFi.h>
#include "RS_ThingSpeak.h"
#include "secrets.h"   // Only WiFi + Write API Key here

RS_ThingSpeak tsClient;   // Create ThingSpeak client

void setup() {
  Serial.begin(115200);

  // Connect WiFi
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // Initialize ThingSpeak with just the write key
  ThingSpeakKeys keys;
  keys.writeApiKey = SECRET_WRITE_APIKEY;  
  tsClient.begin(keys);
}

void loop() {
  // Example: dummy sensor data, 
  float temperature = random(200, 300) / 10.0; // 20.0 – 30.0
  float humidity    = random(400, 600) / 10.0; // 40.0 – 60.0

  int fields[2] = {1, 2};
  String values[2] = {String(temperature), String(humidity)};

  Serial.println("Sending data to ThingSpeak...");
  bool success = tsClient.sendData(fields, values, 2);

  if (success) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.println("Failed to send data.");
  }

  delay(20000); // ThingSpeak free account: min 15s interval
}
