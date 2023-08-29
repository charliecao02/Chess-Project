#include "pawn.h"
#include "gameboard.h"
#include <vector>
using namespace std;

Pawn::Pawn(char colour, int r, int c, GameBoard* board): 
    GamePiece{colour, r, c, board} {
        if (colour == 'W' && r!=1) notMoved = false;
        if (colour == 'B' && r!=6) notMoved = false;
    }

char Pawn::pieceType(){ return 'P'; }

vector<vector<int>> Pawn::getValidMoves(){
    vector<vector<int>> possibleMoves;
    vector<vector<GamePiece *>> theBoard = board->getBoard();
    vector<int> kingPosition = findKing();
    vector<vector<int>> possibleDirections;                              

    switch(colour) {
        case 'W':{
            possibleDirections = {{ 1, -1}, { 1, 0}, { 1, 1}};
            //starting case: move 2 slots
            if(notMoved) {
                int newR = r + possibleDirections[1][0];
                int newC = c + possibleDirections[1][1];
                int newR2 = newR + possibleDirections[1][0];
                int newC2 = newC + possibleDirections[1][1];
                if(newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && 
                    newR2 >= 0 && newR2 < 8 && newC2 >= 0 && newC2 < 8 && 
                    !theBoard[newR][newC] && !theBoard[newR2][newC2]) {
                        //apply changes
                        GamePiece* temp = theBoard[newR2][newC2];
                        theBoard[newR2][newC2] = theBoard[r][c];
                        theBoard[r][c] = nullptr;

                        //test if king will be in check
                        char enemyColour = colour  == 'B' ? 'W' : 'B';
                        if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                            possibleMoves.emplace_back(vector<int>{newR2, newC2});
                        }

                        //revert
                        theBoard[r][c] = theBoard[newR2][newC2];
                        theBoard[newR2][newC2] = temp;
                }
            }
        
            //directly forward: has to be empty slot
            int newR = r + possibleDirections[1][0];
            int newC = c + possibleDirections[1][1];
            if(newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && !theBoard[newR][newC]) {
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

            //up right: occupied by black
            newR = r + possibleDirections[2][0];
            newC = c + possibleDirections[2][1];
            if(newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && 
                theBoard[newR][newC] && theBoard[newR][newC]->pieceColour() == 'B') {
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
            //en passant case: newR has to be 5 + adjacency
            if(newR == 5 && newC >= 0 && newC < 8 && theBoard[4][newC] && !theBoard[5][newC]) {
                if(theBoard[4][newC]->pieceColour() == 'B' && theBoard[4][newC]->pieceType() == 'P'
                    && theBoard[4][newC]->justMoved2()) {
                    //apply changes
                    GamePiece* temp = theBoard[4][newC];
                    theBoard[newR][newC] = theBoard[r][c];
                    theBoard[r][c] = nullptr;
                    theBoard[4][newC] = nullptr;

                    //test if king will be in check
                    char enemyColour = colour  == 'B' ? 'W' : 'B';
                    if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                        possibleMoves.emplace_back(vector<int>{newR, newC});
                    }

                    //revert
                    theBoard[r][c] = theBoard[newR][newC];
                    theBoard[newR][newC] = nullptr;
                    theBoard[4][newC] = temp;
                }
            }

            //up left: occupied by black
            newR = r + possibleDirections[0][0];
            newC = c + possibleDirections[0][1];
            if(newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && 
                theBoard[newR][newC] && theBoard[newR][newC]->pieceColour() == 'B') {
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
            //en passant case: newR has to be 5 + adjacency
            if(newR == 5 && newC >= 0 && newC < 8 && theBoard[4][newC] && !theBoard[5][newC]) {
                if(theBoard[4][newC]->pieceColour() == 'B' && theBoard[4][newC]->pieceType() == 'P'
                    && theBoard[4][newC]->justMoved2()) {
                    //apply changes
                    GamePiece* temp = theBoard[4][newC];
                    theBoard[newR][newC] = theBoard[r][c];
                    theBoard[r][c] = nullptr;
                    theBoard[4][newC] = nullptr;

                    //test if king will be in check
                    char enemyColour = colour  == 'B' ? 'W' : 'B';
                    if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                        possibleMoves.emplace_back(vector<int>{newR, newC});
                    }

                    //revert
                    theBoard[r][c] = theBoard[newR][newC];
                    theBoard[newR][newC] = nullptr;
                    theBoard[4][newC] = temp;
                }
            }
            break;
        }
        case 'B':{
            possibleDirections = {{-1, -1}, {-1, 0}, {-1, 1}};
            //starting case: move 2 slots
            if(notMoved) {
                int newR = r + possibleDirections[1][0];
                int newC = c + possibleDirections[1][1];
                int newR2 = newR + possibleDirections[1][0];
                int newC2 = newC + possibleDirections[1][1];
                if(newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && 
                    newR2 >= 0 && newR2 < 8 && newC2 >=0 && newC2 < 8 && 
                    !theBoard[newR][newC] && !theBoard[newR2][newC2]) {
                        //apply changes
                        GamePiece* temp = theBoard[newR2][newC2];
                        theBoard[newR2][newC2] = theBoard[r][c];
                        theBoard[r][c] = nullptr;

                        //test if king will be in check
                        char enemyColour = colour  == 'B' ? 'W' : 'B';
                        if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                            possibleMoves.emplace_back(vector<int>{newR2, newC2});
                        }

                        //revert
                        theBoard[r][c] = theBoard[newR2][newC2];
                        theBoard[newR2][newC2] = temp;
                }
            }
        
            //directly forward: has to be empty slot
            int newR = r + possibleDirections[1][0];
            int newC = c + possibleDirections[1][1];
            if(newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && !theBoard[newR][newC]) {
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

            //up right: occupied by white
            newR = r + possibleDirections[2][0];
            newC = c + possibleDirections[2][1];
            if(newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && 
                theBoard[newR][newC] && theBoard[newR][newC]->pieceColour() == 'W') {
                    //apply changes
                    GamePiece* temp = theBoard[newR][newC];
                    theBoard[newR][newC] = theBoard[r][c];
                    theBoard[r][c] = nullptr;

                    //test if king will be in check
                    char enemyColour = colour  == 'B' ? 'W' : 'B';
                    if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
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

                    //revert
                    theBoard[r][c] = theBoard[newR][newC];
                    theBoard[newR][newC] = temp;
            }
            //en passant case: newR has to be 2 + adjacency
            if(newR == 2 && newC >= 0 && newC < 8 && theBoard[3][newC] && !theBoard[2][newC]) {
                if(theBoard[3][newC]->pieceColour() == 'W' && theBoard[3][newC]->pieceType() == 'P'
                    && theBoard[3][newC]->justMoved2()) {
                    //apply changes
                    GamePiece* temp = theBoard[3][newC];
                    theBoard[newR][newC] = theBoard[r][c];
                    theBoard[r][c] = nullptr;
                    theBoard[3][newC] = nullptr;

                    //test if king will be in check
                    char enemyColour = colour  == 'B' ? 'W' : 'B';
                    if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                        possibleMoves.emplace_back(vector<int>{newR, newC});
                    }

                    //revert
                    theBoard[r][c] = theBoard[newR][newC];
                    theBoard[newR][newC] = nullptr;
                    theBoard[3][newC] = temp;
                }
            }

            //up left: occupied by white
            newR = r + possibleDirections[0][0];
            newC = c + possibleDirections[0][1];
            if(newR >= 0 && newR < 8 && newC >= 0 && newC < 8 && 
                theBoard[newR][newC] && theBoard[newR][newC]->pieceColour() == 'W') {
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
            //en passant case: newR has to be 2 + adjacency
            if(newR == 2 && newC >= 0 && newC < 8 && theBoard[3][newC] && !theBoard[2][newC]) {
                if(theBoard[3][newC]->pieceColour() == 'W' && theBoard[3][newC]->pieceType() == 'P'
                    && theBoard[3][newC]->justMoved2()) {
                    //apply changes
                    GamePiece* temp = theBoard[3][newC];
                    theBoard[newR][newC] = theBoard[r][c];
                    theBoard[r][c] = nullptr;
                    theBoard[3][newC] = nullptr;

                    //test if king will be in check
                    char enemyColour = colour  == 'B' ? 'W' : 'B';
                    if(!pieceUnderAttackBy(theBoard, kingPosition[0], kingPosition[1], enemyColour)) {
                        possibleMoves.emplace_back(vector<int>{newR, newC});
                    }

                    //revert
                    theBoard[r][c] = theBoard[newR][newC];
                    theBoard[newR][newC] = nullptr;
                    theBoard[3][newC] = temp;
                }
            }
            break;
        }
    }

    return possibleMoves;
}
