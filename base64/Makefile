test:	test.o base64.o
	gcc -g -o test test.o base64.o

test.o:	test.c base64.h
	gcc -Wall -g -c test.c

base64.o:	base64.c base64.h
	gcc -Wall -g -c base64.c

clean:
	rm -f test test.o base64.o
