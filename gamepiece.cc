#include "gamepiece.h"
#include "gameboard.h"
#include <vector>
using namespace std;

class GameBoard;

GamePiece::GamePiece(char colour, int r, int c, GameBoard* board): 
colour{colour}, r{r}, c{c}, board{board}, notMoved{true}, justMovedTwo{false} {}

GamePiece::~GamePiece() {}

char GamePiece::pieceColour(){ return colour; }

bool GamePiece::hasNotMoved(){ return notMoved; }
void GamePiece::setNotMoved(bool b){ notMoved = b; }

bool GamePiece::justMoved2(){ return justMovedTwo; }
void GamePiece::setMoved2(bool b){ justMovedTwo = b; }

void GamePiece::moveTo(int destR, int destC){
    r = destR;
    c = destC;
}

bool GamePiece::pieceUnderAttackBy(vector<vector<GamePiece *>> theBoard, int row, int col, char attackingColour) {
    int i, j;

    // check up (attacked by rooks and queen)
    i = row;
    while(i > 0) {
        --i;
        // go up until encountering a piece
        if(theBoard[i][col]) { 
            if(theBoard[i][col]->pieceColour() == attackingColour) { // if piece is enemy colour
                if(theBoard[i][col]->pieceType() == 'Q' || theBoard[i][col]->pieceType() == 'R') return true; 
                else break; // if not queen or rook we are safe
            } else { // if it's a friendly piece we are safe
                break;
            }
        }
    }

    // check down (attacked by rooks and queen)
    i = row;
    while(i < 7) {
        ++i;
        // go down until encountering a piece
        if(theBoard[i][col]) { 
            if(theBoard[i][col]->pieceColour() == attackingColour) { // if piece is enemy colour
                if(theBoard[i][col]->pieceType() == 'Q' || theBoard[i][col]->pieceType() == 'R') return true; 
                else break; // if not queen or rook we are safe
            } else { // if it's a friendly piece we are safe
                break;
            }
        }
    }

    // check left (attacked by rooks and queen)
    j = col;
    while(j > 0) {
        --j;
        // go left until encountering a piece
        if(theBoard[row][j]) { 
            if(theBoard[row][j]->pieceColour() == attackingColour) { // if piece is enemy colour
                if(theBoard[row][j]->pieceType() == 'Q' || theBoard[row][j]->pieceType() == 'R') return true; 
                else break; // if not queen or rook we are safe
            } else { // if it's a friendly piece we are safe
                break;
            }
        }
    }

    // check right (attacked by rooks and queen)
    j = col;
    while(j < 7) {
        ++j;
        // go right until encountering a piece
        if(theBoard[row][j]) { 
            if(theBoard[row][j]->pieceColour() == attackingColour) { // if piece is enemy colour
                if(theBoard[row][j]->pieceType() == 'Q' || theBoard[row][j]->pieceType() == 'R') return true; 
                else break; // if not queen or rook we are safe
            } else { // if it's a friendly piece we are safe
                break;
            }
        }
    }

    // check diagonal NorthEast (attacked by bishops and queen) 
    i = row; j = col;
    while(j < 7 && i > 0) {
        --i;
        ++j;
        // go NE until encountering a piece
        if(theBoard[i][j]) { 
            if(theBoard[i][j]->pieceColour() == attackingColour) { // if piece is enemy colour
                if(theBoard[i][j]->pieceType() == 'Q' || theBoard[i][j]->pieceType() == 'B') return true; 
                else break; // if not queen or bishop we are safe
            } else { // if it's a friendly piece we are safe
                break;
            }
        }
    }

    // check diagonal SouthEast (attacked by bishops and queen) 
    i = row; j = col;
    while(j < 7 && i < 7) {
        ++i;
        ++j;
        // go SE until encountering a piece
        if(theBoard[i][j]) { 
            if(theBoard[i][j]->pieceColour() == attackingColour) { // if piece is enemy colour
                if(theBoard[i][j]->pieceType() == 'Q' || theBoard[i][j]->pieceType() == 'B') return true; 
                else break; // if not queen or bishop we are safe
            } else { // if it's a friendly piece we are safe
                break;
            }
        }
    }

    // check diagonal SouthWest (attacked by bishops and queen) 
    i = row; j = col;
    while(j > 0 && i < 7) {
        ++i;
        --j;
        // go SW until encountering a piece
        if(theBoard[i][j]) { 
            if(theBoard[i][j]->pieceColour() == attackingColour) { // if piece is enemy colour
                if(theBoard[i][j]->pieceType() == 'Q' || theBoard[i][j]->pieceType() == 'B') return true; 
                else break; // if not queen or bishop we are safe
            } else { // if it's a friendly piece we are safe
                break;
            }
        }
    }

    // check diagonal NorthWest (attacked by bishops and queen) 
    i = row; j = col;
    while(j > 0 && i > 0) {
        --i;
        --j;
        // go NW until encountering a piece
        if(theBoard[i][j]) { 
            if(theBoard[i][j]->pieceColour() == attackingColour) { // if piece is enemy colour
                if(theBoard[i][j]->pieceType() == 'Q' || theBoard[i][j]->pieceType() == 'B') return true; 
                else break; // if not queen or bishop we are safe
            } else { // if it's a friendly piece we are safe
                break;
            }
        }
    }

    // check for knight attacks
    vector<vector<int>> lshape = {{row-1, col-2}, {row+1, col+2}, {row-2, col-1}, {row+2, col+1},
                                {row-1, col+2}, {row+1, col-2}, {row-2, col+1}, {row+2, col-1}};
    for(vector<int> pos : lshape) {
        // check bounds
        if(pos[0] < 0 || pos[0] >= 8 || pos[1] < 0 || pos[1] >= 8) continue;
        // if enemy knight is neighbour, then we are being attacked
        if(theBoard[pos[0]][pos[1]] && theBoard[pos[0]][pos[1]]->pieceColour() == attackingColour && theBoard[pos[0]][pos[1]]->pieceType() == 'N') {
            return true;
        } 
    }

    // check for king attacks
    vector<vector<int>> neighbours = {{row-1, col-1}, {row-1, col}, {row-1, col+1}, {row, col+1}, {row, col-1}, {row+1, col-1}, {row+1, col}, {row+1, col+1}};
    for(vector<int> pos : neighbours) {
        // check bounds
        if(pos[0] < 0 || pos[0] >= 8 || pos[1] < 0 || pos[1] >= 8) continue;
        // if enemy king is neighbour, then we are being attacked
        if(theBoard[pos[0]][pos[1]] && theBoard[pos[0]][pos[1]]->pieceColour() == attackingColour && theBoard[pos[0]][pos[1]]->pieceType() == 'K') {
            return true;
        } 
    }

    // check for white pawn attacks
    vector<vector<int>> pawnpositions;
    if(attackingColour == 'W') pawnpositions = {{row-1, col-1}, {row-1, col+1}};
    else pawnpositions = {{row+1, col-1}, {row+1, col+1}};

    for(vector<int> pos : pawnpositions) {
        // check bounds
        if(pos[0] < 0 || pos[0] >= 8 || pos[1] < 0 || pos[1] >= 8) continue;
        // if enemy king is neighbour, then we are being attacked
        if(theBoard[pos[0]][pos[1]] && theBoard[pos[0]][pos[1]]->pieceColour() == attackingColour && theBoard[pos[0]][pos[1]]->pieceType() == 'P') {
            return true;
        } 
    }

    return false;
}

vector<int> GamePiece::findKing() {
    for(int r = 0; r < 8; ++r) {
        for(int c = 0; c < 8; ++c) {
            vector<vector<GamePiece *>> theBoard = board->getBoard();
            if(!theBoard[r][c]) continue;
            if(theBoard[r][c]->pieceType() == 'K' && 
                theBoard[r][c]->pieceColour() == colour) return vector<int>{r, c};
        }
    }

    // should never happen
    return vector<int>{-1, -1};
}
