#include "queen.h"
#include "gameboard.h"
#include <vector>
using namespace std;

Queen::Queen(char colour, int r, int c, GameBoard* board) : GamePiece{colour, r, c, board} {}

char Queen::pieceType(){ return 'Q'; }

vector<vector<int>> Queen::getValidMoves(){
    vector<vector<int>> possibleMoves;
    vector<vector<GamePiece *>> theBoard = board->getBoard();
    vector<int> kingPosition = findKing();

    //down-right
    for(int i = 1; i < 8; ++i) {
        int newR = r + i;
        int newC = c + i;
        if(newR < 0 || newR >= 8 || newC < 0 || newC >= 8) break; //invalid slot
        else if(!theBoard[newR][newC] || theBoard[newR][newC]->pieceColour() != colour){ //empty or capture
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
        
        if (theBoard[newR][newC]) break; //occupied, stop looking in this dir
    }

    //up-right
    for(int i = 1; i < 8; ++i) {
        int newR = r - i;
        int newC = c + i;
        if(newR < 0 || newR >= 8 || newC < 0 || newC >= 8) break;
        else if(!theBoard[newR][newC] || theBoard[newR][newC]->pieceColour() != colour){ //empty or capture
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
        
        if (theBoard[newR][newC]) break;
    }

    //up-left
    for(int i = 1; i < 8; ++i) {
        int newR = r - i;
        int newC = c - i;
        if(newR < 0 || newR >= 8 || newC < 0 || newC >= 8) break;
        else if(!theBoard[newR][newC] || theBoard[newR][newC]->pieceColour() != colour){ //empty or capture
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
        
        if (theBoard[newR][newC]) break;
    }

    //down-left
    for(int i = 1; i < 8; ++i) {
        int newR = r + i;
        int newC = c - i;
        if(newR < 0 || newR >= 8 || newC < 0 || newC >= 8) break;
        else if(!theBoard[newR][newC] || theBoard[newR][newC]->pieceColour() != colour){ //empty or capture
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
        
        if (theBoard[newR][newC]) break;
    }

    //up
    for(int i = r - 1; i >= 0; --i) {
        if(!theBoard[i][c] || theBoard[i][c]->pieceColour() != colour) {
            //apply changes
            GamePiece* temp = theBoard[i][c];
            theBoard[i][c] = theBoard[r][c];
            theBoard[r][c] = nullptr;

            //test if king will be in check
            char enemyColour = colour  == 'B' ? 'W' : 'B';
            if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                possibleMoves.emplace_back(vector<int>{i, c});
            }

            //revert
            theBoard[r][c] = theBoard[i][c];
            theBoard[i][c] = temp;
        } 

        if(theBoard[i][c]) break; //occupied, stop looking in this dir
    }

    //down
    for(int i = r + 1; i < 8; ++i) {
        if(!theBoard[i][c] || theBoard[i][c]->pieceColour() != colour) {
            //apply changes
            GamePiece* temp = theBoard[i][c];
            theBoard[i][c] = theBoard[r][c];
            theBoard[r][c] = nullptr;

            //test if king will be in check
            char enemyColour = colour  == 'B' ? 'W' : 'B';
            if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                possibleMoves.emplace_back(vector<int>{i, c});
            }

            //revert
            theBoard[r][c] = theBoard[i][c];
            theBoard[i][c] = temp;
        } 

        if(theBoard[i][c]) break;
    }

    //right
    for(int i = c + 1; i < 8; ++i) {
        if(!theBoard[r][i] || theBoard[r][i]->pieceColour() != colour) {
            //apply changes
            GamePiece* temp = theBoard[r][i];
            theBoard[r][i] = theBoard[r][c];
            theBoard[r][c] = nullptr;

            //test if king will be in check
            char enemyColour = colour  == 'B' ? 'W' : 'B';
            if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                possibleMoves.emplace_back(vector<int>{r, i});
            }

            //revert
            theBoard[r][c] = theBoard[r][i];
            theBoard[r][i] = temp;
        } 
        
        if(theBoard[r][i]) break;
    }

    //left
    for(int i = c - 1; i >= 0; --i) {
        if(!theBoard[r][i] || theBoard[r][i]->pieceColour() != colour) {
            //apply changes
            GamePiece* temp = theBoard[r][i];
            theBoard[r][i] = theBoard[r][c];
            theBoard[r][c] = nullptr;

            //test if king will be in check
            char enemyColour = colour  == 'B' ? 'W' : 'B';
            if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                possibleMoves.emplace_back(vector<int>{r, i});
            }

            //revert
            theBoard[r][c] = theBoard[r][i];
            theBoard[r][i] = temp;
        } 
        
        if(theBoard[r][i]) break;
    }

    return possibleMoves;
}
