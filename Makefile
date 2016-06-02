EXEC = nodeTest
CC=g++
CFLAGS=-Wall -std=c++11
BIN = $(filter-out $(EXEC).cpp, $(wildcard *.cpp))
BINFILES = $(BIN:.cpp=.o)

COMMON_PATH = ./Common/
DATA_ACCESS_PATH = ./DataAccess/
LOGIC_PATH = ./Logic/
UTILS_PATH = ./Utils/

COMMON_BIN = $(wildcard ./Common/*.cpp)
DATA_ACCESS_BIN = ./DataAccess/
LOGIC_BIN = ./Logic/
UTILS_BIN = ./Utils/

TEST = ./Tests/

LIB = ./lib/

LIB_TEST = ./DistTest/

all: main


dataAccess:
	$(CC) $(CFLAGS) -c $(DATA_ACCESS_PATH)  $<

logic:
	$(CC) $(CFLAGS) -c $(LOGIC_PATH)  $<

$(COMMON_PATH)%.o: $(COMMON_PATH)%.cpp $(COMMON_PATH)%.hpp
	$(CC) $(CFLAGS) -c $(COMMON_BIN)

main: $(BINFILES)  $(EXEC).cpp
	$(CC) $(CFLAGS) $(BINFILES) $(EXEC).cpp -o $(EXEC)

common:
	$(CC) $(CFLAGS) -c $(COMMON_BIN)

test: common
	$(CC) $(CFLAGS) Node.o $(TEST)$(EXEC).cpp -o $(EXEC)

.PHONY: clean main
