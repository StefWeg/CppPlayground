//
//  main.cpp
//  Paradoks urodzin
//
//  Created by Stefan Węgrzyn on 17.06.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

using namespace std;

int main ()
{
    double number_of_pupils = 0;
    cout << "Enter the number of pupils: ";
    cin >> number_of_pupils;
    
    double number_of_days_in_year = 365;
    
    double denominator = 1;
    for (int j = 0; j < number_of_pupils; j++)
    {
        denominator = denominator * number_of_days_in_year;
    }
    
    double numerator = 1;
    for (int i = 0; i < number_of_pupils; i++)
    {
        numerator = numerator * number_of_days_in_year;
        number_of_days_in_year--;
    }
    
    float probability_of_opposite_event;
    probability_of_opposite_event = numerator / denominator;
    
    float probability_of_event;
    probability_of_event = 1 - probability_of_opposite_event;
    
    cout << "Probability of an event in which two pupils in the class of " << number_of_pupils << " have birthday in ";
    cout << "the same day is equal to: " << probability_of_event << endl;
}