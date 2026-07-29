#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "rfid_task.h"

static TaskHandle_t xRFIDTaskHandle = NULL;

void vRFIDTask(void *pvParemeters)
{


    
    for ( ; ; )
    {

    }

}


void vStartRFIDTask() { xTaskCreate(vRFIDTask, "RFID_TASK", 128, NULL, 3, &xRFIDTaskHandle); }