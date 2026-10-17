#include "pch.h"

#include "tasks/networkClient_task.h"
#include "HTTPClient.h"
#include "global.h"

static const char*         API_URL       = "";
static const unsigned long HTTP_TIMEOUT  = 3000;
static const unsigned long RETRY_MIN_MS  = 500;
static const unsigned long RETRY_MAX_MS  = 10000;

typedef struct Lap {
    long trainingID;
    unsigned long lapTime;
} Lap;

enum class SendResult {
    OK,
    RETRY,
    DROP
};

static TaskHandle_t xNetworkClientTaskHandle = NULL;
QueueHandle_t xLapQueue = NULL;

SendResult postLap(Lap &lap);

void vNetworkClientTask(void* pvParameters) 
{
    Lap lap;

    for ( ; ; )
    {   

        Serial.println("CLIENT (CORE 0)");
        xQueueReceive(xLapQueue, &lap, portMAX_DELAY);

        unsigned long backoff = RETRY_MIN_MS;

/*         for ( ; ; )
        {
            SendResult result = postLap(lap);

            if (result == SendResult::OK)
                break;

            if (result == SendResult::DROP) {
                Serial.printf("Volta descartada (training %ld)\n", lap.trainingID);
                break;
            }

            if (backoff >= RETRY_MAX_MS)
                break;

            vTaskDelay(pdMS_TO_TICKS(backoff));
            backoff = min(backoff * 2, RETRY_MAX_MS);
        }*/

        vTaskDelay(pdMS_TO_TICKS(10));
    } 

}
void vStartNetworkClientTask() {
    xLapQueue = xQueueCreate(50, sizeof(Lap));
    xTaskCreatePinnedToCore(vNetworkClientTask, "NetClient_Task", 8192, NULL, 3, &xNetworkClientTaskHandle, 0);
}


bool sendLapToQueue(Lap lap, unsigned long awaitMS) {
    if (xLapQueue == NULL) { return false; }

    return xQueueSend(xLapQueue, &lap, pdMS_TO_TICKS(awaitMS)) == pdTRUE;
}


Lap createLap(long trainingID, unsigned long lapTime) {
    Lap lap = { trainingID, lapTime };
    return lap;
}

SendResult postLap(Lap &lap) {

    if (WiFi.status() != WL_CONNECTED)
        return SendResult::RETRY;

    char body[96];
    snprintf(body, sizeof(body),
             "{\"trainingID\":%ld,\"lapTime\":%lu}",
             lap.trainingID, lap.lapTime);

    WiFiClient client;
    HTTPClient http;
    http.setConnectTimeout(HTTP_TIMEOUT);
    http.setTimeout(HTTP_TIMEOUT);

    if (!http.begin(client, API_URL))
        return SendResult::RETRY;

    http.addHeader("Content-Type", "application/json");
    int code = http.POST((uint8_t*)body, strlen(body));
    http.end();

    if (code >= 200 && code < 300) return SendResult::OK;
    if (code >= 400 && code < 500) return SendResult::DROP;
    return SendResult::RETRY;                                  
}