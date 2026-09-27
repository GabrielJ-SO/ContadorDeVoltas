#ifndef TRAINING_H
#define TRAINING_H

#include <iostream>

#include "FreePractice.h"
#include "RunningWorkout.h"
#include "IntervalTraining.h"

typedef enum {
    FREE_SLOT,
    FREE_PRACTICE,
    RUNNING_WORKOUT,
    INTERVAL_TRAINING
} TrainingType;

typedef enum {
    NON_STARTED,
    RUNNING,
    COMPLETED
} TrainingState;

typedef struct {
    bool  (*lapCounting)(Training* t);
    void  (*display)(Training* t, char* buffer, size_t tamanhoBuffer);
    void  (*sendLapToAPI)(Training* t);
} TrainingOP;



typedef struct Training 
{

    TrainingType  type;
    TrainingOP    ops;
    TrainingState state;

    int           lapsCompleted;
    long          trainingId, athleteTag;
    unsigned long startTimeMS, lastLapTimeMS, currentTimeMS, totalTimeSumMS;
    
    union
    {
        FreePractice       livre;
        RunningWorkout     corrida;
        IntervalTraining   intervalado;
    } training;

} Training;

#endif