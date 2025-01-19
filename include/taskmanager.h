#ifndef TASKMANAGER_H
#define TASKMANAGER_H

typedef struct Task
{
    int id;
    char title[256];
    int status;
} Task;

#endif