#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void)
{
	QUEUE q;
	int *p;
	int i;

	printf("qsize = %d\n", QSIZE);

	reset_queue(&q);

	i = 0;
	while (1)
	{
		 p = (int *) malloc(sizeof(int)); 
		 if (put_qdata(&q, (void *) p))
			 break;
		 *p = i++;
	}

	while ((p = (int *) get_qdata(&q)) != NULL)
	{
		printf("%d\t", *p);
		if (*p % 5 == 0)
			putchar('\n');
	}
		
	return 0;
}
