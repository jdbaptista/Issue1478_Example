/**
 * testable.c
 * 
 * Contains functions whose return value is tested and log their return value
 * CONFIG_NUM_REPEAT times.
 */

#include "testable.h"

#include "esp_log.h"
#include "sdkconfig.h"

#define TAG "testable"

/**
 * Returns the number 17 and logs 17 CONFIG_NUM_REPEAT times.
 */
int passesFunc(void)
{
    int number = 17;

    for (int i = 0; i < CONFIG_NUM_REPEAT; i++)
    {
        ESP_LOGI(TAG, "%d", number);
    }
    
    return number;
}

/**
 * Returns the number 32 and logs 32 CONFIG_NUM_REPEAT_TIMES.
 */
int failsFunc(void)
{
    int number = 32;

    for (int i = 0; i < CONFIG_NUM_REPEAT; i++)
    {
        ESP_LOGI(TAG, "%d", number);
    }
    
    return number + 2;
}