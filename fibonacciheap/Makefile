CC=g++
FLAG=-Wall -ggdb
OBJ=main.o fhnode.o fibheap.o

main:	$(OBJ) 
	$(CC) $(FLAG) -o main $(OBJ)

main.o: main.cc fibheap.h
	$(CC) $(FLAG) -c main.cc

fhnode.o: fhnode.cc fibheap.h
	$(CC) $(FLAG) -c fhnode.cc

fibheap.o:	fibheap.cc fibheap.h
	$(CC) $(FLAG) -c fibheap.cc
