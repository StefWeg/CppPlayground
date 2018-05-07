//
//  main.cpp
//  English numbers
//
//  Created by Stefan Węgrzyn on 21.06.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

using namespace std;

// deklaracje funkcji
string czytaczPakietow ( string pakiet );

int main ()
{
    
    // wprowadzanie liczby
    string number = "brak";
    
    cout << "Enter the number: ";
    cin >> number;
    
    
    // zabezpieczenie przed za dużą liczbą
    if ( number.length() > 12 )
    {
        cout << "Entered number is too big!";
        return 0;
    }
    
    
    // argumenty do pętli "for":
    string zbiorka = "";
    string doTrojki = "";
    
    // argumenty do zbierania trójek w warunku "if" w pętli "for":
    string jednosci = "";
    string tysiace = "";
    string miliony = "";
    string miliardy = "";
    
    for ( double i = (number.length() - 1); i >= 0; i--) // wybiera liczby od konca
        //(odejmuje 1 od length bo litery w stringu są numerowane od 0 w zwyż)
    {
        
        zbiorka = number[i]; // przetrzymuje kolejne liczby
        
        doTrojki = zbiorka + doTrojki; // dodaje kolejne liczby do przodu
        
        if ( doTrojki.length() == 3 ) // upakowywanie w pakiety (w momencie, gdy zebrala się trojka)
        {
            if ( jednosci.length() == 0 )
            {
                jednosci = doTrojki;
                doTrojki = "";
            }
            else if ( jednosci.length() == 3 && tysiace.length() == 0 )
            {
                tysiace = doTrojki;
                doTrojki = "";
            }
            else if ( jednosci.length() == 3 && tysiace.length() == 3 && miliony.length() == 0 )
            {
                miliony = doTrojki;
                doTrojki = "";
            }
            else
            {
                miliardy = doTrojki;
                doTrojki = "";
            }
        }
    }
    
    // ponieważ po pętli może pozostać niepełna trojka w "doTrojki",
    // więc trzeba resztę z "doTrojki" umieścić w odpowiednim pakiecie
    // wydaje mi się, że dobrym pomyslem jest wstawienie zera na poczatku - może się potem przydać!!!
    
    if ( doTrojki.length() == 1 )
    {
        if ( jednosci.length() == 0 )
        {
            jednosci = "00" + doTrojki;
            doTrojki = "";
        }
        else if ( jednosci.length() == 3 && tysiace.length() == 0 )
        {
            tysiace = "00" + doTrojki;
            doTrojki = "";
        }
        else if ( jednosci.length() == 3 && tysiace.length() == 3 && miliony.length() == 0 )
        {
            miliony = "00" + doTrojki;
            doTrojki = "";
        }
        else
        {
            miliardy = "00" + doTrojki;
            doTrojki = "";
        }
    }
    
    else if ( doTrojki.length() == 2 )
    {
        
        if ( jednosci.length() == 0 )
        {
            jednosci = "0" + doTrojki;
            doTrojki = "";
        }
        else if ( jednosci.length() == 3 && tysiace.length() == 0 )
        {
            tysiace = "0" + doTrojki;
            doTrojki = "";
        }
        else if ( jednosci.length() == 3 && tysiace.length() == 3 && miliony.length() == 0 )
        {
            miliony = "0" + doTrojki;
            doTrojki = "";
        }
        else
        {
            miliardy = "0" + doTrojki;
            doTrojki = "";
        }
    }
    
    // W TYM MIEJSCU MAM SKOŃCZONE PAKIETY
    
    cout << "Number's " << number << " name in English is: " << endl;
    
    if ( number == "0" )
    {
        cout << "zero"; // bo nie chce zeby czytalo zero jak jest na koncu liczby większej od 0
    }
    else if ( miliardy == "" && miliony == "" && tysiace == "" )
    {
        cout << czytaczPakietow(jednosci) << endl;
    }
    else if ( miliardy == "" && miliony == "" )
    {
        cout << czytaczPakietow(tysiace) << "thousand " << czytaczPakietow(jednosci) << endl;
    }
    else if ( miliardy == "" )
    {
        cout << czytaczPakietow(miliony) << "millions " << czytaczPakietow(tysiace) << "thousand " << czytaczPakietow(jednosci) << endl;
    }
    else
    {
        cout << czytaczPakietow(miliardy) << "billions " << czytaczPakietow(miliony) << "millions " << czytaczPakietow(tysiace) << "thousand " << czytaczPakietow(jednosci) << endl;
    }
    // KONIEC PROGRAMU !!!
    
}



// funkcja czytająca pakiety (zadeklarowana u góry)
string czytaczPakietow ( string pakiet )
{
    // ustalenie liczby setek
    string setki = "";
    setki = pakiet[0];
    if ( setki == "0" )
    {
        setki = "";
    }
    else if ( setki == "1" )
    {
        setki = "one hundred ";
    }
    else if ( setki == "2" )
    {
        setki = "two hundred ";
    }
    else if ( setki == "3" )
    {
        setki = "three hundred ";
    }
    else if ( setki == "4" )
    {
        setki = "four hundred ";
    }
    else if ( setki == "5" )
    {
        setki = "five hundred ";
    }
    else if ( setki == "6" )
    {
        setki = "six hundred ";
    }
    else if ( setki == "7" )
    {
        setki = "seven hundred ";
    }
    else if ( setki == "8" )
    {
        setki = "eight hundred ";
    }
    else
    {
        setki = "nine hundred ";
    }
    // koniec z setkami
    
    // jednostki muszę wprowadzić już teraz bo nastki będą figurować jako jednostki
    string jednostki = "";
    
    // ustalenie liczby dziesiątek
    string dziesiatki = "";
    dziesiatki = pakiet[1];
    if ( dziesiatki == "0" )
    {
        dziesiatki = "";
    }
    else if ( dziesiatki == "1" )
    {
        // UWAGA!!!
        string nastki = "";
        string uno = "";
        uno = pakiet[1];
        string duo = "";
        duo = pakiet[2];
        nastki = uno + duo;
        // nastki na piechotę
        if ( nastki == "10" )
        {
            jednostki = "ten ";
        }
        else if ( nastki == "11" )
        {
            jednostki = "eleven ";
        }
        else if ( nastki == "12" )
        {
            jednostki = "twelve ";
        }
        else if ( nastki == "13" )
        {
            jednostki = "thirteen ";
        }
        else if ( nastki == "14" )
        {
            jednostki = "fourteen ";
        }
        else if ( nastki == "15" )
        {
            jednostki = "fifteen ";
        }
        else if ( nastki == "16" )
        {
            jednostki = "sixteen ";
        }
        else if ( nastki == "17" )
        {
            jednostki = "seventeen ";
        }
        else if ( nastki == "18" )
        {
            jednostki = "eighteen ";
        }
        else
        {
            jednostki = "nineteen ";
        }
    }
    else if ( dziesiatki == "2" )
    {
        dziesiatki = "twenty ";
    }
    else if ( dziesiatki == "3" )
    {
        dziesiatki = "thirty ";
    }
    else if ( dziesiatki == "4" )
    {
        dziesiatki = "fourty ";
    }
    else if ( dziesiatki == "5" )
    {
        dziesiatki = "fifty ";
    }
    else if ( dziesiatki == "6" )
    {
        dziesiatki = "sixty ";
    }
    else if ( dziesiatki == "7" )
    {
        dziesiatki = "seventy ";
    }
    else if ( dziesiatki == "8" )
    {
        dziesiatki = "eighty ";
    }
    else
    {
        dziesiatki = "ninety ";
    }
    // koniec z dziesiatkami i nastkami
    
    // ustalanie liczby jednosci
    if ( dziesiatki != "1" ) // jezeli w miejscu liczby dziesiatek jest 1 to tam pozostanie
    {
        jednostki = pakiet[2]; // musi byc wewnatrz if, poniewaz inaczej nastki ^ by sie zmienialy na cyfre jednosi z pakietu
        
        if ( jednostki == "0" )
        {
            jednostki = "";
        }
        else if ( jednostki == "1" )
        {
            jednostki = "one ";
        }
        else if ( jednostki == "2" )
        {
            jednostki = "two ";
        }
        else if ( jednostki == "3" )
        {
            jednostki = "three ";
        }
        else if ( jednostki == "4" )
        {
            jednostki = "four ";
        }
        else if ( jednostki == "5" )
        {
            jednostki = "five ";
        }
        else if ( jednostki == "6" )
        {
            jednostki = "six ";
        }
        else if ( jednostki == "7" )
        {
            jednostki = "seven ";
        }
        else if ( jednostki == "8" )
        {
            jednostki = "eight ";
        }
        else
        {
            jednostki = "nine ";
        }
    }
    else
    {
        dziesiatki = "";
    }
    // koniec z jednostkami
    
    // TWORZENIE NAZWY PAKIETU
    string tresc = setki + dziesiatki + jednostki;
    return tresc;
}






