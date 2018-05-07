//
//  main.cpp
//  array highest, smallest and average
//
//  Created by Stefan Węgrzyn on 06.07.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

#include <ctime>
#include <cstdlib>

using namespace std;



int findTheIndexOFSmallestInArray (int array[], int size)
{
    int index_of_smallest_value = 0;
    for (int i = 1; i < size; i++)
    {
        if ( array[ i ] < array[ index_of_smallest_value ]  )
        {
            index_of_smallest_value = i;
        }
    }
    return index_of_smallest_value;
}

int findTheIndexOFBiggestInArray (int array[], int size)
{
    int index_of_smallest_value = 0;
    for (int i = 1; i < size; i++)
    {
        if ( array[ i ] > array[ index_of_smallest_value ]  )
        {
            index_of_smallest_value = i;
        }
    }
    return index_of_smallest_value;
}

double findAverageOfArray (int array[], int size)
{
    double sumOfArray = 0;
    for ( int i = 0; i < size; i++ )
    {
        sumOfArray = sumOfArray + array[ i ];
    }
    return sumOfArray / size;
}



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





int main ()
{
    int sizeOfArray = 50;
    int array[ sizeOfArray ];
    srand( static_cast<int>( time( NULL ) ) );
    
    for ( int i = 0; i < sizeOfArray; i++ )
    {
        // keep the numbers small so they're easy to read
        array[ i ] = rand() % 100;
    }
    
    int smallest = 0;
    smallest = array [ findTheIndexOFSmallestInArray (array, sizeOfArray) ];
    
    int biggest = 0;
    biggest = array [ findTheIndexOFBiggestInArray (array, sizeOfArray) ];
    
    double average = 0;
    average = findAverageOfArray ( array, sizeOfArray );
    
    
    
    cout << "The smallest: " << smallest << endl;
    cout << "The highest: " << biggest << endl;
    cout << "The average: " << average << endl;
    cout << "Whole array: ";
    displayArray( array, sizeOfArray );
}

