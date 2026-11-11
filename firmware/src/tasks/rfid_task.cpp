#include "pch.h"

#include "tasks/rfid_task.h"
#include "tasks/lapCount_task.h"

#define NUM_TAGS 4

static TaskHandle_t xRFIDTaskHandle = NULL;
static uint8_t lastEpc[12];
const uint32_t DEBOUNCE_MS = 15000;

void handleTag(const uint8_t *epc);

typedef struct Tag {
    std::string id;
    uint32_t lastSeen;
} Tag;

static Tag tagList[NUM_TAGS];

void initializeTagList();

void vRFIDTask(void *pvParemeters)
{
    static uint8_t buf[64];
    static size_t  idx = 0;

    initializeTagList();

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


bool checkTag(std::string tag) {
    uint32_t now = millis();

    for (int i = 0; i < NUM_TAGS; i++) {
        if ((tagList[i].id == tag) && (now - tagList[i].lastSeen) > DEBOUNCE_MS)
        {   
            tagList[i].lastSeen = now;
            return true;
        }
    }

    return false;
}

void handleTag(const uint8_t *epc) {

    char hex[25];
    for (int i = 0; i < 12; i++) sprintf(&hex[i * 2], "%02X", epc[i]);
    hex[24] = '\0';
    std::string tag(hex, 24);

    if (checkTag(tag)) sendTagToRfidQueue(tag, 100);

    Serial.println(tag.c_str());
}

void initializeTagList() {
    for (int i = 0; i < NUM_TAGS; i++) {
        tagList[i].id       = "";
        tagList[i].lastSeen =  0;
    }
}

void addTag(std::string tag) {
    for (int i = 0; i < NUM_TAGS; i++) {
        if (tagList[i].id == "") {
            tagList[i].id = tag;
            return;
        }
            
    }
}

void removeTag(std::string tag) {
    for (int i = 0; i < NUM_TAGS; i++) {
        if (tagList[i].id == tag) {
            tagList[i].id       = "";
            tagList[i].lastSeen =  0;
            return;
        }
            
    }
}

void notifyRFID() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (xRFIDTaskHandle != NULL) xTaskNotifyGive(xRFIDTaskHandle);
}
