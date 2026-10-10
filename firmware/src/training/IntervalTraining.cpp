#include "training/Training.h"
#include "training/TrainingPool.h"
#include "global.h"

void itLapCounting (Training* t) {
    if (t->state == RUNNING) 
    {
        if (!t->dataTraining.interval.interval)
        {
            t->lastLapTimeMS = t->currentTimeMS - t->lapsTimeSumMS;
            t->lapsTimeSumMS += t->lastLapTimeMS;
            t->lapsCompleted++;

            if (t->dataTraining.interval.numberOfLaps == t->lapsCompleted) 
            {
                t->dataTraining.interval.elapsedRestTimeMS = millis();
                t->dataTraining.interval.numberOfCompletedIntervals++; 
                t->dataTraining.interval.interval = true;

                if (t->dataTraining.interval.numberOfIntervals == t->dataTraining.interval.numberOfCompletedIntervals) {
                    t->state       = COMPLETED;
                    t->startTimeMS = millis();
                }
            }
        }
    } else {
        if (t->state == NON_STARTED) {
            t->startTimeMS   = millis();
            t->currentTimeMS =        0;
            t->lastLapTimeMS =        0;
            t->lapsTimeSumMS =        0;
            t->lapsCompleted =        0;
            t->state         =  RUNNING;
        }
    }
}

void itDisplay(Training* t, char* buffer, size_t tamanhoBuffer) {
    char timeBuffer[16], lastLapTimeBuffer[12];
    if (t->state != COMPLETED)
    {
        if (t->state == RUNNING) 
        {   
            if (!t->dataTraining.interval.interval) {
                t->currentTimeMS = millis() - t->startTimeMS;
                timeFormat(t->currentTimeMS, timeBuffer, sizeof(timeBuffer));
                lapTimeFormat(t->lastLapTimeMS, lastLapTimeBuffer, sizeof(lastLapTimeBuffer));

                snprintf(buffer, tamanhoBuffer, "%s |%03d| %s |%03d", timeBuffer, t->lapsCompleted, lastLapTimeBuffer, t->dataTraining.interval.numberOfCompletedIntervals);
            }
            else {
                long remainingRestTimeMS = t->dataTraining.interval.restTimeMS - (millis() - t->dataTraining.interval.elapsedRestTimeMS);

                if (remainingRestTimeMS <= 0) { 
                    t->dataTraining.interval.interval = false;
                    t->state = NON_STARTED;
                }
                else {
                    timeFormat(t->currentTimeMS, timeBuffer, sizeof(timeBuffer));
                    lapTimeFormat(remainingRestTimeMS, lastLapTimeBuffer, sizeof(lastLapTimeBuffer));
                    snprintf(buffer, tamanhoBuffer, "%s |%03d| %s |%03d", timeBuffer, t->lapsCompleted, lastLapTimeBuffer, t->dataTraining.interval.numberOfCompletedIntervals);
                }
            }
        }
        else {
            timeFormat(t->currentTimeMS, timeBuffer, sizeof(timeBuffer));
            snprintf(buffer, tamanhoBuffer, "%s |  Pronto!  |%03d", timeBuffer, t->dataTraining.interval.numberOfCompletedIntervals);
        }
    }
    else {
        long timeOutMS = millis() - t->startTimeMS;
        if (timeOutMS >= 10000){ completeTraining(t); }
   
        timeFormat(t->currentTimeMS, timeBuffer, sizeof(timeBuffer));
        snprintf(buffer, tamanhoBuffer, "%s | Concluido |%03d", timeBuffer, t->dataTraining.interval.numberOfCompletedIntervals);
    }
}

void itSendLapToAPI(Training* t) {

}

TrainingOP itOP = { itLapCounting, itDisplay, itSendLapToAPI };


bool startIntervalTraining(long trainingId, long athleteTag, unsigned long restTimeMS, int intervals, int numberOfLaps) {
    Training t;

    t.type                                    = INTERVAL_TRAINING;
    t.state                                   =       NON_STARTED;
    t.trainingId                              =        trainingId;
    t.athleteTag                              =        athleteTag;
    t.lapsCompleted                           =                 0;
    t.startTimeMS                             =                 0;
    t.lastLapTimeMS                           =                 0;
    t.currentTimeMS                           =                 0;
    t.lapsTimeSumMS                           =                 0;
    t.dataTraining.interval.restTimeMS        =        restTimeMS;
    t.dataTraining.interval.numberOfIntervals =         intervals;
    t.dataTraining.interval.numberOfLaps      =      numberOfLaps;
    t.dataTraining.interval.interval          =             false;
    t.dataTraining.interval.intervalCompleted =             false;

    if (addTraining(&trainingPool, t)) 
        return true;
        
    return false;
}