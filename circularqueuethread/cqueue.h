/*
* cqueue.h - 원형 큐
*/

#ifndef __CQUEUE_H
#define __CQUEUE_H

#include <pthread.h>

#define KBYTE	1024		/* 1 KByte */
#define QSIZE	8 * KBYTE	/* 8 KByte */

#ifndef NDEBUG

#define QSIZE	10

#endif

#define CQUEUE_NEXT(i) (((i) < QSIZE - 1) ? (i) + 1 : 0)

/* 큐의 상태 */
enum QUEUE_EMPTY_STATUS {QUEUE_NOT_EMPTY = 0, QUEUE_EMPTY = 1};
enum QUEUE_FULL_STATUS {QUEUE_NOT_FULL = 0, QUEUE_FULL = 1};

/* 원형 큐 타입 */
typedef struct _circle_queue
{
	char data[QSIZE];			/* 큐 버퍼 */
	unsigned int head;			/* 쓰는 위치 */
	unsigned int tail;			/* 읽는 위치 */
	unsigned int ndata;			/* 데이터의 크기 */
	pthread_mutex_t lock;
} CIRCLE_QUEUE;

CIRCLE_QUEUE *alloc_cqueue(void);	// 원형 큐 할당
void free_cqueue(CIRCLE_QUEUE *q);	// 원형 큐 해제
enum QUEUE_FULL_STATUS full_cqueue(CIRCLE_QUEUE *q);	// 원형큐가 꽉찼나?
enum QUEUE_EMPTY_STATUS empty_cqueue(CIRCLE_QUEUE *q);	// 원형큐가 비었나?
int put_cqueue(CIRCLE_QUEUE *q, char *buf, int len);	// 원형큐에 데이터 추가
int get_cqueue(CIRCLE_QUEUE *q, char *buf, int len);	// 원형큐에서 데이터 가져옴
unsigned int get_cqueue_size(CIRCLE_QUEUE *q);	// 원형큐의 데이터 크기

#ifndef NDEBUG

void print_cqueue(CIRCLE_QUEUE *q);

#endif	// #ifndef NDEBUG

#endif
