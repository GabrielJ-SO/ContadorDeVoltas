#include "pch.h"

#include "tasks/rfid_task.h"
#include "tasks/lapCount_task.h"

static TaskHandle_t xRFIDTaskHandle = NULL;

void vRFIDTask(void *pvParemeters)
{


    for ( ; ; )
    {
        
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}


void vStartRFIDTask() { xTaskCreatePinnedToCore(vRFIDTask, "RFID_TASK", 512, NULL, 5, &xRFIDTaskHandle, 0); }