APP = ./app
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

CC = gcc
FLAGS = -I $(INCLUDE)

all: clean object app run

object: $(OBJ)/filaprocessos.o
app: $(BIN)/tp

clean:
	rm -rf $(OBJ)/*
	rm -rf $(BIN)/*

run: 
	$(BIN)/tp

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $(FLAGS) $< -o $@

$(BIN)/tp: $(APP)/tp.c $(OBJ)/filaprocessos.o
	$(CC) $(FLAGS) $< $(OBJ)/filaprocessos.o -o $@
