//
// udaemon.h - Make Daemon
//

#ifndef __UDAEMON_H
#define __UDAEMON_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>

// switch to daemon mode
int udaemon(void);

#endif
