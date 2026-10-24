#include "pch.h"

#include "tasks/rfid_task.h"
#include "tasks/lapCount_task.h"
#include "FmtLib.h"

static TaskHandle_t xRFIDTaskHandle = NULL;
static uint8_t lastEpc[12];
static uint32_t lastSeen = 0;
const uint32_t DEBOUNCE_MS = 1000;

void handleTag(const uint8_t *epc);

void vRFIDTask(void *pvParemeters)
{
    static uint8_t buf[64];
    static size_t idx = 0;

    for ( ; ; )
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        while (Serial2.available()) 
        {
            uint8_t b = Serial2.read();
            if (idx == 0 && b != 0xAA) continue;
            if (idx < sizeof(buf)) buf[idx++] = b;
            else { idx = 0; continue; }

            if (b == 0xDD) {
                if (idx >= 20 && buf[1] == 0x02 && buf[2] == 0x22) {
                    handleTag(&buf[8]);
                }
                idx = 0;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    
}

void vStartRFIDTask() { xTaskCreatePinnedToCore(vRFIDTask, "RFID_TASK", 4096, NULL, 5, &xRFIDTaskHandle, 0); }

void handleTag(const uint8_t *epc) {
    uint32_t now = millis();
    if (memcmp(epc, lastEpc, 12) == 0 && (now - lastSeen) < DEBOUNCE_MS) {
        lastSeen = now;  
        return;
    }
    memcpy(lastEpc, epc, 12);
    lastSeen = now;
  
    std::string tag = fmt::format("{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}", 
                                    epc[0], epc[1], epc[2], epc[3], epc[4], epc[5], epc[6], epc[7], epc[8], epc[9], epc[10], epc[11]);

    sendTagToRfidQueue(tag, 100);
}

void notifyRFID() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (xRFIDTaskHandle != NULL) xTaskNotifyGive(xRFIDTaskHandle);
}
