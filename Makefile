# G++ is for the GCC compiler for C++
PP := g++

# CXXFLAGS are the compiler flages for when we compile C++ code in this course 
FLAGS := -O2 -g -Wall -Wextra -Wconversion  -pedantic
CXXFLAGS := -m64 -std=c++11 -lX11 $(FLAGS)

# Variables for Folders
INC := inc
SRC := src
OBJ := obj
TEST = tests
EXE = exe


# Test to see if edges are working
MST: MSTEXE
	$(EXE)/MSTEXE $(TEST)/test1.json

MSTEXE : $(OBJ)/main.o
	$(PP) $(CXXFLAGS) -o exe/$@ $< -I single_include

$(OBJ)/%.o : $(SRC)/%.cpp
	$(PP) $(CXXFLAGS) -c -o $@ $< -I single_include

# make initialize
initialize: 
	mkdir $(OBJ) $(EXE)
	

# Make clean
clean :
	rm -rf $(OBJ)/* $(EXE)/*
