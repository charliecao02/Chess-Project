#include <iostream>
#include <iomanip>
#include <string>
#include "gameinstance.h"
#include "player.h"
#include "humanplayer.h"
#include "computerplayer.h"
#include "sdl_wrap.h"
using namespace std;

// Just must declare a global variable (or at the start of main)
// Don't do anything with this object. It just handles the start and end of SDL.
SDL_Runner r;

int main(int argc, char *argv[]){
    //height and width = 800
    Screen s{800, 800, "Chess"};
    s.add_img("board", "./images/board.png");
    s.add_img("whiteKing", "./images/wking.png");
    s.add_img("whiteBishop", "./images/wbishop.png");
    s.add_img("whiteKnight", "./images/wknight.png");
    s.add_img("whitePawn", "./images/wpawn.png");
    s.add_img("whiteQueen", "./images/wqueen.png");
    s.add_img("whiteRook", "./images/wrook.png");
    s.add_img("blackKing", "./images/bking.png");
    s.add_img("blackBishop", "./images/bbishop.png");
    s.add_img("blackKnight", "./images/bknight.png");
    s.add_img("blackPawn", "./images/bpawn.png");
    s.add_img("blackQueen", "./images/bqueen.png");
    s.add_img("blackRook", "./images/brook.png");

    Colour grey{128, 128, 128};
    s.draw_rect(0, 0, 800, 800, grey);
    s.update();
    cin.exceptions(ios::eofbit|ios::failbit);
    GameInstance *game = new GameInstance{&s};
    Player *p1 = nullptr;
    Player *p2 = nullptr;
    string cmd;

    float whitescore = 0, blackscore = 0;

    while (true){
        try {
            cin >> cmd;
            if (cmd == "game"){
                //set up players
                //eg. game computer 4 human

                string in;
                while (!p1){
                    cin >> in;
                    if (in == "human") p1 = new HumanPlayer{};
                    else if (in == "computer"){
                        int level;
                        cin >> level;
                        if (level>=1 && level<=4) p1 = new ComputerPlayer{game->getBoard(), level};
                        else cout << "Invalid Computer Player Level" << endl;
                    }
                    else cout << "Invalid Type For Player 1" << endl;
                }
                while (!p2){
                    cin >> in;
                    if (in == "human") p2 = new HumanPlayer{};
                    else if (in == "computer"){
                        int level;
                        cin >> level;
                        if (level>=1 && level<=4) p2 = new ComputerPlayer{game->getBoard(), level};
                        else cout << "Invalid Computer Player Level" << endl;
                    }
                    else cout << "Invalid Type For Player 2" << endl;
                }

                //start the game
                char winner = game->playGame(p1, p2);
                if(winner == 'W') {
                    ++whitescore;
                } else if(winner == 'B') {
                    ++blackscore;
                } else { // tie
                    whitescore += 0.5;
                    blackscore += 0.5;
                }
                cout << "Current Score:" << endl;
                cout << "White: " << setprecision(2) << whitescore << endl;
                cout << "Black: " << setprecision(2) << blackscore << endl;
                delete game;
                p1 = nullptr;
                p2 = nullptr;
                game = new GameInstance{&s};
            }
            else if (cmd == "setup"){
                //enter setup mode
                game->setup();
            }
            else {
                //invalid command
                cout << "Invalid Command" << endl;
            }
        }
        catch (ios::failure &) { break; }
    }
    cout << "Final Score:" << endl;
    cout << "White: " << setprecision(2) << whitescore << endl;
    cout << "Black: " << setprecision(2) << blackscore << endl;
    delete game;
}
