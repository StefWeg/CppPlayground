//
//  main.cpp
//  Compare Order of Memory Addresses
//
//  Created by Stefan Węgrzyn on 30.07.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

#include <ctime>
#include <cstdlib>

using namespace std;

///// GLOBAL DECLARATIONS ////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////

int main ()
{
    int first_number = 1;
    int second_number = 2;
    int third_number = 3;
    int fourth_number = 4;
    
    cout << &first_number << endl;
    cout << &second_number << endl;
    cout << &third_number << endl;
    cout << &fourth_number << endl;
    
    int *addressOrder[4];
    addressOrder[0] = &first_number;
    addressOrder[1] = &second_number;
    addressOrder[2] = &third_number;
    addressOrder[3] = &fourth_number;
    
    for ( int k = 0; k < 4; k++ )
    {
        int *smallest = addressOrder[k];
        
        for ( int j = k+1; j < 4; j++ )
        {
            if ( addressOrder[j] < smallest )
            {
                smallest = addressOrder[j];
                addressOrder[j] = addressOrder[k];
                addressOrder[k] = smallest;
            }
        }
    }
    
    for ( int i = 0; i < 4; i++ )
    {
        cout << *addressOrder[i] << " ";
    }
    
    
}

//////////////////////////////////////////////////////////////////////////////////////

