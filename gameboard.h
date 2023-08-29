#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_
#include "textdisplay.h"
#include "graphicaldisplay.h"
#include "gamepiece.h"
#include "sdl_wrap.h"
#include <vector>
#include <string>

//forward declare because of include guard bs once again
class TextDisplay;
class GraphicalDisplay;

class GameBoard {
    std::vector<std::vector<GamePiece*>> theBoard;
    TextDisplay *td;
    GraphicalDisplay *gd;
    std::string coordsToPos(std::vector<int>);
public:
    GameBoard(Screen*);
    ~GameBoard();
    void setup();
    int makeMove(int, int, int, int); //return 1 if promotion, 0 otherwise
    void promote(int, int, char);
    void drawBoards();
    bool inCheck(char);
    int numMoves(char);
    bool onlyKings();
    std::vector<std::vector<int>> getValidMoves(char, int, int);
    std::vector<std::vector<GamePiece*>> getBoard();
    static std::vector<int> posToCoords(std::string);
};

#endif
