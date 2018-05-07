//
//  main.cpp
//  connect-4 v2
//
//  Created by Stefan Węgrzyn on 18.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////

struct board
{
    char** boardItself = NULL;
    int num_rows = 0;
    int num_columns = 0;
};

struct playerData
{
    string name = "";
    char symbol = '_';
    int num_moves = 0;
    bool winIndicator = false;
};


void getSize (int &size);
void boardDisplay (board& gameBoard);
void moveOfPlayer (board& gameBoard, playerData& currentPlayer);
bool checkWin (board& gameBoard, playerData& firstPlayer, playerData& secondPlayer);
bool checkFull (board& gameBoard, playerData& firstPlayer, playerData& secondPlayer);


int main ()
{
    // initializing gameBoard
    board gameBoard;
    
    // preparing players' data
    playerData firstPlayer;
    firstPlayer.symbol = '+';
    playerData secondPlayer;
    secondPlayer.symbol = 'x';
    
    // whole game loop
    do
    {
        
        firstPlayer.num_moves = 0;
        firstPlayer.winIndicator = false;
        secondPlayer.num_moves = 0;
        secondPlayer.winIndicator = false;
        
        // prompting user for size of gameBoard
        do
        {
            cout << "Enter number of rows (min 4): ";
            getSize(gameBoard.num_rows);
        } while (gameBoard.num_rows < 4);
        
        do
        {
            cout << "Enter number of columns (min 4): ";
            getSize(gameBoard.num_columns);
        } while (gameBoard.num_columns < 4);
        
        // creating gameBoard
        gameBoard.boardItself = new char*[gameBoard.num_rows];
        
        for (int i = 0; i < gameBoard.num_rows; i++)
        {
            gameBoard.boardItself[i] = new char[gameBoard.num_columns];
        }
        
        // cleaning gameBoard
        for ( int i = 0; i < gameBoard.num_rows; i++ )
        {
            for ( int j = 0; j < gameBoard.num_columns; j++ )
            {
                gameBoard.boardItself[i][j] = '_';
            }
        }
        
        // prompting user for names of players
        cout << "Enter name of first player: ";
        getline (cin, firstPlayer.name, '\n');
        cout << "Enter name of second player: ";
        getline (cin, secondPlayer.name, '\n');
        
        // main game loop
        playerData** playerIndicator = new playerData*[2];
        playerIndicator[0] = &firstPlayer;
        playerIndicator[1] = &secondPlayer;
        int whoseTurn = 1;
        bool winIndicator = false;
        bool fullBoard = false;
        
        while (!(winIndicator || fullBoard))
        {
            if (whoseTurn == 1) whoseTurn = 0;
            else whoseTurn = 1;
            
            moveOfPlayer (gameBoard, *playerIndicator[whoseTurn]);
            
            winIndicator = checkWin (gameBoard, firstPlayer, secondPlayer);
            fullBoard = checkFull (gameBoard, firstPlayer, secondPlayer);
        }
        
        // when game ends
        cout << endl;
        boardDisplay(gameBoard);
        cout << endl;
        
        if (winIndicator)
        {
            if (firstPlayer.winIndicator == true)
            {
                cout << firstPlayer.name << " won!" << endl;
            }
            else
            {
                cout << secondPlayer.name << " won!" << endl;
            }
        }
        
        if (fullBoard)
        {
            cout << "Board is full! No one won!" << endl;
        }
        
        // deallocation of pointers
        delete[] playerIndicator;
        
        for (int i = 0; i < gameBoard.num_rows; i++)
        {
            delete[] gameBoard.boardItself[i];
        }
        
        delete[] gameBoard.boardItself;
        
        // asking user if he wants to play ones more
        cout << "Want to play again?" << endl;
        cin.get();
        cin.get();
        
    } while (true);
    
    cout << "Game over." << endl;
    
    return 0;
}




void getSize (int &size)
{
    string input;
    getline(cin, input, '\n');
    
    try
    {
        size = stoi(input);
    }
    catch (...)
    {
        cout << "Wrong input!" << endl;
    }
}

void boardDisplay (board& gameBoard)
{
    for ( int i = 0; i < gameBoard.num_rows; i++ )
    {
        cout << "|";
        for ( int j = 0; j < gameBoard.num_columns; j++ )
        {
            cout << " " << gameBoard.boardItself[i][j];
        }
        cout << " |" << endl;
    }
}

void moveOfPlayer (board& gameBoard, playerData &currentPlayer)
{
    currentPlayer.num_moves++;
    
    while ( true ) // loop of player's move
    {
        cout << endl;
        
        // displaying board
        boardDisplay (gameBoard);
        
        // move procedures
        int row = 0;
        int column = 0;
        
        cout << endl << currentPlayer.name << " (" << currentPlayer.symbol << ")" << endl;
        
        cout << "Choose row: ";
        cin >> row;
        row = row - 1; // first row is going to be '0' value of array etc.
        
        cout << "Choose column: ";
        cin >> column;
        column = column - 1; // the same reason ^
        
        if ( row > (gameBoard.num_rows-1) || row < 0 || column > (gameBoard.num_columns-1) || column < 0 )
        {
            cout << "Wrong input!" << endl;
            continue;
        }
        else if ( gameBoard.boardItself[row][column] == '_' )
        {
            gameBoard.boardItself[row][column] = currentPlayer.symbol;
            break;
        }
        else
        {
            cout << "You can't put " << currentPlayer.symbol << " in that spot!" << endl;
        }
    }
    
}

bool checkWin (board& gameBoard, playerData& firstPlayer, playerData& secondPlayer)
{
    // lateral
    int fillToThree = 0; // three correct equations means there are four the same characters in row
    
    for ( int i = 0; i < gameBoard.num_rows; i++ ) // checking every row
    {
        for ( int j = 0; j < (gameBoard.num_columns-1); j++ ) // -1 because of the 'if' equation
        {
            if ( gameBoard.boardItself[i][j] == gameBoard.boardItself[i][j+1] && gameBoard.boardItself[i][j] != '_' )
            {
                fillToThree++;
            }
            else
            {
                fillToThree = 0;
            }
            
            if ( fillToThree == 3 )
            {
                if (gameBoard.boardItself[i][j] == firstPlayer.symbol) firstPlayer.winIndicator = true;
                else secondPlayer.winIndicator = true;
                return true;
            }
        }
    }
    
    // vertical
    fillToThree = 0;
    
    for ( int i = 0; i < gameBoard.num_columns; i++ ) // checking every column
    {
        for ( int j = 0; j < (gameBoard.num_rows-1); j++ ) // -1 because of the 'if' equation
        {
            if ( gameBoard.boardItself[j][i] == gameBoard.boardItself[j+1][i] && gameBoard.boardItself[j][i] != '_' )
            {
                fillToThree++;
            }
            else
            {
                fillToThree = 0;
            }
            
            if ( fillToThree == 3 )
            {
                if (gameBoard.boardItself[j][i] == firstPlayer.symbol) firstPlayer.winIndicator = true;
                else secondPlayer.winIndicator = true;
                return true;
            }
        }
    }
    
    return false;
}

bool checkFull (board& gameBoard, playerData& firstPlayer, playerData& secondPlayer)
{
    if (firstPlayer.num_moves + secondPlayer.num_moves == gameBoard.num_rows * gameBoard.num_columns)
    {
        return true;
    }
    return false;
}
