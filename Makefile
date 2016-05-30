EXEC = NodeTest
CC=g++
CFLAGS=-Wall -std=c++11
BIN = $(filter-out $(EXEC).cpp, $(wildcard *.cpp))
BINFILES = $(BIN:.cpp=.o)

all: main

objects/%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $<

main: $(BINFILES)  $(EXEC).cpp
	$(CC) $(CFLAGS) $(BINFILES) $(EXEC).cpp -o $(EXEC)

clean:
	rm -f $(wildcard *.o) $(EXEC)

test:

.PHONY: clean main
