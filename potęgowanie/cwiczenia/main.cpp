//
//  main.cpp
//  cwiczenia
//
//  Created by Stefan Węgrzyn on 30.05.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

using namespace std;

int main ()
{
    double liczba = 0;
    int potega = 0;
    double wynik = 1;
    cout << "Enter x: ";
    cin >> liczba;
    cout << "Enter power: ";
    cin >> potega;
    for ( int i = 0; i < potega; i++)
    {
        wynik = wynik * liczba;
    }
    cout << "Number " << liczba << " raised to the power of " << potega << " ammounts to " << wynik << ".";
}
