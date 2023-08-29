#ifndef GAME_INSTANCE_H_
#define GAME_INSTANCE_H_
#include "gameboard.h"
#include "player.h"
#include "sdl_wrap.h"

class GameInstance {
    GameBoard board;
    Player *p1, *p2; // virtual players, can be human or computer
    int winner;
public:
    GameInstance(Screen*);
    ~GameInstance();
    void setup();
    char playGame(Player *player1, Player *player2);
    GameBoard* getBoard();
};

#endif
