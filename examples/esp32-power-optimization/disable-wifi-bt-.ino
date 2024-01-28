#include "WiFi.h"

#define WIFI_SSID "your-ssid"
#define WIFI_PW "your-pass"

void setup() {
    Serial.begin(115200);

    // --- Enable / disable Bluetooth ---
    // Start Bluetooth
    Serial.println("Starting Bluetooth");
    btStart();
    delay(5000);

    // Stop Bluetooth
    Serial.println("Stopping Bluetooth");
    btStop();
    delay(5000);
    // --- ---

    // --- Enable / disable WiFi ---
    // Start WiFi in Station (STA) Mode
    Serial.println("Starting WiFi in Station Mode");
    WiFi.begin(WIFI_SSID, WIFI_PW);
    delay(5000);

    // Disable WiFi
    Serial.println("Stopping WiFi");
    WiFi.mode(WIFI_OFF);
    delay(5000);
    // --- ---

    // --- Enable / Disable Both WiFi and Bluetooth
    // Enable WiFi and Bluetooth
    Serial.println("Starting Both WiFi and Bluetooth");
    btStart();
    WiFi.begin(WIFI_SSID, WIFI_PW);
    delay(5000);

    // Disable WiFi and Bluetooth
    Serial.println("Stopping Both WiFi and Bluetooth");
    WiFi.mode(WIFI_OFF);
    btStop();
    delay(5000);
    // --- ---
}

void loop() {

}
