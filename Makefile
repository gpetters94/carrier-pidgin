CC=gcc

plugin:
	$(CC) -shared -o carrier-pidgin.so src/carrier-pidgin.c

clean:
	rm -f *.so *.o
