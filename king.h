#ifndef KING_H_
#define KING_H_
#include "gamepiece.h"
#include <vector>

class King : public GamePiece {

public:
    King(char, int, int, GameBoard*);
    std::vector<std::vector<int>> getValidMoves() override;
    char pieceType() override;
};

#endif
