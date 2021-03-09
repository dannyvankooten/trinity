CFLAGS=-Wall -pedantic -g -Werror
PREFIX=/usr/local

trinity: trinity.c data.h
	$(CC) $(CFLAGS) $^ -O3 -o $@

.PHONY: clean
clean:
	rm trinity

.PHONY: install
install: trinity 
	cp $< $(PREFIX)/bin/trinity
	chmod +x $(PREFIX)/bin/trinity

.PHONY: uninstall 
uninstall:
	rm $(PREFIX)/bin/trinity