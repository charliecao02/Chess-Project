#ifndef BISHOP_H_
#define BISHOP_H_
#include "gamepiece.h"
#include <vector>

class Bishop : public GamePiece {

public:
    Bishop(char, int, int, GameBoard*);
    std::vector<std::vector<int>> getValidMoves() override;
    char pieceType() override;
};

#endif
