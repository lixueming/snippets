//
// Name :
//      Stopwatch Test Program
//
// Filename :
//      stopwatch-test.c
//
// Description :
//      Stopwatch Test Program
//
// Author :
//      Sang-Heon Han <bkwormkr (at) yachoo (dot) co (dot) kr>
//
// History :
//      2003-06-12 First version
//
// Bugs :
//      None
//
// Note :
//      None
//

#include <unistd.h>
#include <stdio.h>
#include "stopwatch.h"

int main(void)
{
    STOPWATCH stopwatch;
    double runtime;
    int delaytime;
    char buf[100];
    int num_of_items;

    do
    {
        printf("\ninput delay time : ");
        fgets(buf, 99, stdin);
        num_of_items = sscanf(buf, "%d", &delaytime);
    } while (num_of_items != 1);

    stopwatch_reset(&stopwatch);
    stopwatch_start(&stopwatch);
    sleep(delaytime);
    stopwatch_stop(&stopwatch);

    runtime = stopwatch_gettime(stopwatch);
    printf("run time = %.5fs\n", runtime);

    return 0;
}
