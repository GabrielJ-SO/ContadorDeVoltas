#include "pch.h"

#include "tasks/display_task.h"


static TaskHandle_t xDisplayTaskHandle = NULL;


void vDisplayTask(void *pvParameters)
{


    for ( ; ; )
    {

    }
}


void vStartDisplayTask() { xTaskCreatePinnedToCore(vDisplayTask, "DISPLAY_TASK", 512, NULL, 2, &xDisplayTaskHandle, 1); }