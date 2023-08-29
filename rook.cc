#include "rook.h"
#include "gameboard.h"
#include <vector>
using namespace std;

Rook::Rook(char colour, int r, int c, GameBoard* board): GamePiece{colour, r, c, board} {}

char Rook::pieceType(){ return 'R'; }

vector<vector<int>> Rook::getValidMoves(){
    vector<vector<int>> possibleMoves;
    vector<vector<GamePiece*>> theBoard = board->getBoard();
    vector<int> kingPosition = findKing();

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
