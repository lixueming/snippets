.SUFFIXES : .c .o

CC = gcc -g

INC = 
LIBS = 
CFLAGS = -Wall $(INC)

OBJS = cqueue.o mtestcq.o
SRCS = cqueue.c mtestcq.c

TARGET = mtestcq

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -g -o $@ $(OBJS) $(LIBS)

dep :
	gccmakedep $(INC) $(SRCS)

clean :
	rm -rf $(OBJS) $(TARGET) core

new : 
	$(MAKE) clean 
	$(MAKE) 
