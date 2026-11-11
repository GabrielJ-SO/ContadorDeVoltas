#pragma once
#ifndef RUNNINGWORKOUT_H
#define RUNNINGWORKOUT_H

typedef struct RunningWorkout
{
    int numberOfLaps;
} RunningWorkout;

bool startRunningWorkout(long trainingId, std::string atheleteTag, int numberOfLaps);

#endif