#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_
#include <vector>
#include "player.h"

class HumanPlayer : public Player {
public:
    std::vector<int> getMove(char colour) override;
    char promoteTo() override;
};


#endif
