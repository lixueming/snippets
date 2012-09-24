.SUFFIXES : .c .o

CC = gcc

INC = 
LIBS = 
CFLAGS = -Wall -D_THREAD_SAFE $(INC)

OBJS = cqueue.o testcq.o
SRCS = cqueue.c testcq.c

TARGET = testcq

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) -lpthread

dep :
	gccmakedep $(INC) $(SRCS)

clean :
	rm -rf $(OBJS) $(TARGET) core

new : 
	$(MAKE) clean 
	$(MAKE) 
