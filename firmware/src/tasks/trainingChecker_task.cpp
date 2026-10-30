
#include "pch.h"
#include "global.h"

#include "tasks/trainingChecker_task.h"

static xTaskHandle xTrainingCheckerHandle = NULL;

bool canComplete(Training *t);

void vTrainingCheckerTask(void *pvParameters)
{
    for (int i = 0; i < trainingPool.size; i++) {
        if (canComplete(&trainingPool.items[i]))
            completeTraining(trainingPool.items[i].trainingId);
    }
    
    vTaskDelay(pdMS_TO_TICKS(60000));
}

void vStartTrainingCheckerTask() { xTaskCreatePinnedToCore(vTrainingCheckerTask, "Training_Check", 1024, NULL, 1, &xTrainingCheckerHandle, 1); }


bool canComplete(Training *t) {
    
    if (t->state == TrainingState::COMPLETED)
        if ((millis() - t->currentTimeMS) >= 150000) return true;

    else if ((t->currentTimeMS - t->lapsTimeSumMS) >= 180000) return true;

    return false;
}