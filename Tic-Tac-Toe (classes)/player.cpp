//
//  player.cpp
//  Tic-Tac-Toe_v6 (classes)
//
//  Created by Stefan Węgrzyn on 30.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <string>
#include "player.hpp"

using namespace std;

player::player(string name, char symbol)
    : _name(name)
    , _symbol(symbol)
    , _winIndicator(false)
{}

const string player::getName() {return _name;}
const char player::getSymbol() {return _symbol;}
void player::setWin(bool expression) {_winIndicator = expression;}
bool player::getWin() {return _winIndicator;}
