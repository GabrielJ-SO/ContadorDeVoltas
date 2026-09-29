#include "pch.h"

#include "tasks/networkServer_task.h"

static TaskHandle_t xNetworkServerTaskHandle = NULL;

void vNetworkServerTask(void* pvParameters) 
{

    for ( ; ; )
    {

    }


}


void vStartNetworkServerTask() { xTaskCreatePinnedToCore(vNetworkServerTask, "NetServer_Task", 1024, NULL, 1, &xNetworkServerTaskHandle, 0); }