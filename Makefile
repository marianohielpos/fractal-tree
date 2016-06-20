TREE_TEST_EXEC = treeTest
REGISTER_TEST_EXEC = registerTest
PERSITANCE_TEST_EXEC = persistanceTest
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

logic:
	$(CC) $(CFLAGS) -c $(LOGIC_BIN)


testTree: common persistance logic
	$(CC) $(CFLAGS) $(BINFILES) $(TESTS_PATH)$(TREE_TEST_EXEC).cpp -o $(TREE_TEST_EXEC) -lgtest -lgtest_main

testPersistance: common persistance
	$(CC) $(CFLAGS) $(BINFILES) $(TESTS_PATH)$(PERSITANCE_TEST_EXEC).cpp -o $(PERSITANCE_TEST_EXEC) -lgtest -lgtest_main


testRegister: common
	$(CC) $(CFLAGS) $(BINFILES) $(TESTS_PATH)$(REGISTER_TEST_EXEC).cpp -o $(REGISTER_TEST_EXEC) -lgtest -lgtest_main

.PHONY: clean main
