//
//  player.hpp
//  Tic-Tac-Toe_v6 (classes)
//
//  Created by Stefan Węgrzyn on 30.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <string>
using namespace std;

class player
{
public:
    player (string name, char symbol);
    const string getName ();
    const char getSymbol ();
    void setWin (bool expression);
    bool getWin ();
private:
    player (const player& other); // turning off copy constructor
    player& operator= (const player& other); // turning off assignment operator
    const string _name;
    const char _symbol;
    bool _winIndicator;
};

#endif /* player_hpp */
