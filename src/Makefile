# This is the Makefile for the CSE 20312 course - Lab 06

# G++ is for the GCC compiler for C++
PP := g++

# CXXFLAGS are the compiler flages for when we compile C++ code in this course 
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)

# Variables for Folders
INC := inc
SRC := src
EXE := exe
OBJ := obj


# Command: make SortKLists - Find Kth Largest
EdgeTestObjs := $(OBJ)/EdgeTest.o 

EdgeTest: $(EdgeTestObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/EdgeTest $(EdgeTestObjs)
	$(EXE)/./EdgeTest

$(OBJ)/EdgeTest.o: $(SRC)/EdgeTest.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/EdgeTest.cpp -o $@
	



# make initialize
# Will be called by grader to initialize your objects and executables folders
initialize: 
	mkdir $(OBJ) $(EXE)
	

# Make clean
clean :
	rm -rf $(OBJ)/* $(EXE)/*
