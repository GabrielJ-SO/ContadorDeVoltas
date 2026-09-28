#include "training/training.h"

bool fpLapCounting (Training* t) {
    return true;
}

void fpDisplay(Training* t, char* buffer, size_t tamanhoBuffer) {

}

void fpSendLapToAPI(Training* t) {

}

TrainingOP fpOP = { fpLapCounting, fpDisplay, fpSendLapToAPI };


bool startFreePractice(long trainingId, long athleteTag) {
    return true;
}
