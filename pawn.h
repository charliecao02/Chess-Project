#ifndef PAWN_H_
#define PAWN_H_
#include "gamepiece.h"
#include <vector>

class Pawn : public GamePiece {

public:
    Pawn(char, int, int, GameBoard*);
    std::vector<std::vector<int>> getValidMoves() override;
    char pieceType() override;
};

#endif
