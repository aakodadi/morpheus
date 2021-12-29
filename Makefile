.PHONY: all

all: bin/morpheus

bin/morpheus: src/morpheus.c
	$(CC) -o bin/morpheus src/morpheus.c -luuid -lm
