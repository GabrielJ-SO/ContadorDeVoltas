#include "pch.h"

#include "tasks/rfid_task.h"

static TaskHandle_t xRFIDTaskHandle = NULL;

void vRFIDTask(void *pvParemeters)
{


    for ( ; ; )
    {

    }

}


void vStartRFIDTask() { xTaskCreatePinnedToCore(vRFIDTask, "RFID_TASK", 512, NULL, 3, &xRFIDTaskHandle, 0); }