#pragma once
#ifndef RFID_TASK_H
#define RFID_TASK_H

void vStartRFIDTask();

void notifyRFID();

void addTag(std::string tag);
void removeTag(std::string tag);

#endif