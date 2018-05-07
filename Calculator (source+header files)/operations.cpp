//
//  operations.cpp
//  Calculator (source+header files)
//
//  Created by Stefan Węgrzyn on 29.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <string>
// #include "operations.h"

using namespace std;

double add (const double a, const double b)
{
    return a + b;
}
double subtract (const double a, const double b)
{
    return a - b;
}
double multiply (const double a, const double b)
{
    return a * b;
}
double divide (const double a, const double b)
{
    if (b != 0) return a / b;
    else {string error = "divisor equal 0!"; throw error;}
}