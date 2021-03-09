CFLAGS=-Wall -pedantic -g -Werror
PREFIX=/usr/local
VERSION=0

all: trinity 

trinity: trinity.c data.h
	$(CC) $(CFLAGS) $^ -O3 -o $@
	$(CC) -fPIC -shared -o trinity.so trinity.c

bindata: bindata.c
	$(CC) -o $@
	./$@

.PHONY: clean
clean:
	rm trinity bindata

.PHONY: install
install: trinity 
	cp $< $(PREFIX)/bin/trinity
	chmod +x $(PREFIX)/bin/trinity
	cp trinity.so $(PREFIX)/lib/libtrinity.so.$(VERSION)

.PHONY: uninstall 
uninstall:
	rm $(PREFIX)/bin/trinity