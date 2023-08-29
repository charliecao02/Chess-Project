#include "textdisplay.h"
#include "gamepiece.h"
#include <vector>
#include <iostream>
using namespace std;

TextDisplay::TextDisplay(vector<vector<GamePiece*>> board): curBoard{board} {}

void TextDisplay::update(vector<vector<GamePiece*>> *newBoard){
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            if (curBoard[i][j] != (*newBoard)[i][j]){
                curBoard[i][j] = (*newBoard)[i][j];
            }
        }
    }
    cout << *this << endl;
}

ostream &operator<<(ostream &out, TextDisplay &td){
    //rows in reverse order
    for (int i = 7; i >= 0; --i){
        out << i+1 << ' ';
        for (int j = 0; j < 8; ++j){
            GamePiece *piece = td.curBoard[i][j];
            if (piece != nullptr){
                if (piece->pieceColour() == 'W') out << piece->pieceType();
                else out << static_cast<char>(piece->pieceType() + 32);
            }
            else if ((i+j) % 2 == 0) out << '_';
            else out << ' ';
        }
        out << endl;
    }
    //out << endl;
    out << "  abcdefgh";
    return out;
}
