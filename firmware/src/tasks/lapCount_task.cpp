#include "pch.h"

#include "tasks/lapCount_task.h"

static TaskHandle_t xLapCountTaskHandle = NULL;

static QueueHandle_t xRfidTagQueue = NULL;

void vLapCountTask(void* pvParemeters)
{
    std::string tag;

    for ( ; ; )
    {   

        if (xQueueReceive(xRfidTagQueue, &tag, portMAX_DELAY))
        {
            Serial.println(tag.c_str());
        }
        
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
void vStartLapCountTask() {
    xRfidTagQueue = xQueueCreate(20, sizeof(long));
    xTaskCreatePinnedToCore(vLapCountTask, "LapCount_Task", 4096, NULL, 3, &xLapCountTaskHandle, 1); 
}

bool sendTagToRfidQueue(std::string tag, unsigned long awaitMS) {
    if (xRfidTagQueue == NULL) { return false; }

    return xQueueSend(xRfidTagQueue, &tag, pdMS_TO_TICKS(awaitMS)) == pdTRUE;
}

