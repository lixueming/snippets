#ifndef __STOPWATCH_H
#define __STOPWATCH_H

#include <unistd.h>
#include <sys/time.h>

typedef struct _STOPWATCH
{
    struct timeval  tv_start, tv_stop;
    struct timezone tz_start, tz_stop;
} STOPWATCH;

void stopwatch_reset(STOPWATCH *stopwatch);

int stopwatch_start(STOPWATCH *stopwatch);

int stopwatch_stop(STOPWATCH *stopwatch);

double stopwatch_gettime(const STOPWATCH stopwatch);

#endif
