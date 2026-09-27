#include "pch.h"

#include "tasks/network_task.h"

static TaskHandle_t xNetwoekTaskHandle = NULL;


void vNetworkTask(void* pvParameters) 
{

    for ( ; ; )
    {

    }


}


void vStartNetworkTask() { xTaskCreatePinnedToCore(vNetworkTask, "Net_Task", 1024, NULL, 2, &xNetwoekTaskHandle, 0); }