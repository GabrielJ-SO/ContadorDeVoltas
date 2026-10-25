#include "pch.h"

#include "training/TrainingPool.h"

bool addTraining(Pool* p, Training t) {
    if (p == nullptr || p->size >= MAX_TRAINING_SIMULTANEOUS) return false;
        
    p->items[p->size] = t;
    p->size++;
    return true;
}

void reorderPool(Pool* p) {
    for (int i = 1; i < p->size; i++) {
        if (p->items[i-1].type == FREE_SLOT && p->items[i].type != FREE_SLOT) {
            p->items[i-1]    = p->items[i];
            p->items[i].type = FREE_SLOT;
        }
    }

}

bool removeTraining(Pool* p, int trainingId) {
    for (int i = 0; i < p->size; i++) {
        if (p->items[i].trainingId == trainingId) {
            p->items[i].type        = FREE_SLOT;
            p->items[i].state       = COMPLETED;
            p->items[i].athleteTag  = "";
            p->items[i].trainingId  = -1;
            reorderPool(p); 
            p->size--;
            return true;
        }
    }

    return false;
}

void initializePool(Pool* p) {
    p->size = 0;
    for (int i = 0; i < MAX_TRAINING_SIMULTANEOUS; i++) {
        p->items[i].type = FREE_SLOT;
    }
    
}