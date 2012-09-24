/*
 * base64.c - base64 encoding library
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "base64.h"

const unsigned char base64code[] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
    'w', 'x', 'y', 'z', '0', '1', '2', '3', 
    '4', '5', '6', '7', '8', '9', '+', '/'
};

void ingrp2outgrp(unsigned char outgrp[], unsigned char ingrp[], int size)
{
    assert(size > 0);

    switch (size)
    {
        case 1 :
            ingrp[1] = '\0';
        case 2 :
            ingrp[2] = '\0';
            break;
        default :
            break;
    }

    outgrp[0] = ingrp[0] >> 2;
    outgrp[1] = (ingrp[0] & 0x3) << 4 | ingrp[1] >> 4;
    outgrp[2] = (ingrp[1] & 0xf) << 2 | ingrp[2] >> 6;
    outgrp[3] = ingrp[2] & 0x3f;

    switch (size)
    {
        case 1 :
            outgrp[2] = '=';
        case 2 :
            outgrp[3] = '=';
            break;
        default :
            break;
    }
}

void conv_base64_outgrp(unsigned char outgrp[], int size)
{
    int i;

    for (i = 0; i < 1 + size; i++)
        outgrp[i] = base64code[outgrp[i]];
}

int sbase64(char *dest, char *src, size_t n)
{
    unsigned char ingrp[3];
    unsigned char outgrp[4];
    int size;
    int i;
    int count;
    int nsize;

    nsize = 0;
    for (count = 0, size = 3; *src && size == 3; src += 3, count++)
    {
        ingrp[0] = *src;
        ingrp[1] = *(src + 1);
        ingrp[2] = *(src + 2);
        if (ingrp[1] == '\0')
            size = 1;
        else if (ingrp[2] == '\0')
            size = 2;
        ingrp2outgrp(outgrp, ingrp, size);
        conv_base64_outgrp(outgrp, size);
        for (i = 0; i < 4; i++)
        {
            if (n <= 0)
                return -1;
            *dest++ = outgrp[i];
            n--;
        }
        nsize += 4;

        /* base64 인코딩에서 각 라인은 76 캐릭터를 넘지 못한다 */
        if (*(src + 3) && count == WIDTH)
        {
            count = 0;
            if (n <= 1)
                return -1;
            *dest++ = '\r';
            *dest++ = '\n';
            n -= 2;
            nsize += 2;
        }
        else
            count++;
    }

    if (n <= 0)
        return -1;

    *dest = '\0';

    return nsize;
}

int fbase64(int out, int in)
{
    unsigned char ingrp[3];
    unsigned char outgrp[4];
    int size;
    int count;
    char crlf[] = "\r\n";
    int nsize;

    nsize = 0;

    for (count = 0, size = 3; size == 3;)
    {
        size = read(in, ingrp, 3);

        if (size == -1)
            return 1;
        if (size == 0)
            break;

        ingrp2outgrp(outgrp, ingrp, size);
        conv_base64_outgrp(outgrp, size);
        
        if (write(out, outgrp, 4) != 4)
            return 1;
        else
            nsize += 4;

        /* base64 인코딩에서 각 라인은 76 캐릭터를 넘지 못한다 */
        if (count == WIDTH)
        {
            count = 0;
            if (write(out, crlf, 2) != 2)
                return 1;
            else
                nsize += 2;
        }
        else
            count++;
    }

    return nsize;
}
