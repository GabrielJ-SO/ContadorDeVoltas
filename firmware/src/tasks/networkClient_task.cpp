#include "pch.h"

#include "tasks/networkClient_task.h"

static TaskHandle_t xNetworkClientTaskHandle = NULL;

void vNetworkClientTask(void* pvParameters) 
{

    for ( ; ; )
    {

    }


}


void vStartNetworkClientTask() { xTaskCreatePinnedToCore(vNetworkClientTask, "NetClient_Task", 1024, NULL, 2, &xNetworkClientTaskHandle, 0); }