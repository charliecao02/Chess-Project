#include "king.h"
#include "gameboard.h"
#include <vector>
using namespace std;


King::King(char colour, int r, int c, GameBoard* board):
    GamePiece{colour, r, c, board} {
        if (colour == 'W' && !(r==0 && c==4)) notMoved = false;
        if (colour == 'B' && !(r==7 && c==4)) notMoved = false;
    }

char King::pieceType(){ return 'K'; }

vector<vector<int>> King::getValidMoves(){
    vector<vector<int>> possibleMoves;
    vector<vector<GamePiece *>> theBoard = board->getBoard();
    vector<vector<int>> possibleDirections{{-1, -1}, {-1, 0}, {-1, 1},
                                           { 0, -1},          { 0, 1},
                                           { 1, -1}, { 1, 0}, { 1, 1}};

    for(auto d : possibleDirections) {
        int newR = r + d[0];
        int newC = c + d[1];
        if(newR < 0 || newR >= 8 || newC < 0 || newC >= 8) continue;
        else if(!theBoard[newR][newC] || //empty slot
                theBoard[newR][newC]->pieceColour() != colour) { //capturing slot
                    //apply changes
                    GamePiece* temp = theBoard[newR][newC];
                    theBoard[newR][newC] = theBoard[r][c];
                    theBoard[r][c] = nullptr;

                    //test if king will be in check
                    char enemyColour = colour  == 'B' ? 'W' : 'B';
                    if(!pieceUnderAttackBy(theBoard, newR, newC, enemyColour)) {
                        possibleMoves.emplace_back(vector<int>{newR, newC});
                    }

                    //revert
                    theBoard[r][c] = theBoard[newR][newC];
                    theBoard[newR][newC] = temp;
                }
    }

    //check if it can castle
    if (pieceColour() == 'W' && notMoved){
        //white king side
        if (r==0 && c==4 && theBoard[0][7] != nullptr && theBoard[0][7]->hasNotMoved()
        && theBoard[0][7]->pieceType()=='R' && theBoard[0][7]->pieceColour()=='W'
        && theBoard[0][5] == nullptr && theBoard[0][6] == nullptr && !pieceUnderAttackBy(theBoard, 0, 4, 'B')
        && !pieceUnderAttackBy(theBoard, 0, 5, 'B') && !pieceUnderAttackBy(theBoard, 0, 6, 'B')){
            possibleMoves.emplace_back(vector<int>{0,6});
        }
        //white queen side
        if (r==0 && c==4 && theBoard[0][0] != nullptr && theBoard[0][0]->hasNotMoved()
        && theBoard[0][0]->pieceType()=='R' && theBoard[0][0]->pieceColour()=='W'
        && theBoard[0][3] == nullptr && theBoard[0][2] == nullptr && theBoard[0][1] == nullptr
        && !pieceUnderAttackBy(theBoard, 0, 4, 'B') && !pieceUnderAttackBy(theBoard, 0, 3, 'B')
        && !pieceUnderAttackBy(theBoard, 0, 2, 'B')){
            possibleMoves.emplace_back(vector<int>{0,2});
        }
    }
    else if (pieceColour() == 'B' && notMoved){
        //black king side
        if (r==7 && c==4 && theBoard[7][7] != nullptr && theBoard[7][7]->hasNotMoved()
        && theBoard[7][7]->pieceType()=='R' && theBoard[7][7]->pieceColour()=='B'
        && theBoard[7][5] == nullptr && theBoard[7][6] == nullptr && !pieceUnderAttackBy(theBoard, 7, 4, 'W')
        && !pieceUnderAttackBy(theBoard, 7, 5, 'W') && !pieceUnderAttackBy(theBoard, 7, 6, 'W')){
            possibleMoves.emplace_back(vector<int>{7,6});
        }
        //black queen side
        if (r==7 && c==4 && theBoard[7][0] != nullptr && theBoard[7][0]->hasNotMoved()
        && theBoard[7][0]->pieceType()=='R' && theBoard[7][0]->pieceColour()=='B'
        && theBoard[7][3] == nullptr && theBoard[7][2] == nullptr && theBoard[7][1] == nullptr
        && !pieceUnderAttackBy(theBoard, 7, 4, 'W') && !pieceUnderAttackBy(theBoard, 7, 3, 'W')
        && !pieceUnderAttackBy(theBoard, 7, 2, 'W')){
            possibleMoves.emplace_back(vector<int>{7,2});
        }
    }

    return possibleMoves;
}
