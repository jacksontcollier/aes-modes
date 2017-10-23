CC = gcc
CFLAGS = -Wall
TARGET_EXE = $(BIN_DIR)/cbc-enc $(BIN_DIR)/ctr-enc $(BIN_DIR)/cbc-dec $(BIN_DIR)/ctr-dec \
	     cbc-enc cbc-dec ctr-enc ctr-dec
LFLAGS = -lssl -lcrypto -lpthread
BIN_DIR = bin
SRC_DIR = src

.PHONY: all
all: BUILD_DIRECTORIES $(TARGET_EXE)

.PHONY: clean
clean:
	rm -rf bin cbc-enc cbc-dec ctr-enc ctr-dec

BUILD_DIRECTORIES:
	$(shell mkdir -p bin)

cbc-enc: $(BIN_DIR)/cbc-enc
	$(shell ln -s $(BIN_DIR)/cbc-enc cbc-enc)

cbc-dec: $(BIN_DIR)/cbc-dec
	$(shell ln -s $(BIN_DIR)/cbc-dec cbc-dec)

ctr-enc: $(BIN_DIR)/ctr-enc
	$(shell ln -s $(BIN_DIR)/ctr-enc ctr-enc)

ctr-dec: $(BIN_DIR)/ctr-dec
	$(shell ln -s $(BIN_DIR)/ctr-dec ctr-dec)

$(BIN_DIR)/cbc-enc: $(BIN_DIR)/cbc-enc.o $(BIN_DIR)/aes-modes.o
	$(CC) $(BIN_DIR)/cbc-enc.o $(BIN_DIR)/aes-modes.o $(LFLAGS) -o $(BIN_DIR)/cbc-enc

$(BIN_DIR)/ctr-enc: $(BIN_DIR)/ctr-enc.o $(BIN_DIR)/aes-modes.o
	$(CC) $(BIN_DIR)/ctr-enc.o $(BIN_DIR)/aes-modes.o $(LFLAGS) -o $(BIN_DIR)/ctr-enc

$(BIN_DIR)/cbc-dec: $(BIN_DIR)/cbc-dec.o $(BIN_DIR)/aes-modes.o
	$(CC) $(BIN_DIR)/cbc-dec.o $(BIN_DIR)/aes-modes.o $(LFLAGS) -o $(BIN_DIR)/cbc-dec

$(BIN_DIR)/ctr-dec: $(BIN_DIR)/ctr-dec.o $(BIN_DIR)/aes-modes.o
	$(CC) $(BIN_DIR)/ctr-dec.o $(BIN_DIR)/aes-modes.o $(LFLAGS) -o $(BIN_DIR)/ctr-dec

$(BIN_DIR)/cbc-enc.o: $(SRC_DIR)/cbc-enc.c $(SRC_DIR)/aes-modes.h
	$(CC) -c $(CFLAGS) $(SRC_DIR)/cbc-enc.c -o $(BIN_DIR)/cbc-enc.o

$(BIN_DIR)/ctr-enc.o: $(SRC_DIR)/ctr-enc.c $(SRC_DIR)/aes-modes.h
	$(CC) -c $(CFLAGS) $(SRC_DIR)/ctr-enc.c -o $(BIN_DIR)/ctr-enc.o

$(BIN_DIR)/cbc-dec.o: $(SRC_DIR)/cbc-dec.c $(SRC_DIR)/aes-modes.h
	$(CC) -c $(CFLAGS) $(SRC_DIR)/cbc-dec.c -o $(BIN_DIR)/cbc-dec.o

$(BIN_DIR)/ctr-dec.o: $(SRC_DIR)/ctr-dec.c $(SRC_DIR)/aes-modes.h
	$(CC) -c $(CFLAGS) $(SRC_DIR)/ctr-dec.c -o $(BIN_DIR)/ctr-dec.o

$(BIN_DIR)/aes-modes.o: $(SRC_DIR)/aes-modes.h $(SRC_DIR)/aes-modes.c
	$(CC) -c $(CFLAGS) $(SRC_DIR)/aes-modes.c -o $(BIN_DIR)/aes-modes.o
