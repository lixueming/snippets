/*
 * base64.h - base64 encoding library
 */

#ifndef __BASE64_H
#define __BASE64_H

#define WIDTH   17

int sbase64(char *dest, char *src, size_t n);
int fbase64(int out, int in);

#endif
