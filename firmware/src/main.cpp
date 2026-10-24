#include "pch.h"
#include "global.h"

#include "tasks/rfid_task.h"
#include "tasks/display_task.h"
#include "tasks/lapCount_task.h"
#include "tasks/networkClient_task.h"
#include "tasks/networkServer_task.h"

#include "training/TrainingPool.h"

const uint8_t CMD_MULTI_POLL[]  = {0xAA, 0x00, 0x27, 0x00, 0x03, 0x22, 0xFF, 0xFF, 0x4A, 0xDD};

void setup() {
    Serial.begin(115200);

    Serial2.begin(115200, SERIAL_8N1, RFID_RX_PIN, RFID_TX_PIN);
    Serial2.onReceive(notifyRFID, true);
    delay(500);
    Serial2.write(CMD_MULTI_POLL, sizeof(CMD_MULTI_POLL));

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

