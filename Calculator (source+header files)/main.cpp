//
//  main.cpp
//  Calculator (source+header files)
//
//  Created by Stefan Węgrzyn on 29.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include "operations.h"

using namespace std;

int main ()
{
    double a,b;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << a << " + " << b << " = " << add(a, b) << endl;
    cout << a << " - " << b << " = " << subtract(a, b) << endl;
    cout << a << " * " << b << " = " << multiply(a, b) << endl;
    try {divide(a, b);} catch (string error) {cout << error << endl; return 0;}
    cout << a << " / " << b << " = " << divide(a, b) << endl;
    return 0;
}