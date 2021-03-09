CFLAGS=-Wall -pedantic -g -Werror
PREFIX=/usr/local

all: trinity 

trinity: trinity.c data.h
	$(CC) $(CFLAGS) $^ -O3 -o $@

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

.PHONY: uninstall 
uninstall:
	rm $(PREFIX)/bin/trinity