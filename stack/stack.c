/*
* stack.c - 단순한 스택
*/

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "stack.h"

/* 스택을 초기화 */
void reset_stack(STACK *stack)
{
	assert(stack != NULL);

	stack->sp = 0;
}

/* 스택에 데이터를 push */
int push(STACK *stack, int data)
{
	assert(stack != NULL);
	assert(stack->sp >= 0 && stack->sp <= STACK_SIZE);

	if (stack->sp == STACK_SIZE)
		return 1;

	stack->data[stack->sp++] = data;

	return 0;
}

/* 스택의 데이터를 pop */
int pop(STACK *stack)
{
	assert(stack != NULL);
	assert(stack->sp >= 0 && stack->sp <= STACK_SIZE);

	if (stack->sp == 0)
		return INT_MIN;

	return stack->data[--stack->sp];
}

/* 스택 중간의 데이터를 peek */
int peek(STACK *stack, int no)
{
	assert(stack != NULL);
	assert(stack->sp >= 0 && stack->sp <= STACK_SIZE);

	if (no < 0 || stack->sp >= no)
		return INT_MIN;

	return stack->data[no];
}

/* 스택이 비었는지 검사 */
int empty(STACK *stack)
{
	return (stack->sp > 0) ? 0 : 1;
}

/* 스택이 꽉찼는지 검사 */
int full(STACK *stack)
{
	return (stack->sp < STACK_SIZE) ? 0 : 1;
}
