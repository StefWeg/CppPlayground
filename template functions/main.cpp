//
//  main.cpp
//  template functions
//
//  Created by Stefan Węgrzyn on 10.08.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

// ------------------------------------------------------------------------------------------------------------------------

template <typename insideType>
insideType adder (const vector<insideType>& insertedVector)
{
    insideType result = *insertedVector.begin();
    for (typename vector<insideType>::const_iterator itr = insertedVector.begin()+1, end = insertedVector.end();
         itr != end; ++itr)
    {
        result += *itr;
    }
    return result;
}

template <typename insideType>
bool search (const vector<insideType>& insertedVector, const insideType& value)
{
    for (typename vector<insideType>::const_iterator itr = insertedVector.begin(), end = insertedVector.end();
         itr != end; ++itr)
    {
        if (value == *itr) return true;
    }
    return false;
}

template <typename insideType>
void sort (vector<insideType>& insertedVector)
{
    int counter = 1;
    while (counter != 0) {
        counter = 0;
        for (typename vector<insideType>::iterator prev_itr = insertedVector.begin(), itr = insertedVector.begin()+1, end = insertedVector.end(); itr != end; ++prev_itr, ++itr)
        {
            if (*prev_itr > *itr) {
                insideType temporary = *prev_itr;
                *prev_itr = *itr;
                *itr = temporary;
                counter++;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------------

int main ()
{
    vector<int> vectorOfInt;
    vectorOfInt.push_back(400);
    vectorOfInt.push_back(300);
    vectorOfInt.push_back(550);
    vectorOfInt.push_back(250);
    vector<string> vectorOfString;
    vectorOfString.push_back("hello");
    vectorOfString.push_back("armagedon");
    vectorOfString.push_back("homosapiens");
    vectorOfString.push_back("balon");
    vectorOfString.push_back("armagedon");
    
    // adder function check -------------------------------------------------------------------
    
    for (vector<int>::iterator itr = vectorOfInt.begin(), end = vectorOfInt.end();
         itr != end; ++itr)
    {
        if (itr == vectorOfInt.begin()) cout << *itr;
        else cout << " + " << *itr;
    }
    int sumOfInt = adder(vectorOfInt); // needless to write adder<int>
    cout << " = " << sumOfInt << endl;
    
    for (vector<string>::iterator itr = vectorOfString.begin(), end = vectorOfString.end();
         itr != end; ++itr)
    {
        if (itr == vectorOfString.begin()) cout << *itr;
        else cout << " + " << *itr;
    }
    string sumOfString = adder<string>(vectorOfString);
    cout << " = " << sumOfString << endl;
    
    // search function check -------------------------------------------------------------------
    
    if (search(vectorOfInt,400)) cout << "Value found in vector!" << endl; // needless to write search<int>
    else cout << "Value not found in vector!" << endl;
    
    if (search<string>(vectorOfString,"elo")) cout << "Value found in vector!" << endl;
    else cout << "Value not found in vector!" << endl;
    
    // sort function check ---------------------------------------------------------------------
    
    sort(vectorOfInt);
    for (vector<int>::iterator itr = vectorOfInt.begin(), end = vectorOfInt.end();
         itr != end; ++itr)
    {
        cout << *itr << " ";
    }
    cout << endl;
    sort(vectorOfString);
    for (vector<string>::iterator itr = vectorOfString.begin(), end = vectorOfString.end();
         itr != end; ++itr)
    {
        cout << *itr << " ";
    }
    cout << endl;
    
    // -----------------------------------------------------------------------------------------
    
    return 0;
}
