#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "taskmanager.h"

void saveJSON(const char *title);

Task *loadJSON(int id);

void deleteJSON(int id);

int getAvailableID();

#endif