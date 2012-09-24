/*
* queue.c - 매우 단순한 큐
*/

#include <unistd.h>
#include "queue.h"

/*
* 큐 안의 모든 데이터를 삭제한다
*/
void reset_queue(QUEUE *q)
{
	q->read = q->write = 0;
}

/*
* 큐에 데이터를 하나 추가한다
*/
int put_qdata(QUEUE *q, void *qdata)
{
	if (q->write >= QSIZE)		/* 큐가 가득 찼음 */
		return 1;

	q->qarray[q->write++] = qdata;

	return 0;
}

/*
* 큐에서 데이터를 하나 읽는다
*/
void *get_qdata(QUEUE *q)
{
	if (q->read >= q->write)	/* 큐가 비어있음 */
		return NULL;

	return q->qarray[q->read++];
}
