/* 
 * Copyright (C) 2005 Han, Sang Heon.
 * This file is part of the Bookworm Library.
 */

/**
 * @file    test_dump
 * @brief   bw_dump() 함수를 시험한다
 * @author  한상헌 (bkwormkr@yahoo.co.kr)
 * @date    2005-07-12
 * @bug     없음
 * @warning 없음
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dump.h"

#define DATA_SIZE 1000

/**
 * @fn      main
 * @brief   test_dump 프로그램 메인 함수
 * @param   없음
 * @return  결과값
 * @retval  EXIT_SUCCESS 성공
 */
int main(void)
{
	char      data[DATA_SIZE];
	FILE     *fp;
	int       i;

	srand(time(NULL));
	for (i = 0; i < DATA_SIZE; i++)
		data[i] = (char) (255.0 * rand() / (RAND_MAX + 1.0));

	strcpy(data + 342, "Hello?");

	fp = fopen("test_dump.txt", "w");

	bw_dump(stdout, data, DATA_SIZE, "-------- Test ---------\n");
	bw_dump(stdout, data, DATA_SIZE, "-------- Test ---------\n");
	bw_dump(stdout, data, DATA_SIZE, "-------- Test ---------\n");

	fclose(fp);

	return EXIT_SUCCESS;
}

/* vim: set tabstop=4 shiftwidth=4 foldmethod=marker: */

/* $Id: test_dump.c 7 2005-12-22 06:05:34Z bookworm $ */
