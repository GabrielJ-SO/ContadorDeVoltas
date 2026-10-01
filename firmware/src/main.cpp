#include "pch.h"

#include "tasks/rfid_task.h"
#include "tasks/display_task.h"
#include "tasks/lapCount_task.h"
#include "tasks/networkClient_task.h"
#include "tasks/networkServer_task.h"

#include "training/TrainingPool.h"
#include "global.h"

void setup() {
    Serial.begin(115200);

    initializePool(&trainingPool);

    vStartRFIDTask();
    vStartDisplayTask();
    vStartLapCountTask();
    vStartNetworkClientTask();
    vStartNetworkServerTask();

    vTaskStartScheduler();
}

void loop() {
  
}

