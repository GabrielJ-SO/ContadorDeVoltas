#include "pch.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

#include "tasks/display_task.h"


static TaskHandle_t xDisplayTaskHandle = NULL;


void vDisplayTask(void *pvParameters)
{


    for ( ; ; )
    {

    }
}


void vStartDisplayTask() { xTaskCreatePinnedToCore(vDisplayTask, "DISPLAY_TASK", 512, NULL, 3, &xDisplayTaskHandle, 1); }