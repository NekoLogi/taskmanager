#include <stdio.h>
#include "log.h"

LogLevel logLevel = DEBUG;

void log(LogLevel level, const char *message)
{
    if (level == DEBUG && logLevel == DEBUG)
    {
        printf("[DEBUG] %s", message);
    }
    else if (level == INFO)
    {
        printf("%s", message);
    }
}

void setLogLevel(LogLevel level)
{
    logLevel = level;
}