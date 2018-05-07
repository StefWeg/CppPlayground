//
//  board.cpp
//  Tic-Tac-Toe_v5 (structure methods)
//
//  Created by Stefan Węgrzyn on 30.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include "board.hpp"

using namespace std;

int board::getRows() {return num_rows;}
int board::getColumns() {return num_columns;}

char board::getSymbol(int rowCoordinate, int columnCoordinate)
{
    if (ifCreated)
    {
        if (rowCoordinate >= 0 && rowCoordinate <= num_rows-1 && columnCoordinate >= 0 && columnCoordinate <= num_columns-1)
        {
            return boardItself[rowCoordinate][columnCoordinate];
        }
        else {string error = "wrong parameters!"; throw error;}
    }
    else {string error = "board was not created!"; throw error;}
}

void board::setSymbol(int rowCoordinate, int columnCoordinate, char sign)
{
    if (ifCreated)
    {
        if (rowCoordinate >= 0 && rowCoordinate <= num_rows-1 && columnCoordinate >= 0 && columnCoordinate <= num_columns-1)
        {
            boardItself[rowCoordinate][columnCoordinate] = sign;
        }
        else {string error = "wrong parameters!"; throw error;}
    }
    else {string error = "board was not created!"; throw error;}
}

void board::setSize(int size)
{
    num_rows = size;
    num_columns = size;
}

void board::createBoard()
{
    // creating gameBoard
    boardItself = new char*[num_rows];
    for (int i = 0; i < num_rows; i++)
    {
        boardItself[i] = new char[num_columns];
    }
    // cleaning gameBoard
    for ( int i = 0; i < num_rows; i++ )
    {
        for ( int j = 0; j < num_columns; j++ )
        {
            boardItself[i][j] = '_';
        }
    }
    ifCreated = true;
}

void board::display()
{
    for ( int i = 0; i < num_rows; i++ )
    {
        cout << "|";
        for ( int j = 0; j < num_columns; j++ )
        {
            cout << " " << boardItself[i][j];
        }
        cout << " |" << endl;
    }
}

bool board::checkFull()
{
    if (ifCreated)
    {
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_columns; j++)
            {
                if (boardItself[i][j] == '_') return false;
            }
        }
        return true;
    }
    else {string error = "board was not created!"; throw error;}
}

bool board::checkWin()
{
    // lateral
    for ( int i = 0; i < num_rows; i++ ) // checking every row
    {
        for ( int j = 0; j < (num_columns-1); j++ ) // -1 because of the 'if' equation
        {
            if ( boardItself[i][j] != boardItself[i][j+1]) break;
            if ( j == num_columns-2 && boardItself[i][j] != '_' ) return true; // if 'j == (num_columns-2)' and program is executing here - someone won!
        }
    }
    // vertical
    for ( int i = 0; i < num_columns; i++ ) // checking every column
    {
        for ( int j = 0; j < (num_rows-1); j++ ) // -1 because of the 'if' equation
        {
            if ( boardItself[j][i] != boardItself[j+1][i]) break;
            if ( j == num_rows-2 && boardItself[j][i] != '_'  ) return true; // if 'j == (num_rows-2)' and program is executing here - someone won!
        }
    }
    if (num_rows == num_columns)
    {
        // \diagonal
        for ( int i = 0; i < (num_rows-1); i++ ) // -1 because of the 'if' equation
        {
            if ( boardItself[i][i] != boardItself[i+1][i+1] ) break;
            if ( i == (num_rows-2) && boardItself[i][i] != '_' ) return true; // if 'i == (num_rows-2)' and program is executing here - someone won!
        }
        // /diagonal
        for ( int j = 0; j < (num_rows-1); j++ ) // -1 because of the 'if' equation
        {
            if ( boardItself[j][(num_rows-1)-j] != boardItself[j+1][(num_rows-1)-j-1] ) break; // for example for num_rows = 3 --> (board[0][2] == board[1][1] && board[1][1] == board[2][0])
            if ( j == (num_rows-2) && boardItself[j][(num_rows-1)-j] != '_' ) return true; // if 'j == (num_rows-2)' and program is executing here - someone won!
        }
    }
    return false;
}

void board::clear()
{
    // deallocation of pointers
    for (int i = 0; i < num_rows; i++)
    {
        delete[] boardItself[i];
    }
    
    delete[] boardItself;
    ifCreated = false;
}