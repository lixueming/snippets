/*
* testcq.c - Circle Queue Test
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "cqueue.h"

#define BUFSIZE			1024	/* 버퍼의 크기 */

#define NCTHREAD		5		/* 소비자 쓰레드의 개수 */
#define NPTHREAD		5		/* 생산자 쓰레드의 개수 */

#define NTIMES			100		/* 생산 및 소비 횟수 */

#define RNDSTR_LENGTH	20		/* 랜덤 문자열의 최대 길이 */

pthread_t ctid[NCTHREAD];		/* 소비자 쓰레드 정보 */
pthread_t ptid[NPTHREAD];		/* 생산자 쓰레드 정보 */

void *consumer(void *arg);		/* 소비자 */
void *producer(void *arg);		/* 생산자 */

char *randstr(char *buf, int len);		/* 임의의 문자열을 생성 */
char randalpha(void);					/* 임의의 영문 소문자를 생성 */
int randminmax(int min, int max);		/* min ~ max 값을 생성 */

int main(void)
{
	int tid;
	CIRCLE_QUEUE *q;
	void *retval;

	srand(time(NULL));			/* 랜덤변수 초기화 */

	/* 원형 큐 생성 */
	q = alloc_cqueue();
	if (q == NULL)
	{
		fprintf(stderr, "큐 생성 실패\n");
		exit(1);
	}

	/* Consumer 쓰레드 생성 */
	for (tid = 0; tid < NCTHREAD; tid++)
		if (pthread_create(&ctid[tid], NULL, consumer, q))
		{
			fprintf(stderr, "소비자 쓰레드 생성 실패\n");
			exit(1);
		}

	/* Producer 쓰레드 생성 */
	for (tid = 0; tid < NPTHREAD; tid++)
		if (pthread_create(&ptid[tid], NULL, producer, q))
		{
			fprintf(stderr, "생산자 쓰레드 생성 실패\n");
			exit(1);
		}

	/* Producer 쓰레드가 종료될때까지 기다린다 */
	for (tid = 0; tid < NPTHREAD; tid++)
		if (pthread_join(ptid[tid], &retval))
		{
			fprintf(stderr, "생산자 쓰레드 종료 실패\n");
			exit(1);
		}

	/* Consumer 쓰레드가 종료될때까지 기다린다 */
	for (tid = 0; tid < NCTHREAD; tid++)
		if (pthread_join(ctid[tid], &retval))
		{
			fprintf(stderr, "소비자 쓰레드 종료 실패\n");
			exit(1);
		}

	free_cqueue(q);

	return EXIT_SUCCESS;
}

void *consumer(void *arg)
{
	int i;
	char buf[BUFSIZE];
	CIRCLE_QUEUE *q = (CIRCLE_QUEUE *) arg;
	int len;
	int nget;

	for (i = 0; i < 10; i++)
	{
		printf("CONSUMER : ");
		len = randminmax(1, 100);
		nget = get_cqueue(q, buf, len);
		if (nget < len)
			printf("%d 바이트만큼 읽으려 했지만, %d 바이트만 읽음 : ", len, nget);
		*(buf + nget) = '\0';
		puts(buf);
		printf("큐의 데이터 크기 : %d\n", get_cqueue_size(q));
		usleep(100);	/* 0.1 sec */
	}

	return NULL;
}

void *producer(void *arg)
{
	int i;
	char buf[BUFSIZE];
	CIRCLE_QUEUE *q = (CIRCLE_QUEUE *) arg;
	int len;
	int nput;

	for (i = 0; i < 10; i++)
	{
		len = randminmax(1, 100);
		randstr(buf, len);
		nput = put_cqueue(q, buf, len);	
		if (nput < len)
			printf("PRODUCER : %d 바이트만큼 쓰려 했지만,  %d 바이트만 씀.\n", len, nput);
		printf("큐의 데이터 크기 : %d\n", get_cqueue_size(q));
		usleep(100);	/* 0.1 sec */
	}

	return NULL;
}

char *randstr(char *buf, int len)
{
	char *p = buf;
	
	for (; len > 0; len--)
		*p++ = randalpha();
	*p = '\0';

	return buf;
}

char randalpha(void)
{
	return 'a' + randminmax(0, 'z' - 'a');
}

int randminmax(int min, int max)
{
	return min + (int) ((max - min + 1) * 1.0 * rand() / (RAND_MAX + 1.0));
}
