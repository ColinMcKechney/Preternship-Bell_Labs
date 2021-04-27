INC = inc
SRC = src
OBJ = obj
TEST = tests
EXE = exe
CC = g++
CFLAGS = -m64 -std=c++11 -Weffc++ -O2 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror



test: driver
	$(shell $(EXE)/driver $(TEST)/test.json)

driver : $(OBJ)/driver.o
	$(shell mkdir $(EXE))
	$(CC) $(CFLAGS) -o exe/$@ $< -I single_include

$(OBJ)/%.o : $(SRC)/%.cpp
	$(shell test -d $(OBJ) || mkdir $(OBJ))
	$(CC) $(CFLAGS) -c -o $@ $< -I single_include

clean :
	$(shell rm -r $(OBJ) $(EXE))



