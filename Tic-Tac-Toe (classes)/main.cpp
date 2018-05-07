//
//  main.cpp
//  Tic-Tac-Toe_v6 (classes)
//
//  Created by Stefan Węgrzyn on 30.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include "board.hpp"
#include "player.hpp"

using namespace std;


void moveOfPlayer (board& gameBoard, player& currentPlayer);


int main ()
{
    // initializing gameBoard
    board gameBoard(3);
    
    // whole game loop
    bool ifContinue;
    do
    {
        ifContinue = true;
        
        gameBoard.clear();
        
        // prompting user for names of players
        string* input = new string;
        cout << "Enter name of first player: ";
        getline (cin, *input, '\n');
        player firstPlayer (*input, 'o');
        cout << "Enter name of second player: ";
        getline (cin, *input, '\n');
        player secondPlayer (*input, 'x');
        
        // main game loop
        player** playerIndicator = new player*[2];
        playerIndicator[0] = &firstPlayer;
        playerIndicator[1] = &secondPlayer;
        int whoseTurn = 1;
        
        while ( !( gameBoard.checkWin() || gameBoard.checkFull() ) )
        {
            if (whoseTurn == 1) whoseTurn = 0;
            else whoseTurn = 1;
            
            moveOfPlayer (gameBoard, *playerIndicator[whoseTurn]);
        }
        
        // when game ends
        cout << endl;
        gameBoard.display();
        cout << endl;
        
        if (gameBoard.checkWin())
        {
            // player winning is the one that made the last move
            (*playerIndicator[whoseTurn]).setWin(true);
            if (firstPlayer.getWin()) cout << firstPlayer.getName() << " won!" << endl;
            else cout << secondPlayer.getName() << " won!" << endl;
        }
        
        if (gameBoard.checkFull())
        {
            cout << "Board is full! No one won!" << endl;
        }
        
        // deallocation of pointers
        delete[] playerIndicator;
        
        // asking user if he wants to play ones more
        cout << "Want to play again? Enter anything but 0: ";
        cin.get();
        getline (cin, *input, '\n');
        if (*input == "0") ifContinue = false;
        cout << endl;
        delete input;
        
    } while (ifContinue);
    
    cout << "Game over." << endl;
    return 0;
}


void moveOfPlayer (board& gameBoard, player &currentPlayer)
{
    while ( true ) // loop of player's move
    {
        cout << endl;
        
        // displaying board
        gameBoard.display();
        
        // move procedures
        int rowCoordinate = 0;
        int columnCoordinate = 0;
        
        cout << endl << currentPlayer.getName() << " (" << currentPlayer.getSymbol() << ")" << endl;
        
        cout << "Choose row: ";
        cin >> rowCoordinate;
        rowCoordinate = rowCoordinate - 1; // array numeration starts from '0'
        
        cout << "Choose column: ";
        cin >> columnCoordinate;
        columnCoordinate = columnCoordinate - 1; // the same reason ^
        
        if ( rowCoordinate > (gameBoard.getRows()-1) || rowCoordinate < 0 || columnCoordinate > (gameBoard.getColumns()-1) || columnCoordinate < 0 )
        {
            cout << "Wrong input!" << endl;
            continue;
        }
        else if ( gameBoard.getSymbol(rowCoordinate,columnCoordinate) == '_' )
        {
            gameBoard.setSymbol(rowCoordinate,columnCoordinate,currentPlayer.getSymbol());
            break;
        }
        else
        {
            cout << "You can't put " << currentPlayer.getSymbol() << " in that spot!" << endl;
        }
    }
}