#include <stdio.h>

#include "esp_log.h"

#include "testable.h"

#define TAG "main"

void app_main(void)
{
    ESP_LOGI(TAG, "running passes func...");
    passesFunc();

    ESP_LOGI(TAG, "running fails func...");
    failsFunc();
}