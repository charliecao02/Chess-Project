#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "gamepiece.h"
#include <vector>

class Knight : public GamePiece {

public:
    Knight(char, int, int, GameBoard*);
    std::vector<std::vector<int>> getValidMoves() override;
    char pieceType() override;
};

#endif
