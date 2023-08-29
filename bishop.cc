#include "bishop.h"
#include "gameboard.h"
#include <vector>
using namespace std;

Bishop::Bishop(char colour, int r, int c, GameBoard* board): GamePiece{colour, r, c, board} {}

char Bishop::pieceType(){ return 'B'; }

vector<vector<int>> Bishop::getValidMoves(){
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

    return possibleMoves;
}
