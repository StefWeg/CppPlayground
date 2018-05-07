//
//  main.cpp
//  3-dimensional multiplication table (dynamically allocated memory)
//
//  Created by Stefan Węgrzyn on 16.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;

// structure initialisation
struct tableParameters
{
    int length;
    int width;
    int heigth;
    int level;
};

// function declarations
int ***createTable (tableParameters *table);
void displayTable (tableParameters *table, int ***multiplicationTable);



int main ()
{
    tableParameters *table = new tableParameters;
    
    // prompting user for input
    cout << "Enter length: ";
    cin >> (*table).length;
    cout << "Enter width: ";
    cin >> (*table).width;
    cout << "Enter height: ";
    cin >> (*table).heigth;
    
    // creation of multiplication table
    int ***multiplicationTable = createTable (table);
    
    // display of multiplication table
    cout << "Your 3-dimensional multiplication table is created!" << endl;
    cout << "Enter level to display: ";
    cin >> (*table).level;
    displayTable (table, multiplicationTable);
    
    
    // deallocation of pointers
    delete table;
    
    for (int i = 0; i < (*table).heigth; i++)
    {
        for (int j = 0; j < (*table).length; j++)
        {
            delete[] *(*(multiplicationTable+i)+j); // deallocation of arrays of values (width)
        }
    }
    
    for (int i = 0; i < (*table).heigth; i++)
    {
        delete[] *(multiplicationTable+i); // deallocation of length-pointers
    }
    
    delete[] multiplicationTable; // deallocation of heigth-pointers
    
    // end of program
    return 0;
}



int ***createTable (tableParameters *table)
{
    // initialisation of pointer pointing to array of heigth-pointers pointing to array of length-pointers
    int ***multiplicationTable = new int**[(*table).heigth];
    
    // making every height-pointer point to array of length-pointers
    for (int i = 0; i < (*table).heigth; i++)
    {
        *(multiplicationTable+i) = new int*[(*table).length];
    }
    
    // making every length-pointer point to array of values (width)
    for (int i = 0; i < (*table).heigth; i++)
    {
        for (int j = 0; j < (*table).length; j++)
        {
            *(*(multiplicationTable+i)+j) = new int[(*table).width];
        }
    }
    
    // assignment of proper values to elements of created 3-dimensional 'array'
    for (int i = 0; i < (*table).heigth; i++)
    {
        for (int j = 0; j < (*table).length; j++)
        {
            for (int k = 0; k < (*table).width; k++)
            {
                *(*(*(multiplicationTable+i)+j)+k) = i * j * k;
                // multiplicationTable[i][j][k] = i*j*k;
                // *(*(multiplicationTable+i)+j)[k] = i*j*k;
            }
        }
    }
    
    // return of the ready 3-dimensional multiplication table
    return multiplicationTable;
}


void displayTable (tableParameters *table, int ***multiplicationTable)
{
    // display of the chosen level of the table
    
    // checking max length of number in the table
    int *max_length = new int;
    if (*(*(*(multiplicationTable+(*table).level)+(*table).length-1)+(*table).width-1) == 0)
    {
        // elimination of log10(0) problem
        *max_length = 1;
    }
    else
    {
        *max_length = log10(*(*(*(multiplicationTable+(*table).level)+(*table).length-1)+(*table).width-1)) + 1;
    }
    
    // drawing upper header
    cout << "x" << (*table).level;
    cout.width(*max_length);
    cout << right << "|";
    for (int i = 0; i < (*table).width; i++)
    {
        cout.width(*max_length+2);
        cout << i;
    }
    cout << endl;
    
    // drawing lateral line under upper header
    for (int i = 0; i < (*table).width+1; i++)
    {
        for (int j = 0; j < *max_length+2; j++)
        {
            cout << "-";
        }
    }
    cout << endl;
    
    // drawing left header, vertical line and level of the table itself
    for (int j = 0; j < (*table).length; j++)
    {
        cout.width(*max_length+1);
        cout << left << j << "|";
        
        for (int k = 0; k < (*table).width; k++)
        {
            cout.width(*max_length+2);
            cout << right << *(*(*(multiplicationTable + (*table).level)+j)+k);
        }
        cout << endl;
    }
    
    // deallocation of local pointers
    delete max_length;
}
