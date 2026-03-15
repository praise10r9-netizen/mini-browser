CC=gcc
CFLAGS=-Wall -O2

SRC=src/main.c src/net.c src/http.c src/url.c src/html.c src/dom.c src/renderer.c

browser:
	$(CC) $(CFLAGS) $(SRC) -o browser
