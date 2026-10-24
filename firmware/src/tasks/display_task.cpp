#include "pch.h"
#include "global.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

#include "tasks/display_task.h"

static TaskHandle_t xDisplayTaskHandle = NULL;

void drawHeader();


void vDisplayTask(void *pvParameters)
{
    char trainingBuffer[50];

    for ( ; ; )
    {
        //drawHeader(); 
        for (int i = 0; i < trainingPool.size; i++)
        {
            trainingPool.items[i].ops.display(&trainingPool.items[i], trainingBuffer, sizeof(trainingBuffer));
            Serial.println(trainingBuffer);
        }
     
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    
}
void vStartDisplayTask() { xTaskCreatePinnedToCore(vDisplayTask, "DISPLAY_TASK", 8192, NULL, 2, &xDisplayTaskHandle, 1); }

void drawHeader(){
    char headerBuffer[50];
    snprintf(headerBuffer, sizeof(headerBuffer), "Tmp Geral|vlt|Tmp vlt|rep");
    Serial.println(headerBuffer);
}