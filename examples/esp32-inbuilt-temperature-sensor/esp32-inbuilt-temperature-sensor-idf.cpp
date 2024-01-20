#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/temperature_sensor.h"

static const char *LOG_TAG = "ESP32";

void app_main(void)
{
    ESP_LOGI(LOG_TAG, "Setup the internal temperature sensor, set min/max values to -10 ~ 80 °C");
    temperature_sensor_handle_t temp_handle = NULL;
    temperature_sensor_config_t temp_sensor = {
        .range_min = -10,
        .range_max = 80,
    };
    ESP_ERROR_CHECK(temperature_sensor_install(&temp_sensor, &temp_handle));

    ESP_ERROR_CHECK(temperature_sensor_enable(temp_sensor));

    float tsens_out;
    ESP_LOGI(LOG_TAG, "Get converted data from internal temperature sensor");
    ESP_ERROR_CHECK(temperature_sensor_get_celsius(temp_handle, &tsens_out));
    ESP_LOGI(LOG_TAG, "Temperature value %.02f °C", tsens_value);

    ESP_LOGI(LOG_TAG, "Disabling internal temperature sensor to save power");
    ESP_ERROR_CHECK(temperature_sensor_disable(temp_handle));
}
