//
//  main.cpp
//  Address book
//
//  Created by Stefan Węgrzyn on 11.07.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

/*
#include <ctime>
#include <cstdlib>
*/

using namespace std;

///// GLOBAL DECLARATIONS ////////////////////////////////////////////////////////////

struct people
{
    bool ifExist;
    string name;
    string surname;
    string address;
    string phone_number;
};

people person[25];

people person_temporary[25];

void displayContacs ();

void putDataInAlphabeticalOrder ();

void addToTemporaryArray ( int iteratorOfOriginalArray );

void addContact ();

void removeContact ();

//////////////////////////////////////////////////////////////////////////////////////

int main ()
{
    
    while (true)
    {
        putDataInAlphabeticalOrder();
        
        cout << "MENU" << endl;
        cout << "1. Display contacts" << endl;
        cout << "2. Add contact" << endl;
        cout << "3. Remove contact" << endl;
        cout << "4. Quit address book" << endl;
        cout << "Choose option: ";
        
        int chosenOption = 0;
        cin >> chosenOption;
        
        if ( chosenOption == 1 )
        {
            displayContacs ();
            continue;
        }
        else if ( chosenOption == 2 )
        {
            addContact ();
            continue;
        }
        else if ( chosenOption == 3 )
        {
            removeContact ();
            continue;
        }
        
        else if ( chosenOption == 4 )
        {
            break;
        }
        else if ( chosenOption < 1 || chosenOption > 4 )
        {
            cout << "Wrong input!" << endl << endl;
            continue;
        }
    }
    
    cout << "... adress book closed ...";
}

//////////////////////////////////////////////////////////////////////////////////////

void displayContacs ()
{
    for ( int i = 0; i < 25; i ++ )
    {
        if ( person[i].ifExist )
        {
            cout << endl;
            cout << i+1 << "." << endl;
            cout << person[i].surname << ", " << person[i].name << endl;
            cout << "Adress: " << person[i].address << endl;
            cout << "Phone number: " << person[i].phone_number << endl;
        }
        else // because 'person' array is going to be filled from the biginning
        {
            break;
        }
    }
    
    cout << endl << "Press enter to go back to MENU..." << endl;
    cin.get();
    cin.get();
}

//////////////////////////////////////////////////////////////////////////////////////

void putDataInAlphabeticalOrder ()
{
    char alphabetOfCapitalLetters[26];
    alphabetOfCapitalLetters[0] = 'A';
    alphabetOfCapitalLetters[1] = 'B';
    alphabetOfCapitalLetters[2] = 'C';
    alphabetOfCapitalLetters[3] = 'D';
    alphabetOfCapitalLetters[4] = 'E';
    alphabetOfCapitalLetters[5] = 'F';
    alphabetOfCapitalLetters[6] = 'G';
    alphabetOfCapitalLetters[7] = 'H';
    alphabetOfCapitalLetters[8] = 'I';
    alphabetOfCapitalLetters[9] = 'J';
    alphabetOfCapitalLetters[10] = 'K';
    alphabetOfCapitalLetters[11] = 'L';
    alphabetOfCapitalLetters[12] = 'M';
    alphabetOfCapitalLetters[13] = 'N';
    alphabetOfCapitalLetters[14] = 'O';
    alphabetOfCapitalLetters[15] = 'P';
    alphabetOfCapitalLetters[16] = 'Q';
    alphabetOfCapitalLetters[17] = 'R';
    alphabetOfCapitalLetters[18] = 'S';
    alphabetOfCapitalLetters[19] = 'T';
    alphabetOfCapitalLetters[20] = 'U';
    alphabetOfCapitalLetters[21] = 'V';
    alphabetOfCapitalLetters[22] = 'W';
    alphabetOfCapitalLetters[23] = 'X';
    alphabetOfCapitalLetters[24] = 'Y';
    alphabetOfCapitalLetters[25] = 'Z';
    
    char alphabetOfLowercaseLetters[26];
    alphabetOfLowercaseLetters[0] = 'a';
    alphabetOfLowercaseLetters[1] = 'b';
    alphabetOfLowercaseLetters[2] = 'c';
    alphabetOfLowercaseLetters[3] = 'd';
    alphabetOfLowercaseLetters[4] = 'e';
    alphabetOfLowercaseLetters[5] = 'f';
    alphabetOfLowercaseLetters[6] = 'g';
    alphabetOfLowercaseLetters[7] = 'h';
    alphabetOfLowercaseLetters[8] = 'i';
    alphabetOfLowercaseLetters[9] = 'j';
    alphabetOfLowercaseLetters[10] = 'k';
    alphabetOfLowercaseLetters[11] = 'l';
    alphabetOfLowercaseLetters[12] = 'm';
    alphabetOfLowercaseLetters[13] = 'n';
    alphabetOfLowercaseLetters[14] = 'o';
    alphabetOfLowercaseLetters[15] = 'p';
    alphabetOfLowercaseLetters[16] = 'q';
    alphabetOfLowercaseLetters[17] = 'r';
    alphabetOfLowercaseLetters[18] = 's';
    alphabetOfLowercaseLetters[19] = 't';
    alphabetOfLowercaseLetters[20] = 'u';
    alphabetOfLowercaseLetters[21] = 'v';
    alphabetOfLowercaseLetters[22] = 'w';
    alphabetOfLowercaseLetters[23] = 'x';
    alphabetOfLowercaseLetters[24] = 'y';
    alphabetOfLowercaseLetters[25] = 'z';
    
    
    // sorting surnames taking two first characters into account
    for ( int i = 0; i < 26; i++ )
    {
        for ( int k = 0; k < 26; k++ )
        {
            for ( int j = 0; j < 25; j++ )
            {
                if ( person[j].surname[0] == alphabetOfCapitalLetters[i]
                    && person[j].surname[1] == alphabetOfLowercaseLetters[k] )
                {
                    addToTemporaryArray ( j );
                }
            }
        }
    }

    
    
    // put temporary data to original array
    for ( int i = 0; i < 25; i ++ )
    {
        person[i] = person_temporary[i];
    }
    
    // clear temporary data
    for ( int i = 0; i < 25; i ++ )
    {
        person_temporary[i].ifExist = false;
        person_temporary[i].name = " ";
        person_temporary[i].surname = " ";
        person_temporary[i].address = " ";
        person_temporary[i].phone_number = " ";
    }
}

//////////////////////////////////////////////////////////////////////////////////////

void addToTemporaryArray ( int iteratorOfOriginalArray )
{
    for ( int j = 0; j < 25; j ++ )
    {
        if ( !(person_temporary[j].ifExist) )
        {
            person_temporary[j].ifExist = true;
            
            person_temporary[j] = person[iteratorOfOriginalArray];
            
            return;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////

void addContact ()
{
    for ( int i = 0; i < 25; i ++ )
    {
        if ( !(person[i].ifExist) )
        {
            person[i].ifExist = true;
            
            cout << endl;
            cout << "Adding new contact..." << endl;
            cout << "Please enter name: ";
            cin.get();
            getline ( cin, person[i].name, '\n' );
            cout << "Please enter surname: ";
            getline ( cin, person[i].surname, '\n' );
            cout << "Please enter adress: ";
            getline ( cin, person[i].address, '\n' );
            cout << "Please enter phone number: ";
            getline ( cin, person[i].phone_number, '\n' );
            
            cout << "The contact was added to your adress book." << endl;
            cout << "Press enter to go back to MENU..." << endl;
            cin.get();
            
            return;
        }
    }
    
    // if the program gets here it means there is no space for adding new contact
    cout << "Memory is full! You cannot add a new contact." << endl;
    cout << "Press enter to go back to MENU..." << endl;
    cin.get();
    cin.get();
}

//////////////////////////////////////////////////////////////////////////////////////

void removeContact ()
{
    for ( int i = 0; i < 25; i ++ )
    {
        if ( person[i].ifExist )
        {
            cout << endl;
            cout << i+1 << "." << endl;
            cout << person[i].surname << ", " << person[i].name << endl;
            cout << "Adress: " << person[i].address << endl;
            cout << "Phone number: " << person[i].phone_number << endl;
        }
        else // because 'person' array is going to be filled from the biginning
        {
            break;
        }
    }
    
    cout << endl;
    cout << "Choose the number of the contact you want to remove: ";
    
    int numberOfContactToRemove;
    cin >> numberOfContactToRemove;
    
    if ( numberOfContactToRemove < 1 || numberOfContactToRemove > 25 )
    {
        cout << "There is no contact with such a number!" << endl;
        cout << "Press enter to return to MENU...";
        cin.get();
        cin.get();
        return;
    }
    
    for ( int i = (numberOfContactToRemove - 1); i < (25-1); i++ )
        // (numberOfContactToRemove - 1) because of the array values order
        // (25-1) because program cannot search for value of the array that does not exist --> [i+1]
    {
        person[i].ifExist = person[i+1].ifExist;
        person[i].name = person[i+1].name;
        person[i].surname = person[i+1].surname;
        person[i].address = person[i+1].address;
        person[i].phone_number = person[i+1].phone_number;
    }
    
    // when you remove some contact the last slot of the array always will remain empty
    person[25].ifExist = false;
    person[25].name = " ";
    person[25].surname = " ";
    person[25].address = " ";
    person[25].phone_number = " ";
    
    cout << "The contact was removed." << endl;
    cout << "Press enter to return to MENU..." << endl;
    cin.get();
    cin.get();
}

//////////////////////////////////////////////////////////////////////////////////////









