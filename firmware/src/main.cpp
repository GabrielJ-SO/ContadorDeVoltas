#include "pch.h"
#include "global.h"

#include "tasks/rfid_task.h"
#include "tasks/display_task.h"
#include "tasks/lapCount_task.h"
#include "tasks/networkClient_task.h"
#include "tasks/networkServer_task.h"

#include "training/TrainingPool.h"


void setup() {
    Serial.begin(115200);
    // Serial2.begin(115200, SERIAL_8N1, RFID_RX_PIN, RFID_TX_PIN);
    initializePool(&trainingPool);
    xTrainingPoolMutex = xSemaphoreCreateMutex();
   
    initWiFi();

    vStartNetworkServerTask();
    vStartRFIDTask();
    vStartDisplayTask();
    vStartLapCountTask();
    vStartNetworkClientTask();
    
    Serial.println("Running...");

}

void loop() {
    vTaskDelay(portMAX_DELAY);
}

