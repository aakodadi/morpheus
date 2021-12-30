.PHONY: all

all: bin/morpheus

bin/morpheus: src/morpheus.c
	$(CC) -Wall -Wextra -Werror -O3 -s -o bin/morpheus src/morpheus.c -lm
