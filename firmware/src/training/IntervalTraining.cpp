#include "training/Training.h"
#include "training/TrainingPool.h"
#include "global.h"

bool itLapCounting (Training* t) {
    return true;
}

void itDisplay(Training* t, char* buffer, size_t tamanhoBuffer) {

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
    t.totalTimeSumMS                          =                 0;
    t.dataTraining.interval.restTimeMS        =        restTimeMS;
    t.dataTraining.interval.numberOfIntervals =         intervals;
    t.dataTraining.interval.numberOfLaps      =      numberOfLaps;

    if (addTraining(&trainingPool, t)) 
        return true;
        
    return false;
}