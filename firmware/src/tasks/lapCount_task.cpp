#include "pch.h"

#include "tasks/lapCount_task.h"

static TaskHandle_t xLapCountTaskHandle = NULL;

void vLapCountTask(void* pvParemeters)
{

    for ( ; ; )
    {

    }

}


void vStartLapCountTask() { xTaskCreatePinnedToCore(vLapCountTask, "LapCount_Task", 512, NULL, 3, &xLapCountTaskHandle, 1); }