#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>

class Player {
public:
    virtual std::vector<int> getMove(char colour) = 0;
    virtual char promoteTo() = 0;
    virtual ~Player();
};

#endif
