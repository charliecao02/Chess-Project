#ifndef TEXT_DISPLAY_H_
#define TEXT_DISPLAY_H_
#include <vector>
#include <iostream>
#include "gamepiece.h"

//forward declare because of include guard bs
class GamePiece;

class TextDisplay {
    std::vector<std::vector<GamePiece*>> curBoard;
public:
    TextDisplay(std::vector<std::vector<GamePiece*>>);
    void update(std::vector<std::vector<GamePiece*>>*);
    friend std::ostream &operator<<(std::ostream &, TextDisplay &);
};

#endif
