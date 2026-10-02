#include "training/Training.h"
#include "training/TrainingPool.h"
#include "global.h"

bool fpLapCounting (Training* t) {
    return true;
}

void fpDisplay(Training* t, char* buffer, size_t tamanhoBuffer) {

}

void fpSendLapToAPI(Training* t) {

}

TrainingOP fpOP = { fpLapCounting, fpDisplay, fpSendLapToAPI };


bool startFreePractice(long trainingId, long athleteTag) {
    Training t;

    t.type                               = FREE_PRACTICE;
    t.state                              =   NON_STARTED;
    t.trainingId                         =    trainingId;
    t.athleteTag                         =    athleteTag;
    t.lapsCompleted                      =             0;
    t.startTimeMS                        =             0;
    t.lastLapTimeMS                      =             0;
    t.currentTimeMS                      =             0;
    t.totalTimeSumMS                     =             0;

    if (addTraining(&trainingPool, t)) 
        return true;
        
    return false;
}
