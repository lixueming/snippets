/*
* cqueue.c - Circle Queue (Thread Safe)
*/

#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "minmax.h"
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

	q = (CIRCLE_QUEUE *) malloc(sizeof(CIRCLE_QUEUE));
	if (q == NULL)
		return NULL;					/* 메모리를 할당하지 못했으면 에러 */

	q->head = q->tail = 0;				/* 읽고 쓰는 위치 초기화 */
	q->ndata = 0;						/* 데이터의 크기 초기화 */

	return q;
}

/*
* 큐를 제거한다
*/
void free_cqueue(CIRCLE_QUEUE *q)
{
	assert(q != NULL);

	free(q);							/* 원형큐 메모리를 반환 */
}

/*
* 큐가 완전히 찼는지 조사한다
*/
enum QUEUE_FULL_STATUS full_cqueue(CIRCLE_QUEUE *q)
{
	enum QUEUE_FULL_STATUS retval;

	assert(q != NULL);

	retval = (q->ndata == QSIZE) ? QUEUE_FULL : QUEUE_NOT_FULL;

	return retval;
}

/*
* 큐가 비어있는지 조사한다
*/
enum QUEUE_EMPTY_STATUS empty_cqueue(CIRCLE_QUEUE *q)
{
	enum QUEUE_EMPTY_STATUS retval;

	assert(q != NULL);

	retval = (q->ndata == 0) ? QUEUE_EMPTY : QUEUE_NOT_EMPTY;		/* 큐가 비어있으면 */

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
	unsigned int s1;	// head에서 tail 또는 array 끝 사이의 바이트수
	unsigned int s2;	// array 시작에서 tail 까지 사이의 바이트수

	assert(q != NULL);
	assert(buf != NULL);
	assert(len != 0);


	if (q->head < q->tail)	// Case 1에 해당
	{
		s1 = q->tail - q->head - 1;	// head 다음에 바로 tail이 있다면 빈공간은 없는 것이다
		len = MIN(len, s1);		// len과 s1 중 작은 것의 값만큼만 저장 가능하다

		memcpy(q->data + q->head, buf, len);	// 데이터를 복사한다
		q->head += len;
	}
	else
	{
		// tail이 array 시작이면 QSIZE - 1까지만 사용 가능하다
		s1 = (q->tail != 0) ? QSIZE - q->head : QSIZE - q->head - 1;

		s1 = MIN(len, s1);	// s1 보다 데이터의 길이가 작다면 s1을 조절한다
		memcpy(q->data + q->head, buf, s1);

		s2 = MIN(len - s1, q->tail);	// 복사하고 남은 것과 s2 중에서 작은 것을 선택
		if (s1 <= len && s2 > 0)	// 아직 복사 할 것이 남아있고, 복사할 공간도 있다면
		{
			memcpy(q->data, buf + s1, s2);

			len = s1 + s2;
			q->head = s2;	// array의 끝을 넘었으면, s2의 값이 head의 인덱스이다
		}
		else if (q->head + s1 >= QSIZE)	// array의 끝까지 다 채웠으면
			q->head = 0;	// head를 다시 맨 앞으로 이동
		else
			q->head += len;	// array의 끝을 넘지 않았으면, 단지 len을 더하는 것만으로 끝난다
	}

	q->ndata += len;		/* 추가한 데이터의 크기만큼 증가 */

	return len;
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
	unsigned int s1;	// tail에서 head 또는 array 끝 사이의 바이트 수
	unsigned int s2;	// array 처음에서 head 사이의 바이트 수

	assert(q != NULL);
	assert(buf != NULL);
	assert(len != 0);

	if (q->tail <= q->head)	// Case 1
	{
		s1 = q->head - q->tail;		// head와 tail 사이의 바이트수 (데이터의 양)
		len = MIN(len, s1);			// 요청된 길이와 바이트 수중 작은 것을 선택
		memcpy(buf, q->data + q->tail, len);	// 메모리 복사

		q->tail += len;				// 복사한 양만큼 tail 감소
	}
	else				// Case 2
	{
		s1 = QSIZE - q->tail;		// tail에서 array 끝 사이의 바이트 수

		s1 = MIN(len, s1);			// s1과 len 중 작은 것을 선택
		memcpy(buf, q->data + q->tail, s1);	// 메모리 복사

		if (s1 != len)	// 복사할 것이 남아있으면
		{
			s2 = MIN(len - s1, q->head);	// array 처음에서부터 복사할 데이터 양
			memcpy(buf + s1, q->data, s2);
			
			len = s1 + s2;	// 실제 복사한 데이터의 양
			q->tail = s2;	// array의 끝을 넘었으면, s2가 tail의 값이다
		}
		else if (q->tail + s1 >= QSIZE)	// array의 끝까지 복사했으면
			q->tail = 0;	// tail을 array의 맨 앞으로 설정한다
		else
			q->tail += len;	// tail을 복사한 양만큼 이동시킨다
	}

	q->ndata -= len;		/* 꺼낸 데이터의 크기만큼 감소 */

	return len;
}

// 큐에 들어있는 데이터의 크기(바이트)를 구한다
//
// Return Value :
//
// n : 큐에 들어있는 데이터의 크기 (바이트)

unsigned int get_cqueue_size(CIRCLE_QUEUE *q)
{
	assert(q != NULL);

	return q->ndata;
}

// 큐의 빈 공간의 크기를 구한다
//
// Return Value :
//
// n : 큐의 빈 공간의 크기 (바이트)
unsigned int get_cqueue_free(CIRCLE_QUEUE *q)
{
	return QSIZE - q->ndata;
}

#ifndef NDEBUG

/*
* 원형큐를 출력한다
*/
void print_cqueue(CIRCLE_QUEUE *q)
{
	int head, tail;

	assert(q != NULL);

	head = q->head;
	tail = q->tail;
	printf("Circle Queue (%u, %u, %u) : ", q->head, q->tail, q->ndata);
	while (head != tail)
	{
		putchar((isprint(q->data[tail])) ? q->data[tail] : '.');
		if (tail < QSIZE - 1)
			tail++;
		else
			tail = 0;
	}
	putchar('\n');
}

#endif
