//
//  main.cpp
//  Multiplication table (dynamically allocated two-dimensional array)
//
//  Created by Stefan Węgrzyn on 15.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;


int **createTable (int *num_rows, int *num_columns);

void displayTable (int *num_rows, int *num_columns, int **multiplicationTable);



int main ()
{
    // variables initialisation
    int *num_rows = new int;
    int *num_columns = new int;
    
    // prompting user for input
    cout << "Enter the number of rows: ";
    cin >> *num_rows;
    cout << "Enter the number of columns: ";
    cin >> *num_columns;
    
    // using functions
    int **multiplicationTable = createTable (num_rows, num_columns);
    displayTable (num_rows, num_columns, multiplicationTable);
    
    
    // deallocation of pointers
    for (int i = 0; i < *num_rows; i++)
    {
        delete[] *(multiplicationTable+i);  // delete[] multiplicationTable[i];
    }
    delete[] multiplicationTable;
    
    delete num_rows;
    delete num_columns;
}



int **createTable (int *num_rows, int *num_columns)
{
    // initialisation of pointer pointing to row-pointers pointing to values in each row of the table
    int **multiplicationTable = new int*[*num_rows];
    
    // making every row-pointer point to array of values (length of each array is equal to number of columns)
    for (int i = 0; i < *num_rows; i++)
    {
        *(multiplicationTable+i) = new int[*num_columns];  // multiplicationTable[i] = new int[*num_columns];
    }
    
    // assignment of proper values to elements of in created two-dimensional 'array'
    for (int i = 0; i < *num_rows; i++)
    {
        for (int j = 0; j < *num_columns; j++)
        {
            *(*(multiplicationTable+i)+j) = i * j;  // multiplicationTable[i][j] = i * j;
        }
    }
    
    return multiplicationTable;
}

void displayTable (int *num_rows, int *num_columns, int **multiplicationTable)
{
    // display of the table
    
    // checking max length of number in the table
    int *max_length = new int;
    *max_length = log10((*num_rows-1) * (*num_columns-1)) + 1;
    
    // drawing upper header
    cout.width(*max_length+2);
    cout << right << "|";
    for (int i = 0; i < *num_columns; i++)
    {
        cout.width(*max_length+2);
        cout << i;
    }
    cout << endl;
    
    // drawing lateral line under upper header
    for (int i = 0; i < *num_columns+1; i++)
    {
        for (int j = 0; j < *max_length+2; j++)
        {
            cout << "-";
        }
    }
    cout << endl;
    
    // drawing left header, vertical line and table itself
    for (int i = 0; i < *num_rows; i++)
    {
        cout.width(*max_length+1);
        cout << left << i << "|";
        
        for (int j = 0; j < *num_columns; j++)
        {
            cout.width(*max_length+2);
            cout << right << *(*(multiplicationTable+i)+j);  // cout << multiplicationTable[ i ][ j ] << " ";
        }
        cout << endl;
    }
    
    // deallocation of local pointers
    delete max_length;
}
