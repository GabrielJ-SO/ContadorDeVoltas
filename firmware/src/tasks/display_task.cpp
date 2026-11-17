#include "pch.h"
#include "global.h"
#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

#include "tasks/display_task.h"

#define PANEL_RES_X 128 
#define PANEL_RES_Y  32
#define PANEL_CHAIN   4    

static MatrixPanel_I2S_DMA *dma_display = nullptr;

static TaskHandle_t xDisplayTaskHandle = NULL;

char* drawHeader();


void vDisplayTask(void *pvParameters)
{
    HUB75_I2S_CFG mxconfig(PANEL_RES_X, PANEL_RES_Y, PANEL_CHAIN);

    mxconfig.driver = HUB75_I2S_CFG::SHIFTREG;
    mxconfig.clkphase = false;

    dma_display = new MatrixPanel_I2S_DMA(mxconfig);
    if (!dma_display->begin())
        Serial.println("Error: Failed to setup display.");

    dma_display->setBrightness8(100);
    dma_display->clearScreen();

    dma_display->setTextSize(1);

    dma_display->setTextColor(dma_display->color565(250, 5, 5));

    dma_display->setCursor(0, 0);
    dma_display->print(drawHeader());
    
    dma_display->setTextColor(dma_display->color565(250, 140, 5));

    char trainingBuffer[50];

    for ( ; ; )
    {

        for (int i = 0; i < trainingPool.size; i++) {
            dma_display->setCursor(0, 9*(i+1));
            trainingPool.items[i].ops.display(&trainingPool.items[i], trainingBuffer, sizeof(trainingBuffer));
            dma_display->print(trainingBuffer);
        }
     
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    
}
void vStartDisplayTask() { xTaskCreatePinnedToCore(vDisplayTask, "DISPLAY_TASK", 8192, NULL, 2, &xDisplayTaskHandle, 1); }

char* drawHeader(){
    char headerBuffer[50];
    snprintf(headerBuffer, sizeof(headerBuffer), "Tmp Geral|vlt|Tmp vlt|rep");
    Serial.println(headerBuffer);

    return headerBuffer;
}