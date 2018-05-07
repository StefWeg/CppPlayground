//
//  main.cpp
//  Display of 2-dimensional array addresses
//
//  Created by Stefan Węgrzyn on 16.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;

int main ()
{
    int rows = 4;
    int columns = 5;
    int table[rows][columns];
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout.width(15);
            cout << left << &table[i][j];
        }
        cout << endl;
    }
    
    return 0;
}
