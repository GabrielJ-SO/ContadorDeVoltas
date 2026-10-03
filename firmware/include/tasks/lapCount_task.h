#pragma once
#ifndef LAPCOUNT_TASK_H
#define LAPCOUNT_TASK_H

void vStartLapCountTask();

bool sendTagToRfidQueue(long tag, unsigned long awaitMS);

#endif