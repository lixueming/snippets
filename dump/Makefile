# 
# Copyright (C) 2005 Han, Sang Heon.
# This file is part of the Say Gostop.
#

# 선처리기 정의
#DEFINE = -D_REENTRANT -DTHREADS
#DEFINE = -DNDEBUG

# C 컴파일러
CC = gcc

# 헤더(Header) 디렉토리
INC = 

# 라이브러리 디렉토리 
LIBS = 

# C 컴파일러 옵션
CFLAGS = -Wall -g $(INC)

# 링킹 라이브러리
LINKLIB = 

all:	test_dump fdump

lib:
	gcc $(INC) -Wall -g -c dump.c
	ar rcs libdump.a dump.o

test_dump:	test_dump.c dump.c
	gcc $(INC) -Wall -g -c dump.c
	gcc $(INC) -Wall -g -c test_dump.c
	gcc -g -o test_dump test_dump.o dump.o

fdump:	fdump.c dump.c
	gcc $(INC) -Wall -g -c dump.c
	gcc $(INC) -Wall -g -c fdump.c
	gcc -g -o fdump fdump.o dump.o

clean:
	rm -f test_dump.o test_dump fdump fdump.o dump.o libdump.a

new:
	$(MAKE) clean
	$(MAKE)
