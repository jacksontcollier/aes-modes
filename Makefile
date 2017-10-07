CC = gcc
CFLAGS = -Wall
TARGET_EXE = cbc-enc ctr-enc cbc-dec ctr-dec
LFLAGS = -lssl -lcrypto -lpthread

.PHONY: all
all: $(TARGET_EXE)

.PHONY: clean
clean:
	rm -rf *.o $(TARGET_EXE)

cbc-enc: cbc-enc.o aes-modes.o
	$(CC) cbc-enc.o aes-modes.o $(LFLAGS) -o cbc-enc

ctr-enc: ctr-enc.o aes-modes.o
	$(CC) ctr-enc.o aes-modes.o $(LFLAGS) -o ctr-enc

cbc-dec: cbc-dec.o aes-modes.o
	$(CC) cbc-dec.o aes-modes.o $(LFLAGS) -o cbc-dec

ctr-dec: ctr-dec.o aes-modes.o
	$(CC) ctr-dec.o aes-modes.o $(LFLAGS) -o ctr-dec

cbc-enc.o: cbc-enc.c aes-modes.h
	$(CC) -c $(CFLAGS) cbc-enc.c -o cbc-enc.o

ctr-enc.o: ctr-enc.c aes-modes.h
	$(CC) -c $(CFLAGS) ctr-enc.c -o ctr-enc.o

cbc-dec.o: cbc-dec.c aes-modes.h
	$(CC) -c $(CFLAGS) cbc-dec.c -o cbc-dec.o

ctr-dec.o: ctr-dec.c aes-modes.h
	$(CC) -c $(CFLAGS) ctr-dec.c -o ctr-dec.o

aes-modes.o: aes-modes.h aes-modes.c
	$(CC) -c $(CFLAGS) aes-modes.c -o aes-modes.o
