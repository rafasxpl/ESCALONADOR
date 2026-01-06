APP = ./app
BIN = ./binaries
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

CC = gcc

FLAGS = -I $(INCLUDE) 

all: clean object app run

object: $(OBJ)/merge.o $(OBJ)/insertion.o $(OBJ)/filaprocessos.o
app: $(BIN)/tp

clean:
	rm -rf $(OBJ)/*
	rm -rf $(BIN)/*

run: 
	$(BIN)/tp

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< $(FLAGS) -o $@

$(BIN)/tp: $(APP)/tp.c $(OBJ)/filaprocessos.o
	$(CC) $< $(OBJ)/filaprocessos.o $(OBJ)/merge.o $(OBJ)/insertion.o $(FLAGS) -o $@
