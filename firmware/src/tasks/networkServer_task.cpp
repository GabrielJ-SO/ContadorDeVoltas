#include "pch.h"

#include "tasks/networkServer_task.h"
#include "WiFi.h"       
#include <ESPAsyncWebServer.h>

#include "training/Training.h"


static TaskHandle_t xNetworkServerTaskHandle = NULL;


AsyncWebServer server(80);

const char ssid[] = "";
const char pass[] = "";

IPAddress local_IP(192, 168, 1, 150);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setTrainingRequests();

bool freePracticeRequest(AsyncWebServerRequest *request);
bool intervalTrainingRequest(AsyncWebServerRequest *request);
bool runningWorkoutRequest(AsyncWebServerRequest *request);

void vNetworkServerTask(void* pvParameters) 
{
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    setTrainingRequests();
    server.begin();
    
    server.begin();

    for ( ; ; )
    {   
        Serial.println("SERVER (CORE 0)");

        Serial.printf("Wifi Status: %d\n", WiFi.status());
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
void vStartNetworkServerTask() { xTaskCreatePinnedToCore(vNetworkServerTask, "NetServer_Task", 8192, NULL, 1, &xNetworkServerTaskHandle, 0); }


void setTrainingRequests() {

    // http://192.168.1.150/start/freePractice?id=trainingID&tag=atheleteTag
    server.on("/start/freePractice", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (freePracticeRequest(request))
            request->send(200, "text/plain charset=utf-8;", "Treino livre iniciado!");
        else
            request->send(500, "text/plain charset=utf-8;", "Não foi possível iniciar o treino livre.");
    });
    
    // http://192.168.1.150/start/intervalTraining?id=trainingID&tag=atheleteTag&numInt=numberOfIntervals&numLap=numberOfLaps&restTime=restTime
    server.on("/start/intervalTraining", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (intervalTrainingRequest(request))
            request->send(200, "text/plain charset=utf-8;", "Treino intervalado iniciado!");
        else
            request->send(500, "text/plain charset=utf-8;", "Não foi possível iniciar o treino intervalado.");
    });

    // http://192.168.1.150/start/runningWorkout?id=trainingID&tag=atheleteTag&numLap=numberOfLaps
    server.on("/start/runningWorkout", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (runningWorkoutRequest(request))
            request->send(200, "text/plain charset=utf-8;", "Treino corrida iniciado!");
        else
            request->send(500, "text/plain charset=utf-8;", "Não foi possível iniciar o treino corrida.");
    });


    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain; charset=utf-8;", "Rota não encontrada");
    });
}


bool freePracticeRequest(AsyncWebServerRequest *request) {

    if (request->hasParam("id") && request->hasParam("tag")) 
    {
        long trainingID = request->getParam("id")->value().toInt();
        long atheleteTag = request->getParam("tag")->value().toInt();

        if (startFreePractice(trainingID, atheleteTag))
            return true;
        else
            return false;
    }
    else 
    {
        return false;
    }

}


bool intervalTrainingRequest(AsyncWebServerRequest *request) {
    // TODO
    return false;
}

bool runningWorkoutRequest(AsyncWebServerRequest *request) {
    if (request->hasParam("id") && request->hasParam("tag") && request->hasParam("numLap"))
    {
        long id = request->getParam("id")->value().toInt();
        long tag = request->getParam("tag")->value().toInt();
        int numLap = request->getParam("numLap")->value().toInt();

        if (startRunningWorkout(id, tag, numLap))
            return true;
        else
            return false;
    }
        
    return false;
}

void initWiFi() {

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.setAutoReconnect(true);   // sem reconnect() manual
    WiFi.persistent(false);

    if (!WiFi.config(local_IP, gateway, subnet, gateway))
        Serial.println("Failed to configure a static IP");

    WiFi.begin(ssid, pass);        // não bloqueia
}