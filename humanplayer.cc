#include <vector>
#include <iostream>
#include <string>
#include "humanplayer.h"
#include "gameboard.h"
using namespace std;

class GameBoard;

vector<int> HumanPlayer::getMove(char colour){
    string pos1, pos2;
    cin >> pos1 >> pos2;
    vector<int> orig = GameBoard::posToCoords(pos1);
    vector<int> dest = GameBoard::posToCoords(pos2);
    return vector<int>{orig[0], orig[1], dest[0], dest[1]};
}

char HumanPlayer::promoteTo(){
    char promo;
    cin >> promo;
    while(promo != 'Q' && promo != 'R' && promo != 'N' && promo != 'B') {
        cout << "Invalid promotion" << endl;
        cin >> promo;
    }
    return promo;
}
