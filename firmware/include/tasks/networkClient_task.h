#pragma once
#ifndef NETWORKCLIENT_TASK_H
#define NETWORKCLIENT_TASK_H

void vStartNetworkClientTask();

typedef struct Lap Lap;

Lap createLap(long trainingID, unsigned long lapTime);
bool sendLapToQueue(Lap lap, unsigned long awaitMS);



#endif