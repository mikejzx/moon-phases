OUT=lunar
SRC=main.c
CFLAGS=-O3
LDFLAGS=-lm
CC=gcc

all: $(OUT)

run: all
	./$(OUT)

$(OUT): $(SRC) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

