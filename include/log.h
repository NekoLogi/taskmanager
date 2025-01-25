#ifndef LOG_H
#define LOG_H

typedef enum LogLevel
{
    DEBUG,
    INFO
} LogLevel;

void log(LogLevel level, const char *message);

void setLogLevel(LogLevel level);

#endif