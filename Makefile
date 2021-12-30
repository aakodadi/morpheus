CXX=g++
STANDARD=c++20 -pedantic-errors
CFLAGS= -Wall -Wextra -Werror -std=$(STANDARD) -s

.PHONY: all clean makedirs

all: makedirs bin/morpheus

bin/morpheus: bin/morpheus.o
	$(CXX) $(CFLAGS) -lm -lpthread -o $@ $<

bin/morpheus.o: src/morpheus.c
	$(CXX) -c $(CFLAGS) -o $@ $<

makedirs:
	mkdir -p bin

clean:
	$(RM) -r bin