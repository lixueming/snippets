/*
* queue.h - 매우 단순한 큐
*/

#ifndef __QUEUE_H
#define __QUEUE_H

#define QSIZE	1000	/* 큐의 크기 */

typedef struct _QUEUE
{
	void 	*qarray[QSIZE];	/* 큐 데이터 어레이 */
	int		read;			/* 큐 읽기 인덱스 */
	int		write;			/* 큐 쓰기 인덱스 */
} QUEUE;

void reset_queue(QUEUE *q);
int put_qdata(QUEUE *q, void *qdata);
void *get_qdata(QUEUE *q);

#endif
