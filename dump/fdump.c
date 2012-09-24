/* 
 * Copyright (C) 2005 Han, Sang Heon.
 * This file is part of the Bookworm Library.
 */

/**
 * @file    test_dump
 * @brief   bw_dump() 함수를 시험한다
 * @author  한상헌 (bkwormkr@yahoo.co.kr)
 * @date    2006-01-03
 * @bug     없음
 * @warning 없음
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "dump.h"

#define MAX_HEADER_LEN		80		///< 헤더 최대 길이

/**
 * @fn      main
 * @brief   파일을 16 진수 덤프한다
 * @param   없음
 * @return  결과값
 * @retval  EXIT_SUCCESS 성공
 */
int main(int argc, char *argv[])
{
	FILE *fp;						///< 파일 디스크립터 포인터
	unsigned char *data;			///< 데이터 포인터
	struct stat stat_buf;
	char header[MAX_HEADER_LEN];	///< 덤프 화면 머리글

	if (argc != 2)
	{
		fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
		exit(1);
	}

	if (stat(argv[1], &stat_buf))
	{
		fprintf(stderr, "'%s' 파일 정보를 알 수 없습니다.\n", argv[1]);
		exit(1);
	}

	data = (unsigned char *) malloc(stat_buf.st_size);
	if (data == NULL)
	{
		fprintf(stderr, "메모리를 할당 할 수 없습니다.\n");
		exit(1);
	}

	fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		fprintf(stderr, "'%s' 파일을 열 수 없습니다.\n", argv[1]);
		free(data);
		exit(1);
	}
	if (fread(data, stat_buf.st_size, 1, fp) != 1)
	{
		fprintf(stderr, "'%s' 파일을 읽을 수 없습니다.\n", argv[1]);
		free(data);
		fclose(fp);
		exit(1);
	}

	fclose(fp);

	snprintf(header, MAX_HEADER_LEN, "-- Filename: %s --\n", argv[1]);
	bw_dump(stdout, data, stat_buf.st_size, header);
	free(data);

	return EXIT_SUCCESS;
}

/* vim: set tabstop=4 shiftwidth=4 foldmethod=marker: */

/* $Id: fdump.c 10 2006-01-03 08:25:33Z bookworm $ */
