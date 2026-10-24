#pragma once
#ifndef LAPCOUNT_TASK_H
#define LAPCOUNT_TASK_H

void vStartLapCountTask();

bool sendTagToRfidQueue(std::string tag, unsigned long awaitMS);

#endif