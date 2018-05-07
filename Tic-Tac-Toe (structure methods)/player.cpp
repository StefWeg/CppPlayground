//
//  player.cpp
//  Tic-Tac-Toe_v5 (structure methods)
//
//  Created by Stefan Węgrzyn on 30.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <string>
#include "player.hpp"

using namespace std;

void player::setName(string input) {name = input;}
string player::getName() {return name;}
void player::setSymbol(char sign) {symbol = sign;}
char player::getSymbol() {return symbol;}
void player::setWin(bool expression) {winIndicator = expression;}
bool player::getWin() {return winIndicator;}