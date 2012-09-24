/* 
 * Copyright (C) 2005 Han, Sang Heon.
 * This file is part of the Bookworm Library.
 */

/**
 * @file    dump.h
 * @brief   데이터 내용 모니터 함수
 * @author  한상헌 (bkwormkr@yahoo.co.kr)
 * @date    2005-07-12
 * @bug     없음
 * @warning 없음
 */

#ifndef __DUMP_H
#define __DUMP_H

// 데이터 내용을 hex dump 하여 출력한다
int bw_dump(FILE *fp, void *data, size_t size, const char *msg);

#endif

/* vim: set tabstop=4 shiftwidth=4 foldmethod=marker: */
