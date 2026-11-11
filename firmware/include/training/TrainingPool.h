#pragma once
#ifndef TRAININGPOOL_H
#define TRAININGPOOL_H

#include "training/Training.h"

#define MAX_TRAINING_SIMULTANEOUS 4

typedef struct Pool {
    int      size;
    Training items[MAX_TRAINING_SIMULTANEOUS];
} Pool;


bool addTraining(Pool* p, Training t);
bool removeTraining(Pool* p, int trainingId);

void initializePool(Pool* p);


#endif