//
//  board.hpp
//  Tic-Tac-Toe_v5 (structure methods)
//
//  Created by Stefan Węgrzyn on 30.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>

struct board
{
    char** boardItself = NULL;
    bool ifCreated = false;
    int num_rows = 0;
    int num_columns = 0;
    int getRows ();
    int getColumns ();
    char getSymbol (int rowCoordinate, int columnCoordinate);
    void setSymbol (int rowCoordinate, int columnCoordinate, char sign);
    void setSize (int size);
    void createBoard ();
    void display ();
    bool checkFull ();
    bool checkWin ();
    void clear ();
};

#endif /* board_hpp */
