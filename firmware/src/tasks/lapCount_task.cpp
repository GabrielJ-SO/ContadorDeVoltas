#include "pch.h"

#include "tasks/lapCount_task.h"

static TaskHandle_t xLapCountTaskHandle = NULL;

static QueueHandle_t xRfidTagQueue = NULL;

void vLapCountTask(void* pvParemeters)
{
    long tag = 0;

    for ( ; ; )
    {
        if (xQueueReceive(xRfidTagQueue, &tag, 500))
        {

        }
    }

}

void vStartLapCountTask() {
    xRfidTagQueue = xQueueCreate(20, sizeof(long));
    xTaskCreatePinnedToCore(vLapCountTask, "LapCount_Task", 1024, NULL, 3, &xLapCountTaskHandle, 1); 
}

bool sendTagToRfidQueue(long tag, unsigned long awaitMS) {
    if (xRfidTagQueue == NULL) { return false; }

    return xQueueSend(xRfidTagQueue, &tag, pdMS_TO_TICKS(awaitMS)) == pdTRUE;
}

