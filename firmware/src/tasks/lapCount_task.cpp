#include "pch.h"
#include "global.h"

#include "tasks/lapCount_task.h"

#define TAG_SIZE 25

static TaskHandle_t xLapCountTaskHandle = NULL;

static QueueHandle_t xRfidTagQueue = NULL;

void vLapCountTask(void* pvParemeters)
{
    std::string tag;

    for ( ; ; )
    {   

        if (xQueueReceive(xRfidTagQueue, &tag, portMAX_DELAY))
        {
            std::string athleteTag;
            for (int i = 0; i < trainingPool.size; i++) {
                athleteTag = trainingPool.items[i].athleteTag;
                if (athleteTag == tag) {
                    trainingPool.items[i].ops.lapCounting(&trainingPool.items[i]);
                }  
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
void vStartLapCountTask() {
    xRfidTagQueue = xQueueCreate(20, TAG_SIZE);
    xTaskCreatePinnedToCore(vLapCountTask, "LapCount_Task", 4096, NULL, 3, &xLapCountTaskHandle, 1);
}

bool sendTagToRfidQueue(std::string tag, unsigned long awaitMS) {
    if (xRfidTagQueue == NULL) { return false; }

    return xQueueSend(xRfidTagQueue, &tag, pdMS_TO_TICKS(awaitMS)) == pdTRUE;
}

