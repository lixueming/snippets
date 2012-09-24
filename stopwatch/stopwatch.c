#include <string.h>
#include <assert.h>
#include "stopwatch.h"

void stopwatch_reset(STOPWATCH *stopwatch)
{
    assert(stopwatch != NULL);

    memset(stopwatch, 0, sizeof(STOPWATCH));
}

int stopwatch_start(STOPWATCH *stopwatch)
{
    assert(stopwatch != NULL);

    return gettimeofday(&stopwatch->tv_start, &stopwatch->tz_start);
}

int stopwatch_stop(STOPWATCH *stopwatch)
{
    assert(stopwatch != NULL);

    return gettimeofday(&stopwatch->tv_stop, &stopwatch->tz_stop);
}

double stopwatch_gettime(const STOPWATCH stopwatch)
{
    double t1, t2;

    t1 =  (double) stopwatch.tv_start.tv_sec + 
            (double) stopwatch.tv_start.tv_usec / (1000 * 1000);
    t2 =  (double) stopwatch.tv_stop.tv_sec + 
            (double) stopwatch.tv_stop.tv_usec / (1000 * 1000);

    return t2 - t1; /* second */
}
