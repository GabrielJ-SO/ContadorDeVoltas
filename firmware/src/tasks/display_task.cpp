#include "pch.h"
#include "global.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

#include "tasks/display_task.h"

//#include "training/TrainingPool.h"

static TaskHandle_t xDisplayTaskHandle = NULL;

void drawHeader();


void vDisplayTask(void *pvParameters)
{
    char trainingBuffer[50];
    Training training;


    for ( ; ; )
    {
        // Serial.println("DISPLAY (CORE 1)");
   
            drawHeader();
            for (int i = 0; i < MAX_TRAINING_SIMULTANEOUS; i++)
            {   
                if (xSemaphoreTake(xTrainingPoolMutex, 10) == pdTRUE)
                {   

                    if (trainingPool.items[i].type != FREE_SLOT)
                    {
                        training = trainingPool.items[i];
                        xSemaphoreGive(xTrainingPoolMutex);
                        training.ops.display(&training, trainingBuffer, sizeof(trainingBuffer));
                        Serial.println(trainingBuffer);
                    }
                    else {
                        xSemaphoreGive(xTrainingPoolMutex);
                    }
            
                }
                
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