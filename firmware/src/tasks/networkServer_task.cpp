#include "pch.h"
#include "global.h"
#include "config.h"

#include "tasks/networkServer_task.h"     
#include <ESPAsyncWebServer.h>

#include "training/Training.h"


static TaskHandle_t xNetworkServerTaskHandle = NULL;


AsyncWebServer server(80);

void setTrainingRequests();

bool freePracticeRequest(AsyncWebServerRequest *request);
bool intervalTrainingRequest(AsyncWebServerRequest *request);
bool runningWorkoutRequest(AsyncWebServerRequest *request);
bool stopTrainingRequest(AsyncWebServerRequest *request);

void vNetworkServerTask(void* pvParameters) 
{
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    setTrainingRequests();
    server.begin();

    for ( ; ; )
    {   
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
void vStartNetworkServerTask() { xTaskCreatePinnedToCore(vNetworkServerTask, "NetServer_Task", 8192, NULL, 2, &xNetworkServerTaskHandle, 0); }


void setTrainingRequests() {

    server.on("/start/freePractice", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (freePracticeRequest(request))
            request->send(200, "text/plain charset=utf-8;", "Treino livre iniciado!");
        else
            request->send(500, "text/plain charset=utf-8;", "Não foi possível iniciar o treino livre.");
    });
    
    
    server.on("/start/intervalTraining", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (intervalTrainingRequest(request))
            request->send(200, "text/plain charset=utf-8;", "Treino intervalado iniciado!");
        else
            request->send(500, "text/plain charset=utf-8;", "Não foi possível iniciar o treino intervalado.");
    });

   
    server.on("/start/runningWorkout", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (runningWorkoutRequest(request))
            request->send(200, "text/plain charset=utf-8;", "Treino corrida iniciado!");
        else
            request->send(500, "text/plain charset=utf-8;", "Não foi possível iniciar o treino corrida.");
    });


    server.on("/stop/training", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (stopTrainingRequest(request))
            request->send(200, "text/plain charset=utf-8;", "Treino Finalizado!");
        else
            request->send(500, "text/plain charset=utf-8;", "Não foi possível finalizar o treino.");

    });


    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain; charset=utf-8;", "Rota não encontrada");
    });
}


bool freePracticeRequest(AsyncWebServerRequest *request) {
    if (request->hasParam("id") && request->hasParam("tag")) 
    {
        long trainingID = request->getParam("id")->value().toInt();
        auto str        = request->getParam("tag");

        if (str != nullptr) {
            std::string athleteTag(str->value().c_str());
            if (startFreePractice(trainingID, athleteTag)) return true;
        }
        
    }
   
    return false;
}


bool intervalTrainingRequest(AsyncWebServerRequest *request) {
    if (request->hasParam("id") && request->hasParam("tag") && request->hasParam("numInt") && request->hasParam("numLap") && request->hasParam("restTime")) 
    {
        long trainingID        = request->getParam("id")->value().toInt();
        auto str               = request->getParam("tag");
        int numberOfIntervals  = request->getParam("numInt")->value().toInt();
        int numLap             = request->getParam("numLap")->value().toInt();
        unsigned long restTime = request->getParam("restTime")->value().toInt();

        if (str != nullptr) {
            std::string athleteTag(str->value().c_str());
            if (startIntervalTraining(trainingID, athleteTag, restTime, numberOfIntervals, numLap)) return true;
        }
        
    }

    return false;
}

bool runningWorkoutRequest(AsyncWebServerRequest *request) {
    if (request->hasParam("id") && request->hasParam("tag") && request->hasParam("numLap"))
    {
        long id    = request->getParam("id")->value().toInt();
        auto str   = request->getParam("tag");
        int numLap = request->getParam("numLap")->value().toInt();
        

        if (str != nullptr) {
            std::string athleteTag(str->value().c_str());
            if (startRunningWorkout(id, athleteTag, numLap))  return true; 
        }
       
    }
        
    return false;
}


bool stopTrainingRequest(AsyncWebServerRequest *request) {
    if (request->hasParam("id")) 
    {   
        long id = request->getParam("id")->value().toInt();
        if (completeTraining(id)) return true;
    }
    
    return false;
}


void initWiFi() {

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(false);

    if (!WiFi.config(LOCAL_IP, GATEWAY, SUBNET, GATEWAY))
        Serial.println("Failed to configure a static IP");

    WiFi.begin(WIFI_SSID, WIFI_PASS);   
}