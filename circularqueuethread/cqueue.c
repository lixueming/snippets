/*
* cqueue.c - Circle Queue (Thread Safe)
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <ctype.h>

#include "cqueue.h"

/*
* 큐를 할당한다
*
* 반환값 :
*
* NULL - 에러
* CIRCLE_QUEUE * - 원형큐 구조체 포인터
*
*/
CIRCLE_QUEUE *alloc_cqueue(void)
{
	CIRCLE_QUEUE *q;

	assert(q != NULL);

	q = (CIRCLE_QUEUE *) malloc(sizeof(CIRCLE_QUEUE));
	if (q == NULL)
		return NULL;						/* 메모리를 할당하지 못했으면 에러 */

	q->head = q->tail = 0;					/* 읽고 쓰는 위치 초기화 */
	q->ndata = 0;							/* 데이터의 크기 초기화 */
	pthread_mutex_init(&q->lock, NULL);		/* lock 초기화 */

	return q;
}

/*
* 큐를 제거한다
*/
void free_cqueue(CIRCLE_QUEUE *q)
{
	assert(q != NULL);

	pthread_mutex_destroy(&q->lock);	/* lock에 할당된 자원을 반환한다 */
	free(q);							/* 원형큐 메모리를 반환 */
}

/*
* 큐가 완전히 찼는지 조사한다
*/
enum QUEUE_FULL_STATUS full_cqueue(CIRCLE_QUEUE *q)
{
	enum QUEUE_FULL_STATUS retval;

	assert(q != NULL);

	pthread_mutex_lock(&q->lock);
	retval = (q->ndata == QSIZE) ? QUEUE_FULL : QUEUE_NOT_FULL;
	pthread_mutex_unlock(&q->lock);

	return retval;
}

/*
* 큐가 비어있는지 조사한다
*/
enum QUEUE_EMPTY_STATUS empty_cqueue(CIRCLE_QUEUE *q)
{
	enum QUEUE_EMPTY_STATUS retval;

	assert(q != NULL);

	pthread_mutex_lock(&q->lock);
	retval = (q->ndata == 0) ? QUEUE_EMPTY : QUEUE_NOT_EMPTY;		/* 큐가 비어있으면 */
	pthread_mutex_unlock(&q->lock);

	return retval;
}

/*
* 큐에 데이터를 넣는다
*
* Return Value :
*
* n : 큐에 추가한 데이터의 크기
*/
int put_cqueue(CIRCLE_QUEUE *q, char *buf, int len)
{
	int i;

	assert(q != NULL);
	assert(buf != NULL);
	assert(len != 0);

	pthread_mutex_lock(&q->lock);
	for (i = 0; CQUEUE_NEXT(q->head) != q->tail && i < len; i++)
	{
		q->data[q->head++] = *buf++;
		if (q->head >= QSIZE)
			q->head = 0;
	}
	q->ndata += i;		/* 추가한 데이터의 크기만큼 증가 */
	pthread_mutex_unlock(&q->lock);

	return i;
}

/*
* 큐에서 데이터를 꺼낸다
*
* Return Value :
*
* n : 큐에서 꺼낸 데이터의 크기
*/
int get_cqueue(CIRCLE_QUEUE *q, char *buf, int len)
{
	int i;

	assert(q != NULL);
	assert(buf != NULL);
	assert(len != 0);

	pthread_mutex_lock(&q->lock);
	for (i = 0; q->tail != q->head && i < len; i++)
	{
		*buf++ = q->data[q->tail++];
		if (q->tail >= QSIZE)
			q->tail = 0;
	}
	q->ndata -= i;		/* 꺼낸 데이터의 크기만큼 감소 */
	pthread_mutex_unlock(&q->lock);

	return i;
}

/*
* 현재 큐에 들어있는 데이터의 크기
*
* Return Value :
*
* n : 큐에 있는 데이터의 크기
*/
unsigned int get_cqueue_size(CIRCLE_QUEUE *q)
{
	int ndata;

	assert(q != NULL);

	pthread_mutex_lock(&q->lock);
	ndata = q->ndata;
	pthread_mutex_unlock(&q->lock);

	return ndata;
}

/*
* 원형큐를 출력한다
*/
void print_cqueue(CIRCLE_QUEUE *q)
{
	int head, tail;

	assert(q != NULL);

	pthread_mutex_lock(&q->lock);
	head = q->head;
	tail = q->tail;
	printf("Circle Queue (%p) : ", q);
	while (head != tail)
	{
		putchar((isprint(q->data[tail])) ? q->data[tail] : '.');
		if (tail < QSIZE - 1)
			tail++;
		else
			tail = 0;
	}
	pthread_mutex_unlock(&q->lock);
	putchar('\n');
}
