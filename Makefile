CC=gcc
CFLAGS=-Wall -O2

SRC=src/main.c src/net.c src/http.c

browser:
	$(CC) $(CFLAGS) $(SRC) -o browser
