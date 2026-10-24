#include "training/Training.h"
#include "training/TrainingPool.h"
#include "global.h"

void rwLapCounting (Training* t) {
    if (t->state == RUNNING)
    {
        t->lastLapTimeMS   = t->currentTimeMS - t->lapsTimeSumMS;
        t->lapsTimeSumMS  += t->lastLapTimeMS;
        t->lapsCompleted++;

        if (t->lapsCompleted >= t->dataTraining.workout.numberOfLaps) {
            t->state       = COMPLETED;
        } 
    } 
    else {
        if (t->state == NON_STARTED) {
            t->startTimeMS = millis();
            t->state       = RUNNING;
        }
    }
    
}

void rwDisplay(Training* t, char* buffer, size_t tamanhoBuffer) {
    char timeBuffer[16], lastLapTimeBuffer[12];
    if (t->state != COMPLETED)
    {
        if (t->state == RUNNING) 
        {
            t->currentTimeMS = millis() - t->startTimeMS;
        
            timeFormat(t->currentTimeMS, timeBuffer, sizeof(timeBuffer));
            lapTimeFormat(t->lastLapTimeMS, lastLapTimeBuffer, sizeof(lastLapTimeBuffer));
            snprintf(buffer, tamanhoBuffer, "%s |%03d| %s |-/-", timeBuffer, t->lapsCompleted, lastLapTimeBuffer);
        }
        else {
            snprintf(buffer, tamanhoBuffer, " Pronto! |    |       |-/-");
        }
    }
    else {
        long timeOutMS = millis() - t->startTimeMS;
        if (timeOutMS >= 10000){ completeTraining(t); }

        timeFormat(t->currentTimeMS, timeBuffer, sizeof(timeBuffer));
        lapTimeFormat(t->lastLapTimeMS, lastLapTimeBuffer, sizeof(lastLapTimeBuffer));
        snprintf(buffer, tamanhoBuffer, "%s |%03d| %s |Ok!", timeBuffer, t->lapsCompleted, lastLapTimeBuffer);
    }
}

void rwSendLapToAPI(Training* t) {

}

TrainingOP rwOP = { rwLapCounting, rwDisplay, rwSendLapToAPI };


bool startRunningWorkout(long trainingId, std::string athleteTag, int numberOfLaps) {
    Training t;

    t.type                              = RUNNING_WORKOUT;
    t.state                             =     NON_STARTED;
    t.trainingId                        =      trainingId;
    t.athleteTag                        =      athleteTag;
    t.ops                               =            rwOP;
    t.lapsCompleted                     =               0;
    t.startTimeMS                       =               0;
    t.lastLapTimeMS                     =               0;
    t.currentTimeMS                     =               0;
    t.lapsTimeSumMS                     =               0;
    t.dataTraining.workout.numberOfLaps =    numberOfLaps;
    
    if (addTraining(&trainingPool, t)) 
        return true;
        
    return false;
}