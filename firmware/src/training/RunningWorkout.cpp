#include "training/training.h"

bool rwLapCounting (Training* t) {
    return true;
}

void rwDisplay(Training* t, char* buffer, size_t tamanhoBuffer) {

}

void rwSendLapToAPI(Training* t) {

}

TrainingOP runningWorkoutOP = { rwLapCounting, rwDisplay,rwSendLapToAPI };


bool startRunningWorkout(long trainingId, long atheleteTag, int numberOfLaps) {
    return true;
}