#ifndef ROOK_H_
#define ROOK_H_
#include "gamepiece.h"
#include <vector>

class GameBoard;

class Rook : public GamePiece {

public:
    Rook(char, int, int, GameBoard*);
    std::vector<std::vector<int>> getValidMoves() override;
    char pieceType() override;
};

#endif
