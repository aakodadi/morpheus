.PHONY: all

all: bin/morpheus

bin/morpheus: src/morpheus.c
	$(CC) -Wall -Wextra -Werror -s -o bin/morpheus src/morpheus.c -lm
