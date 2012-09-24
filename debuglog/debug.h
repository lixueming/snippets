/* 
 * Copyright (C) 2004 Han, Sang Heon.
 * This file is part of the Ranker.
 */

/**
 * @file    debug.h
 * @brief   debug message를 syslogd deamon을 통해 출력한다
 * @author  한상헌 (bkwormkr@yahoo.co.kr)
 * @date    2005-04-26
 * @bug     없음
 * @warning 없음
 */

#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef NDEBUG					// 디버깅 메시지를 출력하지 않으면

#define __DEBUG_VOID_CAST       (void)

#define debug_open(facility, ident)	(__DEBUG_VOID_CAST (0))
#define debug_close()         		(__DEBUG_VOID_CAST (0))
#define debug_msg(msg)          	(__DEBUG_VOID_CAST (0))

#else

#include <syslog.h>

// syslogd와 연결한다
#define debug_open(ident, facility)	(syslog((ident), LOG_CONS | LOG_NDELAY, (facility)))
#define debug_close()         		(closelog())
#define debug_msg(msg)          	()

// syslogd와 끊는다
void debug_close(void);


#endif  // #ifdef NDEBUG

#endif  // #ifndef __DEBUG_H

/* vim: set tabstop=4 shiftwidth=4 foldmethod=marker: */
