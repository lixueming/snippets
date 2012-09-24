/* 
 * Copyright (C) 2005 Han, Sang Heon.
 * This file is part of the Bookworm Library.
 */

/**
 * @file    dump.c
 * @brief   데이터 내용 모니터 함수
 * @author  한상헌 (bkwormkr@yahoo.co.kr)
 * @date    2005-07-12
 * @bug     없음
 * @warning 없음
 */

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#include "dump.h"

#define DUMP_BYTES		16						///< 한 줄에 들어가는 바이트수
#define DUMP_HEADER		"-- FD = %d, %s ---------------------\n"

/**
 * @fn      bw_dump
 * @brief   데이터 내용을 hex dump 하여 출력한다
 * @param   fp 파일 스트림 포인터
 * @param   data 데이터 포인터
 * @param   size 데이터 크기
 * @param   msg  출력 메시지
 * @return  출력한 바이트수
 * @retval  -1 오류
 */
int bw_dump(FILE *fp, void *data, size_t size, const char *msg)
{
	int total_output_bytes = 0;		///< 지금까지 출력한 전체 바이트수
	int output_bytes = 0;			///< 출력한 바이트수
	int i = 0;						///< 현재 출력 중인 위치 (DUMP_BYTES 단위)
	int j = 0;						///< 현재 출력 중인 위치 (1 바이트 단위)
	char ch;

	assert(fp != 0);
	assert(data != NULL);
	assert(size >= 0);

	output_bytes = fputs(msg, fp);
	if (output_bytes < 0)
		return output_bytes;
	total_output_bytes += output_bytes;


	for (i = 0; i < size; i += DUMP_BYTES)
	{
		// 주소 출력
		output_bytes = fprintf(fp, "0x%04X  ", i);
		if (output_bytes < 0)
			return output_bytes;
		total_output_bytes += output_bytes;

		// 데이터 출력
		for (j = 0; i + j < size && j < DUMP_BYTES; j++)
		{
			ch = *((char *) data + i + j);
			output_bytes = fprintf(fp, "%02hhX ", ch);
			if (output_bytes < 0)
				return output_bytes;
			total_output_bytes += output_bytes;
		}

		// 모자란 것이 있으면 공백 출력
		for (; j < DUMP_BYTES; j++)
		{
			output_bytes = fputs("   ", fp);
			if (output_bytes < 0)
				return output_bytes;
			total_output_bytes += output_bytes;
		}

		// 문자 출력
		output_bytes = fputc(' ', fp);		// 공백 1칸 출력
		if (output_bytes < 0)
			return output_bytes;
		total_output_bytes += output_bytes;
		for (j = 0; i + j < size && j < DUMP_BYTES; j++)
		{
			ch = *((char *) data + i + j);
			if (isprint(ch))
				output_bytes = fputc(ch, fp);
			else
				output_bytes = fputc(' ', fp);
			if (output_bytes < 0)
				return output_bytes;
			total_output_bytes += output_bytes;
		}

		output_bytes = fputc('\n', fp);
		if (output_bytes < 0)
			return output_bytes;
		total_output_bytes += output_bytes;
	}

	return total_output_bytes;
}

/* vim: set tabstop=4 shiftwidth=4 foldmethod=marker: */
