//
//  main.cpp
//  slot machine game
//
//  Created by Stefan Węgrzyn on 28.06.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

#include <cstdlib>

#include <ctime>

using namespace std;


void giveTimeForSpinning ( int seed );

char chooseSymbol ( int seed );

bool winCheck ( char first_A, char first_B, char first_C, char second_A, char second_B, char second_C, char third_A, char third_B, char third_C );

void resultsDisplay ( char first_A, char first_B, char first_C, char second_A, char second_B, char second_C, char third_A, char third_B, char third_C );



int main ()
{
    srand( static_cast<int>( time(NULL) ) );
    
    char first_A = 0;
    char first_B = 0;
    char first_C = 0;
    char second_A = 0;
    char second_B = 0;
    char second_C = 0;
    char third_A = 0;
    char third_B = 0;
    char third_C = 0;
    
    // 1A 1B 1C
    // 2A 2B 2C
    // 3A 3B 3C
    
    while ( true )
    {
        int seed = 0;
        seed = rand();
        
        int round_number = 0;
        round_number++;
        
        first_A = chooseSymbol ( seed );
        seed = rand();
        first_B = chooseSymbol ( seed );
        seed = rand();
        first_C = chooseSymbol ( seed );
        seed = rand();
        second_A = chooseSymbol ( seed );
        seed = rand();
        second_B = chooseSymbol ( seed );
        seed = rand();
        second_C = chooseSymbol ( seed );
        seed = rand();
        third_A = chooseSymbol ( seed );
        seed = rand();
        third_B = chooseSymbol ( seed );
        seed = rand();
        third_C = chooseSymbol ( seed );
        
        
        cout << "Press enter to spin!" << endl;
        cin.get();
        cout << "Spinning..." << endl << endl;
        
        seed = rand();
        giveTimeForSpinning ( seed );
        cout << "|| " << first_A << " " << first_B << " " << first_C << " ||" << endl;
        seed = rand();
        giveTimeForSpinning ( seed );
        cout << "|| " << second_A << " " << second_B << " " << second_C << " ||" << endl;
        seed = rand();
        giveTimeForSpinning ( seed );
        cout << "|| " << third_A << " " << third_B << " " << third_C << " ||" << endl << endl;
        
        if ( winCheck ( first_A, first_B, first_C, second_A, second_B, second_C, third_A, third_B, third_C ) )
        {
            seed = rand();
            giveTimeForSpinning ( seed );
            
            resultsDisplay ( first_A, first_B, first_C, second_A, second_B, second_C, third_A, third_B, third_C );
            
            cout << "-----------" << endl << endl;
        }
        
    }
    
}



void giveTimeForSpinning ( int seed )
{
    srand( seed );
    
    while ( true )
    {
        int waitingForLessThan10 = 0;
        waitingForLessThan10 = rand ();
        if ( waitingForLessThan10 < 10 )
        {
            break;
        }
    }
}


char chooseSymbol ( int seed )
{
    enum { zero, one, two, three };
    
    int result = 0;
    
    result = ( seed % 4 );
    
    switch ( result )
    {
        case zero:
            return '+';
            break;
        case one:
            return '$';
            break;
        case two:
            return '#';
            break;
        case three:
            return '@';
            break;
            
        default:
            cout << "Error in 'chooseSymbol' function!" << endl;
            return ' ';
            break;
    }
}


bool winCheck ( char first_A, char first_B, char first_C, char second_A, char second_B, char second_C, char third_A, char third_B, char third_C )
{
    
    if ( first_A == first_B && first_B == first_C )
    {
        return true;
    }
    else if ( second_A == second_B && second_B == second_C )
    {
        return true;
    }
    else if ( third_A == third_B && third_B == third_C )
    {
        return true;
    }
    else if ( first_A == second_A && second_A == third_A )
    {
        return true;
    }
    else if ( first_B == second_B && second_B == third_B )
    {
        return true;
    }
    else if ( first_C == second_C && second_C == third_C )
    {
        return true;
    }
    else if ( first_A == second_B && second_B == third_C )
    {
        return true;
    }
    else if ( first_C == second_B && second_B == third_A )
    {
        return true;
    }
    else
    {
        return false;
    }
}


void resultsDisplay ( char first_A, char first_B, char first_C, char second_A, char second_B, char second_C, char third_A, char third_B, char third_C )
{
    int row_first = 0;
    int row_second = 0;
    int row_third = 0;
    int column_A = 0;
    int column_B = 0;
    int column_C = 0;
    int diagonally_first_A = 0;
    int diagonally_first_C = 0;
    
    if ( first_A == first_B && first_B == first_C )
    {
        row_first++;
    }
    if ( second_A == second_B && second_B == second_C )
    {
        row_second++;
    }
    if ( third_A == third_B && third_B == third_C )
    {
        row_third++;
    }
    if ( first_A == second_A && second_A == third_A )
    {
        column_A++;
    }
    if ( first_B == second_B && second_B == third_B )
    {
        column_B++;
    }
    if ( first_C == second_C && second_C == third_C )
    {
        column_C++;
    }
    if ( first_A == second_B && second_B == third_C )
    {
        diagonally_first_A++;
    }
    if ( first_C == second_B && second_B == third_A )
    {
        diagonally_first_C++;
    }
    
    
    if ( row_first == 1 )
    {
        first_A = ' ';
        first_B = ' ';
        first_C = ' ';
    }
    if ( row_second == 1 )
    {
        second_A = ' ';
        second_B = ' ';
        second_C = ' ';
    }
    if ( row_third == 1 )
    {
        third_A = ' ';
        third_B = ' ';
        third_C = ' ';
    }
    if ( column_A == 1 )
    {
        first_A = ' ';
        second_A = ' ';
        third_A = ' ';
    }
    if ( column_B == 1 )
    {
        first_B = ' ';
        second_B = ' ';
        third_B = ' ';
    }
    if ( column_C == 1 )
    {
        first_C = ' ';
        second_C = ' ';
        third_C = ' ';
    }
    if ( diagonally_first_A == 1 )
    {
        first_A = ' ';
        second_B = ' ';
        third_C = ' ';
    }
    if ( diagonally_first_C == 1 )
    {
        first_C = ' ';
        second_B = ' ';
        third_A = ' ';
    }
    
    int amountOfWins = 0;
    amountOfWins = row_first + row_second + row_third + column_A + column_B + column_C + diagonally_first_A + diagonally_first_C;
    if ( amountOfWins == 1 )
    {
        cout << "Single win!" << endl;
    }
    else if ( amountOfWins == 2 )
    {
        cout << "Double win!" << endl;
    }
    else if ( amountOfWins == 3 )
    {
        cout << "Triple win!" << endl;
    }
    else if ( amountOfWins == 4 )
    {
        cout << "Quadruple win!" << endl;
    }
    else if ( amountOfWins == 5 )
    {
        cout << "5x win!" << endl;
    }
    else if ( amountOfWins == 6 )
    {
        cout << "6x win!" << endl;
    }
    else if ( amountOfWins == 7 )
    {
        cout << "7x win!" << endl;
    }
    else
    {
        cout << "8x win!" << endl;
    }
    
    cout << "|| " << first_A << " " << first_B << " " << first_C << " ||" << endl;
    cout << "|| " << second_A << " " << second_B << " " << second_C << " ||" << endl;
    cout << "|| " << third_A << " " << third_B << " " << third_C << " ||" << endl;
}
