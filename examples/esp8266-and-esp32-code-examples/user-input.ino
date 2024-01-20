#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
  Serial.println("Please enter a message:");
}

void loop() {
  if (Serial.available()) {
    String message = Serial.readString();
    Serial.println("You entered: " + message);
  }
}
