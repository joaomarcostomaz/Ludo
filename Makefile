CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

LUDO_OBJ = $(OBJ)/Ludo.o $(OBJ)/main.o
LUDO_INC = $(INC)/Ludo.h
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/Ludo

run: $(EXE)
		$(EXE)
	
$(BIN)/Ludo: $(LUDO_OBJ)
	$(CC) -pg -o $(BIN)/Ludo $(LUDO_OBJ) $(LIBS)

$(OBJ)/Ludo.o: $(LUDO_INC) $(SRC)/Ludo.c
	$(CC) $(CFLAGS) -o $(OBJ)/Ludo.o $(SRC)/Ludo.c

$(OBJ)/main.o: $(LUDO_INC) $(SRC)/main.c
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c

clean:
		rm -f $(EXE) $(LUDO_OBJ) gmon.out
		clear
