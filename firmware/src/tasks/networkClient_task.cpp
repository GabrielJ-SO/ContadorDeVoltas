#include "pch.h"

#include "tasks/networkClient_task.h"
#include "global.h"

typedef struct Lap {
    long trainingId;
    unsigned long lapTime;
} Lap;

static TaskHandle_t xNetworkClientTaskHandle = NULL;

QueueHandle_t xLapQueue = NULL;

void vNetworkClientTask(void* pvParameters) 
{
    Lap lap;

    for ( ; ; )
    {
        if (xQueueReceive(xLapQueue, &lap, pdMS_TO_TICKS(250))) 
        {



        }
    }


}


void vStartNetworkClientTask() {
    xLapQueue = xQueueCreate(20, sizeof(Lap));
    xTaskCreatePinnedToCore(vNetworkClientTask, "NetClient_Task", 1024, NULL, 2, &xNetworkClientTaskHandle, 0);
}


bool sendLapToQueue(Lap lap, unsigned long awaitMS) {
    if (xLapQueue == NULL) { return false; }

    return xQueueSend(xLapQueue, &lap, pdMS_TO_TICKS(awaitMS)) == pdTRUE;
}


Lap createLap(long trainingID, unsigned long lapTime) {
    Lap lap = { trainingID, lapTime };
    return lap;
}