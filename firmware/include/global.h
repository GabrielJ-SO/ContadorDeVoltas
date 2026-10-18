#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

#include "training/TrainingPool.h"


#define RFID_RX_PIN 32
#define RFID_TX_PIN 33


inline Pool trainingPool;

inline SemaphoreHandle_t xTrainingPoolMutex;

#endif