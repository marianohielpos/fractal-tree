EXEC = NodeTest
CC=g++
CFLAGS=-Wall -std=c++11
BIN = $(filter-out $(EXEC).cpp, $(wildcard *.cpp))
BINFILES = $(BIN:.cpp=.o)

COMMON = ./Common
DATA_ACCESS = ./DataAccess
LOGIC = ./Logic
UTILS = ./Utils

TESTS = ./Test

DIST_TEST = ./DistTest

all: main

objects/%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $<

main: $(BINFILES)  $(EXEC).cpp
	$(CC) $(CFLAGS) $(BINFILES) $(EXEC).cpp -o $(EXEC)

clean:
	rm -f $(wildcard *.o) $(EXEC)

testNode: $(COMMON)$(BINFILES) $(TEST)$(EXEC).cpp
	$(CC) $(CFLAGS) $(COMMON)$(BINFILES) $(TEST)$(BINFILES) $(TEST)$(EXEC)$(EXEC).cpp -o $(DIST_TEST)$(EXEC)

.PHONY: clean main
