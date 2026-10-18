#include "pch.h"
#include "global.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

#include "tasks/display_task.h"

//#include "training/TrainingPool.h"

static TaskHandle_t xDisplayTaskHandle = NULL;


void vDisplayTask(void *pvParameters)
{
    char trainingBuffer[50];
    Training training;


    for ( ; ; )
    {
        // Serial.println("DISPLAY (CORE 1)");
        snprintf(trainingBuffer, sizeof(trainingBuffer), "Tmp Geral|vlt|Tmp vlt|rep");
        Serial.println(trainingBuffer);
        for (int i = 0; i < trainingPool.amount; i++)
        {   
            if (xSemaphoreTake(xTrainingPoolMutex, portMAX_DELAY) == pdTRUE)
            {   
                training = trainingPool.pool[i];
                xSemaphoreGive(xTrainingPoolMutex);
            }

            training.ops.display(&trainingPool.pool[i], trainingBuffer, sizeof(trainingBuffer));
            Serial.println(trainingBuffer);
        } 
        
        
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    
}
void vStartDisplayTask() { xTaskCreatePinnedToCore(vDisplayTask, "DISPLAY_TASK", 4096, NULL, 3, &xDisplayTaskHandle, 1); }