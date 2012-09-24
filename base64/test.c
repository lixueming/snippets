#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "base64.h"

#define SIZE 100

int main(void)
{
    char src[1000];
    char dest[SIZE];
    int nbase64;
    int fd;
    int out;

    scanf("%s", src);

    /*
    nbase64 = sbase64(dest, src, SIZE);

    printf("size = %d\n", nbase64);
    puts(dest);
    */

    out = creat("b64.txt", O_CREAT | O_EXCL);
    fd = open(src, O_RDONLY);
    nbase64 = fbase64(2, fd);
    close(fd);
    close(out);

    printf("\n\nsize = %d\n", nbase64);

    return 0;
}
