CC = g++

FLAG = -w -ggdb

test: test.o bintree.o
	$(CC) $(FLAG) -o test test.o bintree.o

test.o: test.cc bintree.h
	$(CC) $(FLAG) -c test.cc

bintree.o: bintree.cc bintree.h
	$(CC) $(FLAG) -c bintree.cc
