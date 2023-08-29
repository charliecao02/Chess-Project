#include <iostream>
#include <vector>
#include <cmath>
#include "gameboard.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "sdl_wrap.h"
using namespace std;

GameBoard::GameBoard(Screen *s): theBoard{}, td{nullptr}, gd{nullptr} {
    vector<GamePiece*> row;
    row.emplace_back(new Rook{'W', 0, 0, this});
    row.emplace_back(new Knight{'W', 0, 1, this});
    row.emplace_back(new Bishop{'W', 0, 2, this});
    row.emplace_back(new Queen{'W', 0, 3, this});
    row.emplace_back(new King{'W', 0, 4, this});
    row.emplace_back(new Bishop{'W', 0, 5, this});
    row.emplace_back(new Knight{'W', 0, 6, this});
    row.emplace_back(new Rook{'W', 0, 7, this});
    theBoard.emplace_back(row);
    row.clear();

    for (int i = 0; i < 8; ++i){
        row.emplace_back(new Pawn{'W', 1, i, this});
    }
    theBoard.emplace_back(row);
    row.clear();

    //empty squares
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 8; ++j){
            row.emplace_back(nullptr);
        }
        theBoard.emplace_back(row);
        row.clear();
    }

    for (int i = 0; i < 8; ++i){
        row.emplace_back(new Pawn{'B', 6, i, this});
    }
    theBoard.emplace_back(row);
    row.clear();

    row.emplace_back(new Rook{'B', 7, 0 , this});
    row.emplace_back(new Knight{'B', 7, 1, this});
    row.emplace_back(new Bishop{'B', 7, 2, this});
    row.emplace_back(new Queen{'B', 7, 3, this});
    row.emplace_back(new King{'B', 7, 4, this});
    row.emplace_back(new Bishop{'B', 7, 5, this});
    row.emplace_back(new Knight{'B', 7, 6, this});
    row.emplace_back(new Rook{'B', 7, 7, this});
    theBoard.emplace_back(row);

    td = new TextDisplay(theBoard);
    gd = new GraphicalDisplay{theBoard, s};
}
GameBoard::~GameBoard() {
    for (auto row: theBoard){
        for (auto piece: row){
            delete piece;
        }
    }
    delete td;
    delete gd;
}

void GameBoard::setup() {
    //clear board
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            delete theBoard[i][j];
            theBoard[i][j] = nullptr;
        }
    }
    td->update(&theBoard);
    gd->update(&theBoard);

    char colour = 'W'; // white goes first
    string action;
    while(cin >> action) {
        if(action == "+") {
            char piece;
            string position;
            cin >> piece >> position;
            vector<int> coords = posToCoords(position);
            int row = coords[0];
            int col = coords[1];
            delete theBoard[row][col];
            switch(piece) {
                case 'R':
                    theBoard[row][col] = new Rook{colour, row, col, this};
                    break;
                case 'N':
                    theBoard[row][col] = new Knight{colour, row, col, this};
                    break;
                case 'K':
                    theBoard[row][col] = new King{colour, row, col, this};
                    break;
                case 'Q':
                    theBoard[row][col] = new Queen{colour, row, col, this};
                    break;
                case 'P':
                    theBoard[row][col] = new Pawn{colour, row, col, this};
                    break;
                case 'B':
                    theBoard[row][col] = new Bishop{colour, row, col, this};
                    break;
            }
            //update also draws the boards
            td->update(&theBoard);
            gd->update(&theBoard);

        } else if(action == "-") {
            string position;
            cin >> position;
            vector<int> coords = posToCoords(position);
            int row = coords[0];
            int col = coords[1];
            delete theBoard[row][col];
            theBoard[row][col] = nullptr;
            td->update(&theBoard);
            gd->update(&theBoard);

        } else if(action == "=") {
            string col;
            cin >> col;
            if(col == "white") colour = 'W';
            else colour = 'B';

        } else if(action == "done") {
            int whitekings = 0, blackkings = 0;
            for (auto row: theBoard) {
                for (auto piece: row) {
                    if (piece != nullptr){
                        if(piece->pieceType() == 'K') {
                            if(piece->pieceColour() == 'W') ++whitekings;
                            else ++blackkings;
                        }
                    }
                }
            }

            int pawninfirstorlastrow = 0;
            for(int i = 0; i<8; ++i) {
                if (theBoard[0][i] != nullptr && theBoard[0][i]->pieceType() == 'P'){
                    ++pawninfirstorlastrow;
                }
                if (theBoard[7][i] != nullptr && theBoard[7][i]->pieceType() == 'P') {
                    ++pawninfirstorlastrow;
                }
            }

            if(blackkings != 1 || whitekings != 1) {
                cout << "Number of black or white kings is not equal to one! Please continue setup." << endl;
                continue;
            }

            if(pawninfirstorlastrow) {
                cout << "Pawns cannot be in the first or last row! Please continue setup." << endl;
                continue;
            }

            // make sure no kings are in check
            if (inCheck('W') || inCheck('B')){
                cout << "Kings cannot be in check! Please continue setup." << endl;
                continue;
            }
            break;
        }
        else cout << "Invalid Command" << endl;
    }
}

vector<vector<int>> GameBoard::getValidMoves(char colour, int R, int C){
    if (!theBoard[R][C]) return vector<vector<int>>{};
    char targetColour = theBoard[R][C]->pieceColour();
    if (targetColour != colour){
        return vector<vector<int>>{};
    }
    else {
        return theBoard[R][C] -> getValidMoves();
    }
}

int GameBoard::makeMove(int origR, int origC, int destR, int destC) {
    //en passant: delete correct pawn
    if (theBoard[origR][origC]->pieceType() == 'P'
        && (origC != destC) && !theBoard[destR][destC]){
        if (theBoard[origR][origC]->pieceColour() == 'W'){
            delete theBoard[4][destC];
            theBoard[4][destC] = nullptr;
        }
        else{
            delete theBoard[3][destC];
            theBoard[3][destC] = nullptr;
        }
    }

    delete theBoard[destR][destC];
    theBoard[destR][destC] = theBoard[origR][origC];
    theBoard[origR][origC] = nullptr;
    //update r and c
    theBoard[destR][destC] -> moveTo(destR, destC);
    theBoard[destR][destC] -> setNotMoved(false);

    //clear all justMovedTwo flags
    for (auto r: theBoard){
        for (auto p: r){
            if (p) p -> setMoved2(false);
        }
    }

    //pawn move 2 squares
    if (theBoard[destR][destC]->pieceType() == 'P' && abs(destR-origR)==2){
        theBoard[destR][destC] -> setMoved2(true);
    }

    //castling, move the rook
    if (theBoard[destR][destC]->pieceType() == 'K' && abs(destC-origC)==2){
        if (destC > origC){ //king side
            theBoard[destR][5] = theBoard[destR][7];
            theBoard[destR][7] = nullptr;
            theBoard[destR][5] -> moveTo(destR, 5);
            theBoard[destR][5] -> setNotMoved(false);
        }
        else { //queen side
            theBoard[destR][3] = theBoard[destR][0];
            theBoard[destR][0] = nullptr;
            theBoard[destR][3] -> moveTo(destR, 3);
            theBoard[destR][3] -> setNotMoved(false);
        }
    }

    //promotion
    if (theBoard[destR][destC]->pieceType() == 'P' && (destR==0 || destR==7)){
        //update displays in promote()
        return 1;
    }
    else { //no promotion
        td->update(&theBoard);
        gd->update(&theBoard);
        return 0;
    }
}

void GameBoard::promote(int r, int c, char type){
    char colour = theBoard[r][c]->pieceColour();
    delete theBoard[r][c];
    switch(type){
        case 'Q':
            theBoard[r][c] = new Queen{colour, r, c, this};
            break;
        case 'R':
            theBoard[r][c] = new Rook{colour, r, c, this};
            break;
        case 'N':
            theBoard[r][c] = new Knight{colour, r, c, this};
            break;
        case 'B':
            theBoard[r][c] = new Bishop{colour, r, c, this};
            break;
    }
    td->update(&theBoard);
    gd->update(&theBoard);
}

bool GameBoard::inCheck(char colour){
    int kingR, kingC;
    for(int r = 0; r < 8; ++r) {
        for(int c = 0; c < 8; ++c) {
            if(!theBoard[r][c]) continue;
            if(theBoard[r][c]->pieceType() == 'K' && 
                theBoard[r][c]->pieceColour() == colour){
                kingR = r;
                kingC = c;
            }
        }
    }
    GamePiece *king = theBoard[kingR][kingC];
    char enemyColour = colour  == 'B' ? 'W' : 'B';
    return king->pieceUnderAttackBy(theBoard, kingR, kingC, enemyColour);
}

int GameBoard::numMoves(char colour){
    int num = 0;
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            GamePiece *piece = theBoard[i][j];
            if (piece && piece->pieceColour() == colour){
                num += piece->getValidMoves().size();
            }
        }
    }
    return num;
}

bool GameBoard::onlyKings(){
    for (auto row: theBoard){
        for (auto piece: row){
            if (piece && piece->pieceType() != 'K') return false;
        }
    }
    return true;
}

void GameBoard::drawBoards() {
    cout << *td << endl;
    gd -> draw();
}

string GameBoard::coordsToPos(vector<int> coords) {
    int x = coords[0];
    int y = coords[1];

    string result;
    char letter = y + 97;
    int row = 8 - x;
    result.push_back(letter);
    result.push_back(row);
    return result;
}

vector<int> GameBoard::posToCoords(string pos) {
    char letter = pos[0];
    int row = pos[1] - '0';

    int x = row - 1;
    int y = letter - 97;
    return vector<int>{x, y};
}

vector<vector<GamePiece*>> GameBoard::getBoard() {
    return theBoard;
}
