#include "pch.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

#include "tasks/display_task.h"


static TaskHandle_t xDisplayTaskHandle = NULL;


void vDisplayTask(void *pvParameters)
{


    for ( ; ; )
    {
        Serial.println("DISPLAY (CORE 1)");
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    
}
void vStartDisplayTask() { xTaskCreatePinnedToCore(vDisplayTask, "DISPLAY_TASK", 4096, NULL, 3, &xDisplayTaskHandle, 1); }