//
//  board.cpp
//  Tic-Tac-Toe_v6 (classes)
//
//  Created by Stefan Węgrzyn on 30.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include "board.hpp"

using namespace std;

board::board()
    : board(3)
{}

board::board(int size)
    : _boardItself(NULL)
    , _num_rows(size)
    , _num_columns(size)
{
    // creating gameBoard
    _boardItself = new char*[_num_rows];
    for (int i = 0; i < _num_rows; i++)
    {
        _boardItself[i] = new char[_num_columns];
    }
    // cleaning gameBoard
    for ( int i = 0; i < _num_rows; i++ )
    {
        for ( int j = 0; j < _num_columns; j++ )
        {
            _boardItself[i][j] = '_';
        }
    }
}

board::board (const board &other)
    : _boardItself(NULL)
    , _num_rows(other._num_rows)
    , _num_columns(other._num_columns)
{
    // creating gameBoard
    _boardItself = new char*[_num_rows];
    for (int i = 0; i < _num_rows; i++)
    {
        _boardItself[i] = new char[_num_columns];
    }
    // inserting symbols from other board into this board
    for ( int i = 0; i < _num_rows; i++ )
    {
        for ( int j = 0; j < _num_columns; j++ )
        {
            _boardItself[i][j] = other._boardItself[i][j];
        }
    }
}

board& board::operator= (const board& other)
{
    if (&other == this) return *this;
    if (other._num_rows != this->_num_rows)
    {string error = "cannot assign board of different size!"; throw error;}
    // inserting symbols from other board into this board
    for ( int i = 0; i < _num_rows; i++ )
    {
        for ( int j = 0; j < _num_columns; j++ )
        {
            _boardItself[i][j] = other._boardItself[i][j];
        }
    }
    return *this;
}

board::~board()
{
    // deallocation of pointers
    for (int i = 0; i < _num_rows; i++)
    {
        delete[] _boardItself[i];
    }
    
    delete[] _boardItself;
}

const int board::getRows() {return _num_rows;}

const int board::getColumns() {return _num_columns;}

char board::getSymbol(int rowCoordinate, int columnCoordinate)
{
    if (rowCoordinate >= 0 && rowCoordinate <= _num_rows-1 && columnCoordinate >= 0 && columnCoordinate <= _num_columns-1)
    {
        return _boardItself[rowCoordinate][columnCoordinate];
    }
    else {string error = "wrong parameters!"; throw error;}
}

void board::setSymbol(int rowCoordinate, int columnCoordinate, char sign)
{
    if (rowCoordinate >= 0 && rowCoordinate <= _num_rows-1 && columnCoordinate >= 0 && columnCoordinate <= _num_columns-1)
    {
        _boardItself[rowCoordinate][columnCoordinate] = sign;
    }
    else {string error = "wrong parameters!"; throw error;}
}

void board::display()
{
    for ( int i = 0; i < _num_rows; i++ )
    {
        cout << "|";
        for ( int j = 0; j < _num_columns; j++ )
        {
            cout << " " << _boardItself[i][j];
        }
        cout << " |" << endl;
    }
}

bool board::checkFull()
{
    for (int i = 0; i < _num_rows; i++)
    {
        for (int j = 0; j < _num_columns; j++)
        {
            if (_boardItself[i][j] == '_') return false;
        }
    }
    return true;
}

bool board::checkWin()
{
    // lateral
    for ( int i = 0; i < _num_rows; i++ ) // checking every row
    {
        for ( int j = 0; j < (_num_columns-1); j++ ) // -1 because of the 'if' equation
        {
            if ( _boardItself[i][j] != _boardItself[i][j+1]) break;
            if ( j == _num_columns-2 && _boardItself[i][j] != '_' ) return true; // if 'j == (num_columns-2)' and program is executing here - someone won!
        }
    }
    // vertical
    for ( int i = 0; i < _num_columns; i++ ) // checking every column
    {
        for ( int j = 0; j < (_num_rows-1); j++ ) // -1 because of the 'if' equation
        {
            if ( _boardItself[j][i] != _boardItself[j+1][i]) break;
            if ( j == _num_rows-2 && _boardItself[j][i] != '_'  ) return true; // if 'j == (num_rows-2)' and program is executing here - someone won!
        }
    }
    if (_num_rows == _num_columns)
    {
        // \diagonal
        for ( int i = 0; i < (_num_rows-1); i++ ) // -1 because of the 'if' equation
        {
            if ( _boardItself[i][i] != _boardItself[i+1][i+1] ) break;
            if ( i == (_num_rows-2) && _boardItself[i][i] != '_' ) return true; // if 'i == (num_rows-2)' and program is executing here - someone won!
        }
        // /diagonal
        for ( int j = 0; j < (_num_rows-1); j++ ) // -1 because of the 'if' equation
        {
            if ( _boardItself[j][(_num_rows-1)-j] != _boardItself[j+1][(_num_rows-1)-j-1] ) break; // for example for num_rows = 3 --> (board[0][2] == board[1][1] && board[1][1] == board[2][0])
            if ( j == (_num_rows-2) && _boardItself[j][(_num_rows-1)-j] != '_' ) return true; // if 'j == (num_rows-2)' and program is executing here - someone won!
        }
    }
    return false;
}

void board::clear()
{
    for ( int i = 0; i < _num_rows; i++ )
    {
        for ( int j = 0; j < _num_columns; j++ )
        {
            _boardItself[i][j] = '_';
        }
    }
}