CC = g++
CFLAGS = -Wextra -Wall -Wvla -std=c++17 -c -g -pthread  -DNDEBUG
LDFLAGS = -g
VFLAGS = --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes
HEADERS = Piece.h King.h Pawn.h Knight.h Queen.h Bishop.h Rook.h Board.h GameMaster.h Game.h
SOURCES = Piece.cpp King.cpp Pawn.cpp Knight.cpp Queen.cpp Bishop.cpp Rook.cpp Board.cpp GameMaster.cpp Game.cpp
OBJECTS = Piece.o King.o Pawn.o Knight.o Queen.o Bishop.o Rook.o Board.o GameMaster.o Game.o chess.o
TAR_FILES = $(HEADERS) $(SOURCES) chess.cpp Makefile README

# All Target

valgrind: chess
	valgrind $(VFLAGS) $^

# Executables
chess: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Object Files
%.o : %.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

# Other Targets
tar: $(TAR_FILES)
	tar cvf ex2.tar $^

clean:
	rm -f *.o chess chess.tar

# Phony
.PHONY: all clean tar
