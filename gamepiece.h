#ifndef GAME_PIECE_H_
#define GAME_PIECE_H_
#include "gameboard.h"
#include <vector>

//forward declare because of more include guard bs
class GameBoard;

class GamePiece {
protected:
    char colour;
    int r, c;
    GameBoard* board;
    bool notMoved;
    bool justMovedTwo;
public:
    GamePiece(char, int, int, GameBoard*);
    virtual ~GamePiece();
    virtual std::vector<std::vector<int>> getValidMoves() = 0;
    virtual char pieceType() = 0;
    char pieceColour();

    bool hasNotMoved();
    void setNotMoved(bool);

    bool justMoved2();
    void setMoved2(bool);
    
    bool pieceUnderAttackBy(std::vector<std::vector<GamePiece *>>, int, int, char);
    std::vector<int> findKing();
    //update r and c
    void moveTo(int, int);
};

#endif
