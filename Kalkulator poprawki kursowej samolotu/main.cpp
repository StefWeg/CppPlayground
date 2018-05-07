//
//  main.cpp
//  Kalkulator poprawki kursowej
//
//  Created by Stefan Węgrzyn on 31.07.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <math.h>

/*
 #include <ctime>
 #include <cstdlib>
*/

using namespace std;

///// GLOBAL DECLARATIONS ////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////

int main ()
{
    double NKDM = 0; // Nakazany kąt drogi magnetyczny
    double S = 0; // droga WPT --> KPT
    double Vr = 0; // prędkość rzeczywista
    double DN = 0; // kierunek wiatru nawigacyjnego
    double U = 0; // prędkość wiatru
    
    cout << "Please enter following parameters: " << endl;
    cout << "NKDM (Nakazany kąt drogi magnetyczny) [0-360 stopni]: ";
    cin >> NKDM;
    cout << "S (WPT --> KPT) [km]: ";
    cin >> S;
    cout << "Vr (Prędkość rzeczywista) [km/h]: ";
    cin >> Vr;
    cout << "DN (Kierunek wiatru nawigacyjnego) [0-360 stopni]: ";
    cin >> DN;
    cout << "U (Prędkość wiatru) [km/h]: ";
    cin >> U;
    
    
    double KW = 0; // kąt wiatru
    double KW_inRadians = 0; // kąt wiatru w radianach
    double cosinus_KW = 0; // cosinus kąta wiatru
    string windCharacter = " ";
    string adjustmentCharacter = " ";
    
    // obliczanie kąta wiatru
    KW = DN - NKDM;
    if ( KW > 180 )
    {
        KW = KW - 360;
    }
    else if ( KW < -180 )
    {
        KW = KW + 360;
    }
    
    // definiowanie charakteru wiatru względem NLD (Nakazanej linii drogi) oraz kierunku poprawki
    if ( KW == 0 )
    {
        windCharacter = "wiatr tylny";
        adjustmentCharacter = "";
    }
    else if ( KW == 180 || KW == -180 )
    {
        windCharacter = "wiatr czołowy";
        adjustmentCharacter = "";
    }
    else if ( KW < 180 && KW > 90 )
    {
        windCharacter = "wiatr lewostronny czołowo-boczny";
        adjustmentCharacter = "w lewo";
    }
    else if ( KW < 90 && KW > 0 )
    {
        windCharacter = "wiatr lewostronny tylno-boczny";
        adjustmentCharacter = "w lewo";
    }
    else if ( KW > -90 && KW < 0 )
    {
        windCharacter = "wiatr prawostronny tylno-boczny";
        adjustmentCharacter = "w prawo";
    }
    else if ( KW > -180 && KW < -90 )
    {
        windCharacter = "wiatr prawostronny czołowo-boczny";
        adjustmentCharacter = "w prawo";
    }
    else
    {
        cout << "Error in defining KW!";
        return 0;
    }
    
    // operacje na kącie wiatru potrzebne do dalszych obliczeń
    // nie przejmuje się, że KW jest ujemny bo cosinus jest funkcją parzystą
    
    KW_inRadians = (KW/180.0)*M_PI;
    
    cosinus_KW = cos ( KW_inRadians );
    
    
    double W = 0; // prędkość podróżna względem ziemi (GS - ground speed)
    double a = 0;
    double b = 0;
    double c = 0;
    double delta = 0; // potrzebna przy obliczaniu W
    double delta_sqrt = 0;
    double first_solution = 0;
    double second_solution = 0;
    
    // obliczanie W(GS) [twierdzenie cosinusów]
    a = 1;
    b = -2*U*cosinus_KW;
    c = U*U - Vr*Vr;
    delta = b*b - 4*a*c;
    delta_sqrt = sqrt (delta);
    first_solution = ((-b) - delta_sqrt)/2*a;
    second_solution = ((-b) + delta_sqrt)/2*a;
    
    if (first_solution > 0)
    {
        W = first_solution;
    }
    else if (second_solution > 0)
    {
        W = second_solution;
    }
    else
    {
        cout << "Error in computing W!";
        return 0;
    }
    
    
    double KZ = 0; // kąt znoszenia
    double KZ_inRadians = 0;
    double sinus_KZ = 0;
    
    // obliczanie KZ [twierdzenie sinusów]
    if ( KW == 0 || KW == 180 || KW == -180 )
    {
        KZ = 0;
    }
    else if ( KW < 0 )
    {
        KW_inRadians = KW_inRadians - 2*KW_inRadians; // zmieniam kąt wiatru na dodatni (na czas obliczeń)
        sinus_KZ = (U*sin(KW_inRadians))/Vr;
        KZ_inRadians = asin (sinus_KZ);
        KZ = (KZ_inRadians/M_PI)*180;
        KW_inRadians = KW_inRadians - 2*KW_inRadians; // ponowna zmiana kąta wiatru na ujemny
        KZ = KZ - 2*KZ; // zamiana kąta znoszenia na ujemny
    }
    else if ( KW > 0 )
    {
        sinus_KZ = (U*sin(KW_inRadians))/Vr;
        KZ_inRadians = asin (sinus_KZ);
        KZ = (KZ_inRadians/M_PI)*180;
    }
    else
    {
        cout << "Error in computing KZ!";
        return 0;
    }
    
    
    double KM = 0; // kurs magnetyczny (z poprawką na wiatr)
    
    // obliczanie KM
    KM = NKDM - KZ;
    
    if ( KZ < 0 )
    {
        KZ = KZ - 2*KZ; // zamiana kąta znoszenia na dodatni przed wyświetleniem wyników
    }
    
    
    double T = 0; // czas podróży do KPT
    
    //obliczanie T
    T = S/W;
    
    
    // Wyświetlanie wyników:
    
    cout << endl;
    cout << "Przy wietrze nawigacyjnym o kierunku " << DN << " stopni i prędkości " << U << " km/h," << endl;
    cout << "chcąc lecieć kursem magnetycznym " << NKDM << " stopni napotkasz " << windCharacter << "." << endl;
    cout << "By przemieszczać się tym kursem magnetycznym " << endl;
    cout << "z prędkością rzeczywistą " << Vr << " km/h do oddalonego o " << S << " km punktu trasy" << endl;
    cout << "należy dokonać poprawki o " << KZ << " stopni "  << adjustmentCharacter << endl;
    cout << "i lecieć kursem magnetycznym " << KM << " stopni." << endl;
    cout << "Wówczas prędkość samolotu względem ziemi będzie wynosiła " << W << " km/h," << endl;
    cout << "a podróż do punktu trasy będzie trwała " << T << " h.";
    
}

//////////////////////////////////////////////////////////////////////////////////////
