TREE_TEST_EXEC = treeTest
REGISTER_TEST_EXEC = registerTest
PERSITANCE_TEST_EXEC = persistanceTest
PROGRAM_NAME = program
CC=g++
CFLAGS=-Wall -std=c++11
BINFILES = $(wildcard *.o)

COMMON_PATH = ./Common/
DATA_ACCESS_PATH = ./DataAccess/
LOGIC_PATH = ./Logic/
UTILS_PATH = ./Utils/
TESTS_PATH = ./Tests/
PROGRAM_PATH = ./Program/

COMMON_BIN = $(wildcard $(COMMON_PATH)*.cpp)
DATA_ACCESS_BIN = $(wildcard $(DATA_ACCESS_PATH)*.cpp)
LOGIC_BIN = $(wildcard $(LOGIC_PATH)*.cpp)
UTILS_BIN = $(wildcard $(UTILS_PATH)*.cpp)
PROGRAM = $(wildcard $(PROGRAM_PATH)*.cpp)

all: main

main: common persistance logic
	$(CC) $(CFLAGS) $(BINFILES) $(PROGRAM) -o $(PROGRAM_NAME) -lboost_program_options

persistance:
	$(CC) $(CFLAGS) -c $(DATA_ACCESS_BIN)

common:
	$(CC) $(CFLAGS) -c $(COMMON_BIN)

logic:
	$(CC) $(CFLAGS) -c $(LOGIC_BIN)


treeTest: common persistance logic
	$(CC) $(CFLAGS) $(BINFILES) $(TESTS_PATH)$(TREE_TEST_EXEC).cpp -o $(TREE_TEST_EXEC) -lgtest -lgtest_main

persistanceTest: common persistance
	$(CC) $(CFLAGS) $(BINFILES) $(TESTS_PATH)$(PERSITANCE_TEST_EXEC).cpp -o $(PERSITANCE_TEST_EXEC) -lgtest -lgtest_main


registerTest: common
	$(CC) $(CFLAGS) $(BINFILES) $(TESTS_PATH)$(REGISTER_TEST_EXEC).cpp -o $(REGISTER_TEST_EXEC) -lgtest -lgtest_main

.PHONY: clean main
