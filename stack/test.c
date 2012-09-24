#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "stack.h"

int main(void)
{
	STACK stack;
	STACK *ptr_stack;
	int i;

	ptr_stack = &stack;
	reset_stack(ptr_stack);

	for (i = 0; i < 100; i++)
		push(ptr_stack, i);

	while ((i = pop(ptr_stack)) != INT_MIN)
		printf("pop() = %d\n", i);

	return 0;
}
