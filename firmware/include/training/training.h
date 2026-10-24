#pragma once
#ifndef TRAINING_H
#define TRAINING_H

#include "pch.h"

#include "FreePractice.h"
#include "RunningWorkout.h"
#include "IntervalTraining.h"

struct Training;


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
    void  (*lapCounting)(Training* t);
    void  (*display)(Training* t, char* buffer, size_t tamanhoBuffer);
    void  (*sendLapToAPI)(Training* t);
} TrainingOP;


struct Training
{
    TrainingType  type;
    TrainingOP    ops;
    TrainingState state;

    int           lapsCompleted;
    long          trainingId;
    std::string   athleteTag;
    unsigned long startTimeMS, lastLapTimeMS, currentTimeMS, lapsTimeSumMS;
    
    union
    {
        FreePractice       free;
        RunningWorkout     workout;
        IntervalTraining   interval;
    } dataTraining;

};


void timeFormat(unsigned long tempoMS, char* buffer, size_t bufferSize);
void lapTimeFormat(unsigned long tempoMS, char* buffer, size_t bufferSize);

void completeTraining(Training* t);

#endif