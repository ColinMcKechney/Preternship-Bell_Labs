# This is the Makefile for the CSE 20312 course - Lab 06

# G++ is for the GCC compiler for C++
PP := g++

# CXXFLAGS are the compiler flages for when we compile C++ code in this course 
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror
CXXFLAGS := -m64 -std=c++11 $(FLAGS)

# Variables for Folders
INC := inc
SRC := src
EXE := exe
OBJ := obj


# Test to see if edges are working
EdgeTestObjs := $(OBJ)/EdgeTest.o 

EdgeTest: $(EdgeTestObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/EdgeTest $(EdgeTestObjs)
	$(EXE)/./EdgeTest

$(OBJ)/EdgeTest.o: $(SRC)/EdgeTest.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/EdgeTest.cpp -o $@
	
# Test to see if graphs are working
GraphTestObjs := $(OBJ)/GraphTest.o 

GraphTest: $(GraphTestObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/GraphTest $(GraphTestObjs)
	./$(EXE)/GraphTest

$(OBJ)/GraphTest.o: $(SRC)/GraphTest.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/GraphTest.cpp -o $@
	



# make initialize
# Will be called by grader to initialize your objects and executables folders
initialize: 
	mkdir $(OBJ) $(EXE)
	

# Make clean
clean :
	rm -rf $(OBJ)/* $(EXE)/*
