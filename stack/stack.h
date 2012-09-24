/*
* stack.h - 단순한 스택
*/

#ifndef __STACK_H
#define __STACK_H

#define STACK_SIZE	1000	/* 스택의 크기 */

typedef struct __STACK
{
	int sp;
	int data[STACK_SIZE];	/* 스택 데이터 */
} STACK;

void reset_stack(STACK *stack);
int push(STACK *stack, int data);
int pop(STACK *stack);
int peek(STACK *stack, int no);
int empty(STACK *stack);
int full(STACK *stack);

#endif
