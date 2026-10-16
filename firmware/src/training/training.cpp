#include "training/Training.h"


void timeFormat(unsigned long tempoMS, char* buffer, size_t bufferSize) {
    int seg = tempoMS / 1000 % 60;
    int min = (tempoMS / 1000) / 60;
    int hrs = (tempoMS / 1000) / 60 / 60;
    snprintf(buffer, bufferSize, "%02d:%02d:%02d", hrs, min, seg);
}

void lapTimeFormat(unsigned long tempoMS, char* buffer, size_t bufferSize) {
    int seg = tempoMS / 1000 % 60;
    int min = (tempoMS / 1000) / 60;
    snprintf(buffer, bufferSize, "%02d:%02d", min, seg);
}


void completeTraining(Training* t) {
    t->type       = FREE_SLOT;
    t->state      = NON_STARTED;
    t->athleteTag = -1;
    t->trainingId = -1;
}