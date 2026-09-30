#pragma once
#ifndef TRAININGPOOL_H
#define TRAININGPOOL_H

#include "training/Training.h"

#define MAX_TRAINING_SIMULTANEOUS 4

typedef struct pool {
    int      amount;
    Training pool[MAX_TRAINING_SIMULTANEOUS];
} Pool;


bool addTraining(Pool* p, Training t);
void removeTraining(Pool* p, Training t);

void initializePool(Pool* p, Training t);


#endif