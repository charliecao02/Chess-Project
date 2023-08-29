#ifndef COMPUTERPLAYER_H_
#define COMPUTERPLAYER_H_
#include <vector>
#include "gameboard.h"
#include "player.h"

class ComputerPlayer : public Player {
    GameBoard *board;
    int level;
    std::vector<std::vector<int>> captureAndCheck(char, std::vector<std::vector<int>>);
    std::vector<std::vector<int>> avoidCapture(char, std::vector<std::vector<int>>);
    std::vector<std::vector<int>> tryToCapture(char colour, char enemyPiece, std::vector<std::vector<int>> capturesAndChecks);
public:
    ComputerPlayer(GameBoard *board, int level);
    std::vector<int> getMove(char colour) override;
    char promoteTo() override;
};

#endif
