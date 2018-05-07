//
//  main.cpp
//  spaceShips 30x100
//
//  Created by Stefan Węgrzyn on 19.07.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

// this program requires 'window' 30x100 to work properly !!! ////////////////////////

#include <iostream>

#include <ctime>
#include <cstdlib>

using namespace std;

///// GLOBAL DECLARATIONS ////////////////////////////////////////////////////////////

char board[30][100];

struct spaceShip
{
    bool ifExist;
    int xCoordinate;
    int yCoordinate;
};

spaceShip ship[10];

//////////////////////////////////////////////////////////////////////////////////////

int main ()
{
    // establishing seed for random numbers
    srand( static_cast<int>( time(NULL) ) );
    
    // filling the board
    for ( int i = 0; i < 30; i++ )
    {
        for ( int j = 0; j < 100; j++ )
        {
            board[i][j] = '|';
        }
    }
    
    // finding positions for all (10) spaceships
    for ( int i = 0; i < 10; i++ )
    {
        ship[i].ifExist = true;
        
        // checking if x and y coordinates were used before
        int chosen_xCoordinate = 0;
        int chosen_yCoordinate = 0;
        bool chosen_Coordinates_WereAlreadyUsed = false;
        
        do
        {
            chosen_xCoordinate = rand()%30;
            chosen_yCoordinate = rand()%100;
            for ( int j = 0; j < 10; j++ )
            {
                if ( chosen_xCoordinate == ship[j].xCoordinate && chosen_yCoordinate == ship[j].yCoordinate )
                {
                    chosen_Coordinates_WereAlreadyUsed = true;
                    break;
                }
            }
        } while ( chosen_Coordinates_WereAlreadyUsed );
        
        ship[i].xCoordinate = chosen_xCoordinate;
        ship[i].yCoordinate = chosen_yCoordinate;
        
        board[chosen_xCoordinate][chosen_yCoordinate] = 'o';
    }
    
    
    //////// MAIN LOOP //////////////////////////////////////////////////////////////////////////////////////////////////////////
    while ( true )
    {
        // displaying board
        for ( int i = 0; i < 30; i++ )
        {
            for ( int j = 0; j < 100; j++ )
            {
                cout << board[i][j];
            }
            cout << endl;
        }
        
        
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        // finding new positions for all (10) spaceships
        for ( int i = 0; i < 10; i++ )
        {
            if ( ship[i].ifExist )
            {
                
                int xCoordinate = 0;
                int yCoordinate = 0;
                
                // erase ship from its current position
                board[ship[i].xCoordinate][ship[i].yCoordinate] = '|';
                
                // checking if x and y coordinates are occupied before changing coordinates of the ship (if yes, choose move again!)
                bool chosen_Coordinates_AreOccupied =false;
                
                do
                {
                    chosen_Coordinates_AreOccupied = false;
                    
                    xCoordinate = ship[i].xCoordinate;
                    yCoordinate = ship[i].yCoordinate;
                    
                    // which move will the ship make
                    enum move { up, upAndRight, right, downAndRight, down, downAndLeft, left, upAndLeft };
                    int chosenMove = rand()%8;
                    
                    // applying move
                    switch (chosenMove)
                    {
                        case up:
                            xCoordinate++;
                            break;
                            
                        case upAndRight:
                            xCoordinate++;
                            yCoordinate++;
                            break;
                            
                        case right:
                            yCoordinate++;
                            break;
                            
                        case downAndRight:
                            xCoordinate--;
                            yCoordinate++;
                            break;
                            
                        case down:
                            xCoordinate--;
                            break;
                            
                        case downAndLeft:
                            xCoordinate--;
                            yCoordinate--;
                            break;
                            
                        case left:
                            yCoordinate--;
                            break;
                            
                        case upAndLeft:
                            xCoordinate++;
                            yCoordinate--;
                            break;
                            
                            
                        default:
                            cout << "Error in applying move!" << endl;
                            break;
                    }
                    
                    // checking if new coordinates belong to the board
                    if ( xCoordinate < 0 || xCoordinate >= 30 || yCoordinate < 0 || yCoordinate >= 100 )
                    {
                        ship[i].ifExist = false;
                        ship[i].xCoordinate = -100;
                        ship[i].yCoordinate = -100;
                    }
                    
                    // checking if new coordinates are occupied by another ship (if yes, cause program to repat the loop)
                    else if ( board[xCoordinate][yCoordinate] != '|' )
                    {
                        chosen_Coordinates_AreOccupied = true;
                    }
                    // if coordinates belong to the board and are not occupied
                    else
                    {
                        ship[i].xCoordinate = xCoordinate;
                        ship[i].yCoordinate = yCoordinate;
                        
                        board[xCoordinate][yCoordinate] = 'o';
                    }
                    
                    
                } while ( chosen_Coordinates_AreOccupied );
                
            }
            
        }
        
        /*
         int*timeToWait = new int;
         int T = 1000;
         timeToWait = &T;
         wait(timeToWait);
         */
        
        
        /*
         // click enter to refresh board
         cin.get();
         */
        
        
        
        while (true)
        {
            int number = rand();
            
            if ( number > 0 && number < 100 )
            {
                break;
            }
        }
        
        
    }
    
    
}

//////////////////////////////////////////////////////////////////////////////////////
