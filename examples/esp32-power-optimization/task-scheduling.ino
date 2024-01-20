#include <Arduino.h>
#include <esp_sleep.h> 

void mainTask() {
  // Mock Main Task code
  delay(500);
}

void secondaryTask() {
  // Mock Secondary Task code
  delay(1000);
}

void setup() {
  // Add your setup code here
}

void loop() {
  // Calculate the time until the next scheduled task or event
  unsigned long nextMainTaskTime = millis() + 500;
  unsigned long nextSecondaryTaskTime = millis() + 1000;

  // Determine the minimum time until the next task
  unsigned long nextTaskTime = min(nextMainTaskTime, nextSecondaryTaskTime);

  // Enter deep sleep to save power until the next task is scheduled
  esp_sleep_enable_timer_wakeup(nextTaskTime * 1000); // Convert to microseconds
  esp_deep_sleep_start();
}
