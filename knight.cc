#include "knight.h"
#include "gameboard.h"
#include <vector>
#include <iostream>
using namespace std;

Knight::Knight(char colour, int r, int c, GameBoard* board): GamePiece{colour, r, c, board} {}

char Knight::pieceType(){ return 'N'; }

vector<vector<int>> Knight::getValidMoves(){
    vector<vector<int>> possibleMoves;
    vector<vector<GamePiece *>> theBoard = board->getBoard();
    vector<vector<int>> possibleDirections{         {-2, -1}, {-2,  1}, 
                                           {-1, -2},                  {-1,  2},
                                           { 1, -2},                  { 1,  2},
                                                    { 2, -1}, { 2,  1}};
    vector<int> kingPosition = findKing();

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
                    if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                        possibleMoves.emplace_back(vector<int>{newR, newC});
                    }

                    //revert
                    theBoard[r][c] = theBoard[newR][newC];
                    theBoard[newR][newC] = temp;
                }
        }

    return possibleMoves;
}
