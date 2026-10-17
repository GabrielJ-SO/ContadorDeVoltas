#include "pch.h"

#include "training/TrainingPool.h"

bool addTraining(Pool* p, Training t) {
    if (p == nullptr || p->amount >= MAX_TRAINING_SIMULTANEOUS) {
        return false;
    }

    p->pool[p->amount] = t;
    p->amount++;
    return true;
}

void reorderPool(Pool* p) {
    for (int i = 1; i < p->amount; i++) {
        if (p->pool[i-1].type == FREE_SLOT && p->pool[i].type != FREE_SLOT) {
            p->pool[i-1]    = p->pool[i];
            p->pool[i].type = FREE_SLOT;
        }
    }

}

void removeTraining(Pool* p, int trainingId) {

    for (int i = 0; i < MAX_TRAINING_SIMULTANEOUS; i++) {
        if (p->pool[i].trainingId == trainingId) {
            p->pool[i].type = FREE_SLOT;
            reorderPool(p);
            p->amount--;
            return;
        }
    }
}

void initializePool(Pool* p) {
    p->amount = 0;
    for (int i = 0; i < MAX_TRAINING_SIMULTANEOUS; i++) {
        p->pool[i].type = FREE_SLOT;
    }
}