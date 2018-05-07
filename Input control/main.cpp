//
//  main.cpp
//  Testy
//
//  Created by Stefan Węgrzyn on 09.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

using namespace std;

int main ()
{
    string input = "";
    
    cout << "Please enter your number: ";
    getline(cin, input, '\n');  // getline writes input into string
    
    short int number = 0;   // using short int to make out_of_range exception more plausible
    
    try     // checks if function inside (in this case stoi) throws an exception
            // information about exceptions thrown by functions can be found in documentation
    {
        number = stoi (input);
        cout << "Number your entered is: " << number << endl;
    }
    catch (invalid_argument error)  // handles invalid_argument exception
    {
        cout << "This is not a number, dummy!" << endl;
        cout << error.what() << endl;
    }
    catch (out_of_range error)  // handles out_of_range exception
    {
        cout << "The number you entered is too big for int, dummy!" << endl;
        cout << error.what() << endl;
    }
    
    return 0;
}
