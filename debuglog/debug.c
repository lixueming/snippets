/* 
 * Copyright (C) 2004 Han, Sang Heon.
 * This file is part of the Ranker.
 */

/**
 * @file    debug.c
 * @brief   디버깅 메시지를 표준 에러 출력 또는 파일로 내보낸다
 * @author  한상헌 (bkwormkr@yahoo.co.kr)
 * @date    2004-12-22
 * @bug     없음
 * @warning 없음
 */

#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>

#include "datetime.h"
#include "debug.h"

#ifndef NO_DEBUG_MSG    // 디버깅 메시지를 출력하면

static int debug_fd = STDERR_FILENO;    ///< 디버깅 출력 파일 디스크립터
static char debug_msg_buf[MAX_DEBUG_MSG_LEN];  ///< 디버깅 메시지 버퍼
static char debug_now_buf[NOW_LEN];            ///< 디버깅 시각 출력 버퍼

/**
 * @fn      debug_init
 * @brief   디버깅 메시지를 출력 할 파일 디스크립터를 얻는다
 * @param   filename 디버깅 메시지 출력 파일명
 * @return  디버깅 메시지 출력 파일 디스크립터
 * @retval  0 에러 없음
 * @retval  1 에러 있음
 */
int debug_init(const char *filename)
{
#ifdef DEBUG_MSG_TO_FILE
    int fd;
    int flags;
    mode_t mode;

    assert(filename != NULL);

    flags = O_RDWR | O_CREAT | O_APPEND | O_SYNC;
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    fd = open(filename, flags, mode);

    if (fd == -1)   // 파일을 열지 못했으면
        return 1;

    debug_fd = fd;
#else
    debug_fd = STDERR_FILENO;   // 디버깅 메시지를 표준 에러 출력으로 보낸다
#endif

    return 0;
}

/**
 * @fn      debug_relase
 * @brief   디버깅 메시지를 출력 할 파일 디스크립터를 지운다
 * @param   없음
 * @return  없음
 */
void debug_release(void)
{
#ifdef DEBUG_MSG_TO_FILE       // 표준 에러 출력은 닫으면 안 된다
    close(debug_fd);
#endif
}

/**
 * @fn      debug_msg
 * @brief   디버깅 메시지를 출력한다
 * @param   msg 디버깅 메시지
 * @return  없음
 */
void debug_msg(const char *msg)
{
    int len;

    assert(msg != NULL);

    len = strlen(msg);
    write(debug_fd, msg, len);
}

/**
 * @fn      debug_tmsg
 * @brief   현재 시각이 붙은 디버깅 메시지를 출력한다
 * @param   msg 디버깅 메시지
 * @return  없음
 */
void debug_tmsg(const char *msg)
{
    assert(msg != NULL);

    debug_msgf("%s %s", getnow(debug_now_buf), msg);
}

#endif  // #ifndef NO_DEBUG_MSG

/**
 * @fn      debug_msgf
 * @brief   형식화한(formatted) 디버깅 메시지를 출력한다
 * @param   format 형식
 * @param   ... 가변 파라미터
 * @return  없음
 */
void debug_msgf(const char *format, ...)
{
#ifndef NO_DEBUG_MSG
    va_list ap; ///< 가변 인자 리스트

    assert(format != NULL);

    va_start(ap, format);
    vsnprintf(debug_msg_buf, MAX_DEBUG_MSG_LEN, format, ap);
    debug_msg(debug_msg_buf);
    va_end(ap);
#endif
}

/**
 * @fn      debug_tmsgf
 * @brief   현재 시각이 붙은 형식화한(formatted) 디버깅 메시지를 출력한다
 * @param   format 형식
 * @param   ... 가변 파라미터
 * @return  없음
 */
void debug_tmsgf(const char *format, ...)
{
#ifndef NO_DEBUG_MSG
    va_list ap; ///< 가변 인자 리스트

    assert(format != NULL);

    debug_tmsg("");    // 현재 시각을 출력한다

    va_start(ap, format);
    vsnprintf(debug_msg_buf, MAX_DEBUG_MSG_LEN, format, ap);
    debug_msg(debug_msg_buf);
    va_end(ap);
#endif
}
