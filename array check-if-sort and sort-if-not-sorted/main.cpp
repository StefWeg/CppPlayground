//
//  main.cpp
//  array check-if-sort and sort-if-not-sorted
//
//  Created by Stefan Węgrzyn on 07.07.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

#include <ctime>
#include <cstdlib>

using namespace std;


bool checkIfArrayIsSorted ( int array[], int size )
{
    for ( int i = 0; i < (size - 1); i++ )
        // (size - 1) ponieważ jeżeli przy indeksie przed ostatnim wszystko się zgadza, wtedy jest dobrze!
    {
        if ( !( array[i] <= array[i+1] ) )
        {
            return false;
        }
    }
    return true;
}


//////////////////////////////////////////////////////////////////////////////////////


int findTheSmallestAmongReminding ( int array [], int size, int currentIndex );
void swap ( int array[], int currentIndex, int indexOfSmallestAmongReminding );

void sort ( int array [], int size )
{
    for ( int i = 0; i < size; i++ )
    {
        int indexOfSmallestAmongReminding = findTheSmallestAmongReminding( array, size, i );
        swap ( array, i, indexOfSmallestAmongReminding );
    }
}


int findTheSmallestAmongReminding ( int array [], int size, int currentIndex )
{
    int index_of_smallest_value = currentIndex;
    for (int j = currentIndex + 1; j < size; j++)
    {
        if ( array[ j ] < array[ index_of_smallest_value ]  )
        {
            index_of_smallest_value = j;
        }
    }
    return index_of_smallest_value;
}


void swap (int array[], int currentIndex, int indexOfSmallestAmongReminding )
{
    int temporarilyStoredNumber = array[currentIndex];
    array[currentIndex] = array[indexOfSmallestAmongReminding];
    array[indexOfSmallestAmongReminding] = temporarilyStoredNumber;
}


//////////////////////////////////////////////////////////////////////////////////////


// small helper method to display the before and after arrays
void displayArray (int array[], int size)
{
    cout << "{";
    for ( int i = 0; i < size; i++ )
    {
        // you'll see this pattern a lot for nicely formatting
        // lists--check if we're past the first element, and
        // if so, append a comma
        if ( i != 0 )
        {
            cout << ", ";
        }
        cout << array[ i ];
    }
    cout << "}";
}


//////////////////////////////////////////////////////////////////////////////////////


int main ()
{
    int sizeOfArray = 5;
    int array[ sizeOfArray ];
    srand( static_cast<int>( time( NULL ) ) );
    
    for ( int i = 0; i < sizeOfArray; i++ )
    {
        // keep the numbers small so they're easy to read
        array[ i ] = rand() % 100;
    }
    
    cout << "Original array: ";
    displayArray( array, sizeOfArray );
    cout << endl;
    
    if ( checkIfArrayIsSorted( array, sizeOfArray ) )
    {
        cout << "The original array is sorted!";
    }
    else
    {
        sort ( array, sizeOfArray );
        
        cout << "The original array was not sorted." << endl;
        cout << "Now it is sorted and looks like this: " << endl;
        displayArray( array, sizeOfArray );
    }
}

//////////////////////////////////////////////////////////////////////////////////////




