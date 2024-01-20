const uint32_t SLEEP_DURATION = 5 * 1000000; // µs

// ESP32 boot count
RTC_DATA_ATTR int bootCount = 0;

void printWakeUpReason() {
  esp_sleep_wakeup_cause_t wakeupReason = esp_sleep_get_wakeup_cause();

  switch (wakeupReason) {
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("The device was awakened by an external signal using RTC_IO.");
      break;
    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("The device was awakened by an external signal using RTC_CNTL.");
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("The device was awakened by a timer event.");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("The device was awakened by a touchpad interaction.");
      break;
    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("The device was awakened by a ULP (Ultra-Low-Power) program.");
      break;
    default:
      Serial.printf("The device woke up for an unknown reason: %d\n", wakeupReason);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000); // Wait a bit to make sure Serial starts

  // Print boot counter every boot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  // Print wake up reason
  printWakeUpReason();
}

// Enter Light Sleep with Timer Wake-up source
void lightSleep() {
    esp_sleep_enable_timer_wakeup(SLEEP_DURATION);
    esp_light_sleep_start();
}

// Enter Deep Sleep with Timer Wake-up source
void deepSleep() {
    esp_sleep_enable_timer_wakeup(SLEEP_DURATION);
    esp_deep_sleep_start();
}

// Enter Hibernation mode with Timer Wake-up source
void hibernate() {
    // Shut down RTC (Low Power) Peripherals
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH,   ESP_PD_OPTION_OFF);
    // Shut down RTC Slow Memory
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
    // Shut down RTC Fast Memory
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
    // Shut down Crystal Oscillator XTAL 
    esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL,         ESP_PD_OPTION_OFF);
    // Enter Deep Sleep
    deepSleep();
}

void loop() {
  Serial.println("Entering Light Sleep mode...");
  delay(1000);
  lightSleep();

  Serial.println("Entering Deep Sleep mode...");
  delay(1000);
  deepSleep();

  Serial.println("Entering Hibernation mode...");
  delay(1000);
  hibernate();
}
