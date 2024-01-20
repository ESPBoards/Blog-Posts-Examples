#include <driver/rmt.h>

// Set the RMT channel number
#define RMT_CHANNEL 0

// Define the IR signal in an array of durations in microseconds
const uint16_t irSignal[] = {8000, 4500, 500, 550, 500, 550, 500, 550, 500, 1600, 500, 1600, 500, 1600, 500, 1600, 500, 550, 500, 550, 500, 550, 500, 1600, 500, 1600, 500, 1600, 500, 1600, 500, 1600, 500, 1600, 500, 1600, 500, 1600, 500, 550, 500, 550, 500, 550, 500, 1600, 500, 1600, 500, 550, 500, 550, 500, 550, 500, 550};

void setup() {
  // Configure the RMT peripheral
  rmt_config_t config;
  config.gpio_num = GPIO_NUM_4;
  config.rmt_mode = RMT_MODE_CARRIER;
  config.channel = RMT_CHANNEL;
  config.clk_div = 80;

  // Initialize the RMT peripheral
  rmt_config(&config);
  rmt_driver_install(config.channel, 0, 0);

  // Start the carrier signal
  rmt_carrier_mode_start(RMT_CHANNEL, 1, true, &carrier_config);
}

void loop() {
  // Send the IR signal
  rmt_write_items(RMT_CHANNEL, irSignal, sizeof(irSignal) / sizeof(irSignal[0]), true);

  // Wait a bit before sending the next signal
  vTaskDelay(pdMS_TO_TICKS(500));
}
