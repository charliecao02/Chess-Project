#ifndef QUEEN_H_
#define QUEEN_H_
#include "gamepiece.h"
#include <vector>

class Queen : public GamePiece {

public:
    Queen(char, int, int, GameBoard*);
    std::vector<std::vector<int>> getValidMoves() override;
    char pieceType() override;
};

#endif
