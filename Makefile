EXEC = persistanceTest
CC=g++
CFLAGS=-Wall -std=c++11
BINFILES = $(wildcard *.o)

COMMON_PATH = ./Common/
DATA_ACCESS_PATH = ./DataAccess/
LOGIC_PATH = ./Logic/
UTILS_PATH = ./Utils/
TESTS_PATH = ./Tests/

COMMON_BIN = $(wildcard $(COMMON_PATH)*.cpp)
DATA_ACCESS_BIN = $(wildcard $(DATA_ACCESS_PATH)*.cpp)
LOGIC_BIN = $(wildcard $(LOGIC_PATH)*.cpp)
UTILS_BIN = $(wildcard $(UTILS_PATH)*.cpp)

all: main

persistance:
	$(CC) $(CFLAGS) -c $(DATA_ACCESS_BIN)

common:
	$(CC) $(CFLAGS) -c $(COMMON_BIN)

test: common persistance
	$(CC) $(CFLAGS) $(BINFILES) $(TESTS_PATH)$(EXEC).cpp -o $(EXEC) -lgtest -lgtest_main

.PHONY: clean main
