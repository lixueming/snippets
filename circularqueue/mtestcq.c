#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "cqueue.h"

#define BUFLEN	1000

int main(void)
{
	char s[BUFLEN];
	CIRCLE_QUEUE *q;
	int loopflag = 1;
	int len;
	int cmd;
	int result;

	q = alloc_cqueue();

	while (loopflag)
	{
		printf("1) Put    2) Get    3) Quit : ");
		gets(s);

		cmd = atoi(s);
		
		if (cmd < 1 || cmd > 3)	// 명령을 잘 못 선택했으면
			continue;

		if (cmd == 1)	// Put
		{
			printf("String : ");
			gets(s);
			len = strlen(s);
			if (len <= 0)
				continue;
		}
		else if (cmd == 2)	// Get
		{
			printf("Length : ");
			gets(s);
			len = atoi(s);
			if (len <= 0)
				continue;
		}

		print_cqueue(q);
		printf("left size = %d\n", get_cqueue_free(q));

		switch (cmd)
		{
			case 1 :	// Put
				result = put_cqueue(q, s, len);
				break;
			case 2 :	// Get
				result = get_cqueue(q, s, len);
				printf("Get : %s\n", s);
				break;
			case 3 :	// Quit
				loopflag = 0;
				break;
			default :
				continue;
		}

		printf("Result : %d\n", result);
		printf("left size = %d\n", get_cqueue_free(q));
		print_cqueue(q);
	}	// of while

	free_cqueue(q);

	return 0;
}	// of main

