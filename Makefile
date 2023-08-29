CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = bishop.o chessgame.o computerplayer.o gameboard.o gameinstance.o gamepiece.o graphicaldisplay.o humanplayer.o king.o knight.o pawn.o player.o queen.o rook.o sdl_wrap.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lSDL2 -lSDL2_image -lSDL2_ttf

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
