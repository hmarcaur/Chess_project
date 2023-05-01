# Silent commands

# $@	The name of the target
# $<	The name of the first dependency
# $^	The dependency list
# $?	The dependency list more recent than the target
# $*	The file name without suffix


CC=g++
CFLAGS= #-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=Chess
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

Chess: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

main.o: Position.hpp Piece.hpp Board.hpp Chessboard.hpp Pawn.hpp Queen.hpp Bishop.hpp Knight.hpp Rook.hpp King.hpp

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
