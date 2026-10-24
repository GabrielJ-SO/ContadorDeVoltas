#include "training/Training.h"
#include "training/TrainingPool.h"
#include "global.h"

void fpLapCounting (Training* t) {
    if (t->state == RUNNING)
    {
        t->lastLapTimeMS = t->currentTimeMS - t->lapsTimeSumMS;
        t->lapsTimeSumMS += t->lastLapTimeMS;
        t->lapsCompleted++;

    } else {
        t->startTimeMS = millis();
        t->state       =  RUNNING;
    }
}

void fpDisplay(Training* t, char* buffer, size_t tamanhoBuffer) {
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

        timeFormat(t->currentTimeMS, timeBuffer, sizeof(timeBuffer));
        lapTimeFormat(t->lastLapTimeMS, lastLapTimeBuffer, sizeof(lastLapTimeBuffer));
        snprintf(buffer, tamanhoBuffer, "%s |%03d| %s |OK!", timeBuffer, t->lapsCompleted, lastLapTimeBuffer);
    }
}

void fpSendLapToAPI(Training* t) {

}

TrainingOP fpOP = { fpLapCounting, fpDisplay, fpSendLapToAPI };


bool startFreePractice(long trainingId, std::string athleteTag) {
    Training t;

    t.type                               = FREE_PRACTICE;
    t.state                              =   NON_STARTED;
    t.trainingId                         =    trainingId;
    t.athleteTag                         =    athleteTag;
    t.ops                                =          fpOP;
    t.lapsCompleted                      =             0;
    t.startTimeMS                        =             0;
    t.lastLapTimeMS                      =             0;
    t.currentTimeMS                      =             0;
    t.lapsTimeSumMS                      =             0;

    if (addTraining(&trainingPool, t)) 
        return true;
        
    return false;
}
