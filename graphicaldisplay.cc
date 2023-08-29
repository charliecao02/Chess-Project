#include "graphicaldisplay.h"
#include "sdl_wrap.h"
#include <vector>
using namespace std;

GraphicalDisplay::GraphicalDisplay(vector<vector<GamePiece*>> board, Screen* screen) : 
    curBoard{board}, screen{screen} {}

void GraphicalDisplay::draw(){
    screen->draw_img("board", 0, 0);
    Colour red{255, 0, 0};
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            int posX = 100*j;
            int posY = 100*(7-i);
            if (curBoard[i][j]){
                char piece = curBoard[i][j]->pieceType();
                char colour = curBoard[i][j]->pieceColour();
                if (colour == 'W'){
                    switch(piece){
                        case 'K':{
                            if (curBoard[i][j]->pieceUnderAttackBy(curBoard, i, j, 'B')){
                                screen->draw_rect(posX, posY, 100, 100, red);
                            }
                            screen->draw_img("whiteKing", posX, posY);
                            break;
                        }
                        case 'N':
                            screen->draw_img("whiteKnight", posX, posY);
                            break;
                        case 'B':   
                            screen->draw_img("whiteBishop", posX, posY);
                            break;
                        case 'P':
                            screen->draw_img("whitePawn", posX, posY);
                            break;
                        case 'Q':
                            screen->draw_img("whiteQueen", posX, posY);
                            break;
                        case 'R':
                            screen->draw_img("whiteRook", posX, posY);
                            break;
                    }
                }
                else {
                    switch(piece) {
                        case 'K':{
                            if (curBoard[i][j]->pieceUnderAttackBy(curBoard, i, j, 'W')){
                                screen->draw_rect(posX, posY, 100, 100, red);
                            }
                            screen->draw_img("blackKing", posX, posY);
                            break;
                        }
                        case 'N':
                            screen->draw_img("blackKnight", posX, posY);
                            break;
                        case 'B':   
                            screen->draw_img("blackBishop", posX, posY);
                            break;
                        case 'P':
                            screen->draw_img("blackPawn", posX, posY);
                            break;
                        case 'Q':
                            screen->draw_img("blackQueen", posX, posY);
                            break;
                        case 'R':
                            screen->draw_img("blackRook", posX, posY);
                            break;
                    }
                }
            }
        }
    }
    screen->update();
}

void GraphicalDisplay::update(vector<vector<GamePiece*>>* newBoard){
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            if (curBoard[i][j] != (*newBoard)[i][j]){
                curBoard[i][j] = (*newBoard)[i][j];
            }
        }
    }
    draw();
}
