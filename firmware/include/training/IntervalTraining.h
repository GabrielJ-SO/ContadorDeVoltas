#pragma once
#ifndef INTERVALTRAINING_H
#define INTERVALTRAINING_H

typedef struct IntervalTraining
{
    unsigned long restTimeMS, elapsedRestTimeMS;
    int           numberOfIntervals, numberOfCompletedIntervals, numberOfLaps;
    bool          interval, intervalCompleted;
} IntervalTraining;

bool startIntervalTraining(long trainingId, long athleteTag, unsigned long restTimeMS, int intervals, int numberOfLaps);

#endif