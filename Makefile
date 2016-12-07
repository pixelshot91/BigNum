CXX=g++
CPPFLAGS=-I"src"
CXXFLAGS=-Wall -Wextra -pedantic -std=c++14 -O3

VPATH=src
SRC=main.cc

BIN=bistro

OBJ=$(SRC:.cc=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(OBJ) $(BIN) vgcore.*

.PHONY: clean check all
