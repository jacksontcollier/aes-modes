all: aes-modes.o cbc-enc ctr-enc cbc-dec ctr-dec

aes-modes.o: aes-modes.h aes-modes.c
	gcc -c aes-modes.c -o aes-modes.o

cbc-enc: cbc-enc.o aes-modes.o aes-modes.h
	gcc cbc-enc.o aes-modes.o -o cbc-enc

ctr-enc: ctr-enc.o aes-modes.o aes-modes.h
	gcc ctr-enc.o aes-modes.o -o ctr-enc

cbc-dec: cbc-dec.o aes-modes.o aes-modes.h
	gcc cbc-dec.o aes-modes.o -o cbc-dec

ctr-dec: ctr-dec.o aes-modes.o aes-modes.h
	gcc ctr-dec.o aes-modes.o -o cbc-dec

cbc-enc.o: cbc-enc.c aes-modes.o aes-modes.h
	gcc -c cbc-enc.c -o cbc-enc.o

ctr-enc.o: ctr-enc.c aes-modes.o aes-modes.h
	gcc -c ctr-enc.c -o ctr-enc.o

cbc-dec.o: cbc-dec.c aes-modes.o aes-modes.h
	gcc -c cbc-dec.c -o cbc-dec.o

ctr-dec.o: ctr-dec.c aes-modes.o aes-modes.h
	gcc -c ctr-dec.c -o ctr-dec.o
