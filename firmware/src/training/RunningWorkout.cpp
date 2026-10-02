#include "training/Training.h"
#include "training/TrainingPool.h"
#include "global.h"

bool rwLapCounting (Training* t) {
    return true;
}

void rwDisplay(Training* t, char* buffer, size_t tamanhoBuffer) {

}

void rwSendLapToAPI(Training* t) {

}

TrainingOP rwOP = { rwLapCounting, rwDisplay,rwSendLapToAPI };


bool startRunningWorkout(long trainingId, long athleteTag, int numberOfLaps) {
    Training t;

    t.type                              = RUNNING_WORKOUT;
    t.state                             =     NON_STARTED;
    t.trainingId                        =      trainingId;
    t.athleteTag                        =      athleteTag;
    t.lapsCompleted                     =               0;
    t.startTimeMS                       =               0;
    t.lastLapTimeMS                     =               0;
    t.currentTimeMS                     =               0;
    t.totalTimeSumMS                    =               0;
    t.dataTraining.workout.numberOfLaps =    numberOfLaps;
    
    if (addTraining(&trainingPool, t)) 
        return true;
        
    return false;
}