#ifndef GRAPHICAL_DISPLAY_H_
#define GRAPHICAL_DISPLAY_H_
#include <vector>
#include "gamepiece.h"
#include "sdl_wrap.h"

//forward declare because of include guard bs
class GamePiece;

class GraphicalDisplay {
    std::vector<std::vector<GamePiece*>> curBoard;
    Screen *screen;
public:
    GraphicalDisplay(std::vector<std::vector<GamePiece*>>, Screen*);
    void update(std::vector<std::vector<GamePiece*>>*);
    void draw();
};

#endif
