#pragma once
#ifndef TRAININGPOOL_H
#define TRAININGPOOL_H

#include "training/Training.h"

#define MAX_TRAINING_SIMULTANEOUS 4

typedef struct Pool {
    int      amount;
    Training pool[MAX_TRAINING_SIMULTANEOUS];
} Pool;


bool addTraining(Pool* p, Training t);
void removeTraining(Pool* p, int trainingId);

void initializePool(Pool* p);


#endif