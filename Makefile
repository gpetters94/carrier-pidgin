CC=gcc
CFLAGS=-Wall `pkg-config --cflags --libs glib-2.0` -Iheaders -shared -fPIC
SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst src/%.c, bin/%.o, $(SOURCES))
HEADERS=$(wildcard headers/*.h)

plugin: bin_dir $(OBJECTS)
	$(CC) -shared -o carrier-pidgin.so $(OBJECTS)

bin/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean install uninstall bin_dir

bin_dir:
	@mkdir -p bin

clean:
	rm -rf bin
	rm -f *.so *.o

install:
	mkdir -p ~/.purple/plugins
	cp -t ~/.purple/plugins *.so

uninstall:
	rm -f ~/.purple/plugins/carrier-pidgin.so
