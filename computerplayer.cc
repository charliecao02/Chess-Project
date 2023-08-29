#include <vector>
#include <random>
#include <iostream>
#include <string>
#include "computerplayer.h"
#include "gameboard.h"
using namespace std;

ComputerPlayer::ComputerPlayer(GameBoard* board, int level) : board{board}, level{level} {}

char ComputerPlayer::promoteTo(){
    if (level == 1){
        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<int> dist(0, 3);
        char choices[4] = {'Q', 'R', 'N', 'B'};
        return choices[dist(mt)];
    }
    else return 'Q';
}

vector<vector<int>> ComputerPlayer::captureAndCheck(char colour, vector<vector<int>> possibleMoves) {
    vector<vector<int>> capturesAndChecks;

    vector<vector<int>> tilesUnderAttack;
    for(int i = 0; i<8; ++i) {
        for(int j = 0; j<8; ++j) {
            if(board->getBoard()[i][j] && board->getBoard()[i][j]->pieceUnderAttackBy(board->getBoard(), i, j, colour)) {
                tilesUnderAttack.emplace_back(vector<int>{i, j});
            }
        }
    }

    // captures
    for(vector<int> move : possibleMoves) {
        for(vector<int> tile : tilesUnderAttack) {
            if(move[2] == tile[0] && move[3] == tile[1]) capturesAndChecks.emplace_back(move);
        }
    }

    // checks
    GamePiece* enemyKing;
    vector<int> enemyKingPosition;
    for(int i = 0; i<8; ++i) {
        for(int j = 0; j<8; ++j) {
            if(board->getBoard()[i][j] && board->getBoard()[i][j]->pieceType() == 'K' && board->getBoard()[i][j]->pieceColour() != colour) {
                enemyKing = board->getBoard()[i][j];
                enemyKingPosition = vector<int>{i, j};
            }
        }
    }
    
    for(vector<int> move : possibleMoves) {
        int oldR = move[0], oldC = move[1];
        int newR = move[2], newC = move[3];

        GamePiece* temp = board->getBoard()[newR][newC];
        board->getBoard()[newR][newC] = board->getBoard()[oldR][oldC];
        board->getBoard()[oldR][oldC] = nullptr;

        if(enemyKing->pieceUnderAttackBy(board->getBoard(), enemyKingPosition[0], enemyKingPosition[1], colour)) {
            capturesAndChecks.emplace_back(move);
        }

        //revert
        board->getBoard()[oldR][oldC] = board->getBoard()[newR][newC];
        board->getBoard()[newR][newC] = temp;
    }
    
    return capturesAndChecks;
}

vector<vector<int>> ComputerPlayer::avoidCapture(char colour, vector<vector<int>> capturesAndChecks) {
    vector<vector<int>> avoidsCapture;
    for(vector<int> move : capturesAndChecks) {
        int oldR = move[0], oldC = move[1];
        int newR = move[2], newC = move[3];
        GamePiece* pieceToMove = board->getBoard()[oldR][oldC];
        GamePiece* temp = board->getBoard()[newR][newC];
        board->getBoard()[newR][newC] = pieceToMove;
        board->getBoard()[oldR][oldC] = nullptr;

        char enemyColour = (colour == 'W') ? 'B' : 'W';

        if(!pieceToMove->pieceUnderAttackBy(board->getBoard(), newR, newC, enemyColour)) {
            avoidsCapture.emplace_back(move);
        }

        //revert
        board->getBoard()[oldR][oldC] = pieceToMove;
        board->getBoard()[newR][newC] = temp;
    }
    return avoidsCapture;
}

vector<vector<int>> ComputerPlayer::tryToCapture(char colour, char enemyPiece, vector<vector<int>> capturesAndChecks) {
    char enemyColour = (colour == 'W') ? 'B' : 'W';
    vector<vector<int>> capture;
    for(vector<int> move : capturesAndChecks) {
        int newR = move[2], newC = move[3];
        if(board->getBoard()[newR][newC] && board->getBoard()[newR][newC]->pieceType() == enemyPiece
                && board->getBoard()[newR][newC]->pieceColour() == enemyColour) {
                    capture.emplace_back(move);
                }
    }
    return capture;
}

vector<int> ComputerPlayer::getMove(char colour){

    random_device rd;
    mt19937 mt(rd());

    vector<vector<int>> possibleMoves;
    
    for(int i = 0; i<8; ++i) {
        for(int j = 0; j<8; ++j) {
            for(vector<int> move : board->getValidMoves(colour, i, j)) { // move is newR and newC
                possibleMoves.emplace_back(vector<int>{i, j, move[0], move[1]}); // possibleMoves{originalR, originalC, newR, newC}
            }
        }
    }

    switch(level) {
        case 1:{
            // random legal moves
            uniform_int_distribution<int> dist(0, possibleMoves.size() - 1);
            return possibleMoves[dist(mt)];
            break;
        }
        case 2:{
            // prefers captures and checks
            vector<vector<int>> capturesAndChecks = captureAndCheck(colour, possibleMoves);
            if(capturesAndChecks.size() > 0) {
                uniform_int_distribution<int> dist(0, capturesAndChecks.size() - 1);
                return capturesAndChecks[dist(mt)];
            } else {
                uniform_int_distribution<int> dist(0, possibleMoves.size() - 1);
                return possibleMoves[dist(mt)];
            }
            break;
        }
        case 3:{
            vector<vector<int>> capturesAndChecks = captureAndCheck(colour, possibleMoves);
            vector<vector<int>> avoidsCapture = avoidCapture(colour, capturesAndChecks);
            
            if(avoidsCapture.size() > 0) {
                uniform_int_distribution<int> dist(0, avoidsCapture.size() - 1);
                return avoidsCapture[dist(mt)]; 
            } else if(capturesAndChecks.size() > 0) {
                uniform_int_distribution<int> dist(0, capturesAndChecks.size() - 1);
                return capturesAndChecks[dist(mt)];
            } else {
                uniform_int_distribution<int> dist(0, possibleMoves.size() - 1);
                return possibleMoves[dist(mt)];
            }
            break;
        }
        case 4:{
            vector<vector<int>> capturesAndChecks = captureAndCheck(colour, possibleMoves);
            vector<vector<int>> avoidsCapture = avoidCapture(colour, capturesAndChecks);

            char enemyColour = (colour == 'W') ? 'B' : 'W';

            // try to capture enemy queen
            vector<vector<int>> queenCapturesWhileAvoidingCapture = tryToCapture(colour, 'Q', avoidsCapture);
            if(queenCapturesWhileAvoidingCapture.size() > 0) {
                uniform_int_distribution<int> dist(0, queenCapturesWhileAvoidingCapture.size() - 1);
                return queenCapturesWhileAvoidingCapture[dist(mt)];
            }
            vector<vector<int>> queenCaptures = tryToCapture(colour, 'Q', capturesAndChecks);
            if(queenCaptures.size() > 0) {
                uniform_int_distribution<int> dist(0, queenCaptures.size() - 1);
                return queenCaptures[dist(mt)];
            }

            // try to save our queen(s)
            vector<vector<int>> saveQueens;
            vector<vector<int>> queenCaptureAndCheckSafely;
            for(int i = 0; i<8; ++i) {
                for(int j = 0; j<8; ++j) {
                    if(board->getBoard()[i][j] && board->getBoard()[i][j]->pieceType() == 'Q' && board->getBoard()[i][j]->pieceColour() == colour) {
                        if(board->getBoard()[i][j]->pieceUnderAttackBy(board->getBoard(), i, j, enemyColour)) {
                            vector<vector<int>> queenMoves;
                            for(vector<int> move : possibleMoves) {
                                if(move[0] == i && move[1] == j) {
                                    queenMoves.emplace_back(move);
                                }
                            }
                            for(vector<int> move : avoidCapture(colour, captureAndCheck(colour, queenMoves)))
                                queenCaptureAndCheckSafely.emplace_back(move);
                            for(vector<int> move : avoidCapture(colour, queenMoves))
                                saveQueens.emplace_back(move);
                        }
                    }
                }
            }
            if(queenCaptureAndCheckSafely.size() > 0) {
                uniform_int_distribution<int> dist(0, queenCaptureAndCheckSafely.size() - 1);
                return queenCaptureAndCheckSafely[dist(mt)];
            }
            if(saveQueens.size() > 0) {
                uniform_int_distribution<int> dist(0, saveQueens.size() - 1);
                return saveQueens[dist(mt)];
            }

            // moves from now on shouldn't trade our queens
            vector<vector<int>> safeQueenMoves;
            for(int i = 0; i<8; ++i) {
                for(int j = 0; j<8; ++j) {
                    if(board->getBoard()[i][j] && board->getBoard()[i][j]->pieceType() == 'Q' && board->getBoard()[i][j]->pieceColour() == colour) {
                        vector<vector<int>> queenMoves;
                        for(vector<int> move : possibleMoves) {
                            if(move[0] == i && move[1] == j) {
                                queenMoves.emplace_back(move);
                            }
                        }
                        for(vector<int> move : avoidCapture(colour, queenMoves))
                            safeQueenMoves.emplace_back(move);
                    }
                }
            }
            vector<vector<int>> temp;
            for(vector<int> move : possibleMoves) {
                int i = move[0], j = move[1];
                if(!(board->getBoard()[i][j] && board->getBoard()[i][j]->pieceType() == 'Q' && board->getBoard()[i][j]->pieceColour() == colour)) {
                    temp.emplace_back(move);
                }
            }
            for(vector<int> move : safeQueenMoves) {
                temp.emplace_back(move);
            }
            possibleMoves = temp;
            capturesAndChecks = captureAndCheck(colour, possibleMoves);
            avoidsCapture = avoidCapture(colour, capturesAndChecks);

            // try to capture enemy rook
            vector<vector<int>> rookCapturesWhileAvoidingCapture = tryToCapture(colour, 'R', avoidsCapture);
            if(rookCapturesWhileAvoidingCapture.size() > 0) {
                uniform_int_distribution<int> dist(0, rookCapturesWhileAvoidingCapture.size() - 1);
                return rookCapturesWhileAvoidingCapture[dist(mt)];
            }
            vector<vector<int>> rookCaptures = tryToCapture(colour, 'R', capturesAndChecks);
            if(rookCaptures.size() > 0) {
                uniform_int_distribution<int> dist(0, rookCaptures.size() - 1);
                return rookCaptures[dist(mt)];
            }

            // try to save our rooks
            vector<vector<int>> saveRooks;
            vector<vector<int>> rookCaptureAndCheckSafely;
            for(int i = 0; i<8; ++i) {
                for(int j = 0; j<8; ++j) {
                    if(board->getBoard()[i][j] && board->getBoard()[i][j]->pieceType() == 'R' && board->getBoard()[i][j]->pieceColour() == colour) {
                        if(board->getBoard()[i][j]->pieceUnderAttackBy(board->getBoard(), i, j, enemyColour)) {
                            vector<vector<int>> rookMoves;
                            for(vector<int> move : possibleMoves) {
                                if(move[0] == i && move[1] == j) {
                                    rookMoves.emplace_back(move);
                                }
                            }
                            for(vector<int> move : avoidCapture(colour, captureAndCheck(colour, rookMoves)))
                                rookCaptureAndCheckSafely.emplace_back(move);
                            for(vector<int> move : avoidCapture(colour, rookMoves))
                                saveRooks.emplace_back(move);
                        }
                    }
                }
            }
            if(rookCaptureAndCheckSafely.size() > 0) {
                uniform_int_distribution<int> dist(0, rookCaptureAndCheckSafely.size() - 1);
                return rookCaptureAndCheckSafely[dist(mt)];
            }
            if(saveRooks.size() > 0) {
                uniform_int_distribution<int> dist(0, saveRooks.size() - 1);
                return saveRooks[dist(mt)];
            }

            // try to capture enemy bishop or knight
            vector<vector<int>> bishopCapturesWhileAvoidingCapture = tryToCapture(colour, 'B', avoidsCapture);
            vector<vector<int>> knightCapturesWhileAvoidingCapture = tryToCapture(colour, 'N', avoidsCapture);
            if(bishopCapturesWhileAvoidingCapture.size() > 0) {
                uniform_int_distribution<int> dist(0, bishopCapturesWhileAvoidingCapture.size() - 1);
                return bishopCapturesWhileAvoidingCapture[dist(mt)];
            }
            if(knightCapturesWhileAvoidingCapture.size() > 0) {
                uniform_int_distribution<int> dist(0, knightCapturesWhileAvoidingCapture.size() - 1);
                return knightCapturesWhileAvoidingCapture[dist(mt)];
            }
            vector<vector<int>> bishopCaptures = tryToCapture(colour, 'B', capturesAndChecks);
            vector<vector<int>> knightCaptures = tryToCapture(colour, 'N', capturesAndChecks);
            if(bishopCaptures.size() > 0) {
                uniform_int_distribution<int> dist(0, bishopCaptures.size() - 1);
                return bishopCaptures[dist(mt)];
            }
            if(knightCaptures.size() > 0) {
                uniform_int_distribution<int> dist(0, knightCaptures.size() - 1);
                return knightCaptures[dist(mt)];
            }

            // last resort 
            if(avoidsCapture.size() > 0) {
                uniform_int_distribution<int> dist(0, avoidsCapture.size() - 1);
                return avoidsCapture[dist(mt)]; 
            } else if(capturesAndChecks.size() > 0) {
                uniform_int_distribution<int> dist(0, capturesAndChecks.size() - 1);
                return capturesAndChecks[dist(mt)];
            } else {
                uniform_int_distribution<int> dist(0, possibleMoves.size() - 1);
                return possibleMoves[dist(mt)];
            }

            break;
        }
        default:{
            break;
        }
    }

    cout << "reached end" << endl;
    return possibleMoves[0];
}
