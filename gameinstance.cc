#include "gameinstance.h"
#include "sdl_wrap.h"
#include <iostream>
#include <algorithm>
using namespace std;

GameInstance::GameInstance(Screen *s): board{s}, p1{nullptr}, p2{nullptr}, winner{0} {}

GameInstance::~GameInstance(){
    delete p1;
    delete p2;
}

void GameInstance::setup(){
    //erase default board and place pieces
    board.setup();
}

char GameInstance::playGame(Player *player1, Player *player2){
    p1 = player1;
    p2 = player2;
    //draw textDisplay, graphicalDisplay first time
    //use update when game is running
    board.drawBoards();
    char winner = 0;
    char turn = 'W'; // white goes first
    vector<int> move;
    string command;
    while(winner == 0) {
        //if only kings remains, stalemate
        if (board.onlyKings()){
            cout << "Stalemate!" << endl;
            winner = 'T';
            break;
        }

        if (turn == 'W') cout << "Player 1's move:" << endl;
        else cout << "Player 2's move:" << endl;
        cin >> command;
        if(command == "move") {
            if(turn == 'W') {
                move = p1->getMove('W');
                //validation: you own that piece, valid move, if pawn promotion call promoteTo?
                int origR = move[0];
                int origC = move[1];
                int destR = move[2];
                int destC = move[3];
                vector<int> destCoord = vector<int>{destR, destC};
                vector<vector<int>> validMoves = board.getValidMoves('W', origR, origC);
                if (find(validMoves.begin(), validMoves.end(), destCoord) != validMoves.end()){
                    int promote = board.makeMove(origR, origC, destR, destC);
                    if (promote){
                        char promoteTo = p1->promoteTo();
                        board.promote(destR, destC, promoteTo);
                    }
                    turn = 'B';
                    //test if check or checkmate or stalemate
                    int numMoves = board.numMoves('B');
                    if (board.inCheck('B')){
                        cout << "Black is in check." << endl;
                        if (numMoves == 0){
                            cout << "Checkmate! White wins!" << endl;
                            winner = 'W';
                        }
                    }
                    else if (numMoves == 0){
                        cout << "Stalemate!" << endl;
                        winner = 'T';
                    }
                }
                else cout << "Invalid Move! Try again" << endl;
            } else {
                move = p2->getMove('B');
                //validation: you own that piece, valid move, if pawn promotion call promoteTo?
                int origR = move[0];
                int origC = move[1];
                int destR = move[2];
                int destC = move[3];
                vector<int> destCoord = vector<int>{destR, destC};
                vector<vector<int>> validMoves = board.getValidMoves('B', origR, origC);
                if (find(validMoves.begin(), validMoves.end(), destCoord) != validMoves.end()){
                    int promote = board.makeMove(origR, origC, destR, destC);
                    if (promote){
                        char promoteTo = p2->promoteTo();
                        board.promote(destR, destC, promoteTo);
                    }
                    turn = 'W';
                    //test if check or checkmate or stalemate
                    int numMoves = board.numMoves('W');
                    if (board.inCheck('W')){
                        cout << "White is in check." << endl;
                        if (numMoves == 0){
                            cout << "Checkmate! Black wins!" << endl;
                            winner = 'B';
                        }
                    }
                    else if (numMoves == 0){
                        cout << "Stalemate!" << endl;
                        winner = 'T';
                    }
                }
                else cout << "Invalid Move! Try again" << endl;
            }
        }
        else if (command == "resign"){
            //resign
            if (turn == 'W'){
                cout << "White resigns." << endl;
                winner = 'B';
            }
            else {
                cout << "Black resigns." << endl;
                winner = 'W';
            }
        }
        else cout << "Invalid Command" << endl;
    }

    return winner; // this is for keeping score in the end, returns W, B, or T for tie
}

GameBoard* GameInstance::getBoard() {
    return &board;
}
