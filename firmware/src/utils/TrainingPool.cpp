#include "pch.h"

#include "training/TrainingPool.h"

bool addTraining(Pool* p, Training t) {
    if (p == nullptr || p->amount >= MAX_TRAINING_SIMULTANEOUS) {
        return false;
    }

    for (int i = 0; i < MAX_TRAINING_SIMULTANEOUS; i++) {
        if (p->pool[i].type == FREE_SLOT) {
            p->pool[i] = t;
            p->amount++;
            return true;
        }
    }

    return false;
}

void removeTraining(Pool* p, int trainingId) {

    for (int i = 0; i < MAX_TRAINING_SIMULTANEOUS; i++) {
        if (p->pool[i].trainingId == trainingId) {
            p->pool[i].type = FREE_SLOT;
            p->amount--;
            return;
        }
    }
}

void initializePool(Pool* p) {
    p->amount = 0;
    for (int i = 0; i < MAX_TRAINING_SIMULTANEOUS; i++) {
        p->pool[0].type = FREE_SLOT;
    }
}