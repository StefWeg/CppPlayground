//
//  board.hpp
//  Tic-Tac-Toe_v6 (classes)
//
//  Created by Stefan Węgrzyn on 30.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>

class board
{
public:
    board (); // constructor with no argument
    board (int size); // constructor with argument
    board (const board &other); // copy constructor
    board& operator= (const board& other); // assignment operator
    ~board (); // destructor
    const int getRows ();
    const int getColumns ();
    char getSymbol (int rowCoordinate, int columnCoordinate);
    void setSymbol (int rowCoordinate, int columnCoordinate, char sign);
    void display ();
    bool checkFull ();
    bool checkWin ();
    void clear ();
private:
    char** _boardItself;
    const int _num_rows;
    const int _num_columns;
};

#endif /* board_hpp */
