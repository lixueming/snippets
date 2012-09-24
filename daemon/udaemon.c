//
// daemon.c - Make Daemon
//

#include "udaemon.h"

// Prevent child processs die
struct sigaction ignore_child_death;

//
// Description :
//      Switch to daemon mode
//
// Return Value :
//      0 - No error
//      1 - Error
//
int udaemon(void)
{
    struct rlimit resource_limit = {0};
    int status = -1;
    int filedesc = -1;
    int i;

    ignore_child_death.sa_handler = NULL;
    memset(&ignore_child_death.sa_mask, sizeof(ignore_child_death.sa_mask), 0);
    ignore_child_death.sa_flags= SA_NOCLDSTOP | SA_RESTART;
    ignore_child_death.sa_restorer= NULL;
    
    // Prevent zombie process
    sigaction(SIGCHLD, &ignore_child_death, NULL);
    
    status = fork();
    switch (status)
    {
        case -1 :   // error
            return 1;
        case 0 :    // clone
            break;
        default :   // original process
            exit(0);
    }
    
    resource_limit.rlim_max = 0;
    status = getrlimit(RLIMIT_NOFILE, &resource_limit);
    if (-1 == status)
        return 1;
    
    if (0 == resource_limit.rlim_max)
        return 1;
    
    for (i = 0; i < resource_limit.rlim_max; i++)
        (void) close(i);
    
    status = setsid();
    if (-1 == status)
        return 1;

    // Fork again
    status = fork();
    switch (status)
    {
        case -1 :
            return 1;
        case 0 :        // clone process
            break;
        default :       // original process
            exit(0);
    }
    
    chdir("/");         // change root directory
    umask(0);           // chage user mask
    
    filedesc = open("/dev/null", O_RDWR);
    (void) dup(filedesc);
    (void) dup(filedesc);
    
    return 0;   // success
}   // of udeamon
