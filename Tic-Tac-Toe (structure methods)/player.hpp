//
//  player.hpp
//  Tic-Tac-Toe_v5 (structure methods)
//
//  Created by Stefan Węgrzyn on 30.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <string>
using namespace std;

struct player
{
    string name = "";
    char symbol = '_';
    bool winIndicator = false;
    void setName (string input);
    string getName ();
    void setSymbol (char sign);
    char getSymbol ();
    void setWin (bool expression);
    bool getWin ();
};

#endif /* player_hpp */
