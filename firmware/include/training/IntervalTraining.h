#ifndef INTERVALTRAINING_H
#define INTERVALTRAINING_H

typedef struct IntervalTraining
{
    unsigned long restTimeMS, elapsedRestTimeMS;
    int           numberOfIntervals, numberOfCompletedIntervals, numberOfLaps;
    bool          interval, intervalCompleted;
} IntervalTraining;


#endif