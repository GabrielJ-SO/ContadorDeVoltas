#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "display_task.h"


static TaskHandle_t xDisplayTaskHandle = NULL;


void vDisplayTask(void *pvParameters)
{


    
    for ( ; ; )
    {

    }
}


void vStartDisplayTask() { xTaskCreate(vDisplayTask, "DISPLAY_TASK", 512, NULL, 2, &xDisplayTaskHandle); }