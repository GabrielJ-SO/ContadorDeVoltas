#include "training/Training.h"

bool itLapCounting (Training* t) {
    return true;
}

void itDisplay(Training* t, char* buffer, size_t tamanhoBuffer) {

}

void itSendLapToAPI(Training* t) {

}

TrainingOP itOP = { itLapCounting, itDisplay, itSendLapToAPI };


bool startIntervalTraining(long trainingId, long athleteTag, unsigned long restTimeMS, int intervals, int numberOfLaps) {
    return true;
}