//
//  main.cpp
//  Element in sorted array (recursion)
//
//  Created by Stefan Węgrzyn on 21.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void create (int myArray[], int &length)
{
    srand(static_cast<int>(time(NULL)));
    
    for (int i = 0; i < length; i++)
    {
        myArray[i] = rand()%100;
        
        // disabling addition of two same numbers to the array
        for (int j = 0; j < i; j++)
        {
            if (myArray[i] == myArray[j])
            {
                i--;
                break;
            }
        }
        //
    }
}

void sort (int myArray[], int &length)
{
    int temporary = 0;
    
    for (int i = 0; i < length; i++)
    {
        for (int j = i; j < length; j++)
        {
            if (myArray[j] < myArray[i])
            {
                temporary = myArray[i];
                myArray[i] = myArray[j];
                myArray[j] = temporary;
            }
        }
    }
}

int find (int number, int* arrayStart, int indexOffset)
{
    if (number < arrayStart[indexOffset/2])
    {
        // when indexOffset == 1 and program gets here it means 'number' is not in the array
        if (indexOffset == 1)
        {
            string error = "no_such_number";
            throw error;
        }
        
        return find (number, arrayStart, (indexOffset/2));
    }
    else if (number > arrayStart[indexOffset/2])
    {
        // when indexOffset == 1 and program gets here it means 'number' is not in the array
        if (indexOffset == 1)
        {
            string error = "no_such_number";
            throw error;
        }
        
        arrayStart += indexOffset/2;
        return indexOffset/2 + find (number, arrayStart, indexOffset-(indexOffset/2));
    }
    else // number == arrayStart[indexOffset/2]
    {
        return indexOffset/2;
    }
}


int main ()
{
    // creation of array
    int length = 30;
    
    int* myArray = new int[length];
    
    create (myArray, length);
    sort (myArray, length);
    
    // display
    for (int i = 0; i < length; i++)
    {
        cout << myArray[i] << " ";
    }
    
    // prompting user for number to look for
    int number = 0;
    cout << endl << "Enter number you are looking for: ";
    cin >> number;
    
    // searching for number
    int indexOfNumber = -1;
    
    try
    {
        indexOfNumber = find (number, myArray, length-1);
    }
    catch (string error)
    {
        cout << error << endl;
    }
    
    cout << "Index: " << indexOfNumber << endl;
    
    //
    return 0;
}
