//
//  main.cpp
//  Contact book (STL map)
//
//  Created by Stefan Węgrzyn on 25.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <map>

using namespace std;

struct contactData
{
    string phone_number;
    string email;
};

void display (const map <string, contactData> &contactBook);
void displayReversed (const map <string, contactData> &contactBook);
bool checkIfContactExists (const map <string, contactData> &contactBook, const string &name);
void findNumberAndEmailByName (map <string, contactData> &contactBook);
void findNameByNumberOrEmail (const map <string, contactData> &contactBook);
void addContact (map <string, contactData> &contactBook);
void contactEditor (map <string, contactData> &contactBook);
void deleteContact (map <string, contactData> &contactBook);


int main ()
{
    map <string, contactData> contactBook;
    string option = "";
    int indicator = 0;
    
    while (indicator != 8)
    {
        cout << "CONTACT BOOK:" << endl;
        cout << "1. Print contacts in alphabetical order" << endl;
        cout << "2. Print contacts in counter alphabetical order" << endl;
        cout << "3. Find phone number and email by name" << endl;
        cout << "4. Find name by phone number or email" << endl;
        cout << "5. Add new contact" << endl;
        cout << "6. Edit existing contact" << endl;
        cout << "7. Remove contact" << endl;
        cout << "8. Exit contact book" << endl;
        cout << "Choose an option: ";
        
        getline(cin, option, '\n');
        try {indicator = stoi (option);}
        catch (...) {cout << "Wrong input!" << endl; continue;}
        
        switch (indicator)
        {
            case 1:
                display(contactBook);
                break;
            case 2:
                displayReversed(contactBook);
                break;
            case 3:
                findNumberAndEmailByName(contactBook);
                break;
            case 4:
                findNameByNumberOrEmail(contactBook);
                break;
            case 5:
                addContact(contactBook);
                break;
            case 6:
                contactEditor(contactBook);
                break;
            case 7:
                deleteContact(contactBook);
                break;
            case 8:
                contactBook.clear();
                break;
            default:
                cout << "There is not such option!" << endl << endl;
                break;
        }
    }
    
    return 0;
}



void display (const map <string, contactData> &contactBook)
{
    cout << "--------------------" << endl << "Contacts: " << endl;
    for (map <string, contactData> :: const_iterator itr = contactBook.begin(), end = contactBook.end();
         itr != end; ++itr)
    {
        cout << itr->first << ": " << (itr->second).phone_number << ", " << (itr->second).email << endl;
    }
    cout << "--------------------" << endl << endl;
}

void displayReversed (const map <string, contactData> &contactBook)
{
    cout << "--------------------" << endl << "Contacts: " << endl;
    for (map <string, contactData> :: const_reverse_iterator itr = contactBook.rbegin(), end = contactBook.rend();
         itr != end; ++itr)
    {
        cout << itr->first << ": " << (itr->second).phone_number << ", " << (itr->second).email << endl;
    }
    cout << "--------------------" << endl << endl;
}

bool checkIfContactExists (const map <string, contactData> &contactBook, const string &name)
{
    map <string, contactData> :: const_iterator itr = contactBook.find(name);
    if (itr != contactBook.end()) return true;
    else return false;
}

void findNumberAndEmailByName (map <string, contactData> &contactBook)
{
    string name = "";
    cout << "Enter the name of the person: ";
    getline(cin, name, '\n');
    if (checkIfContactExists(contactBook, name))
    {
        if ((contactBook[name]).phone_number != "no number")
        {cout << "phone number: " << (contactBook[name]).phone_number << endl;}
        else cout << "phone number unknown" << endl;
        if ((contactBook[name]).email != "no email")
        {cout << "email: " << (contactBook[name]).email << endl << endl;}
        else cout << "email unknown" << endl << endl;
    }
    else cout << "There is no person with such a name in contact book!" << endl << endl;
}

void findNameByNumberOrEmail (const map <string, contactData> &contactBook)
{
    string input = "";
    cout << "Enter phone number or email of the person: ";
    getline(cin, input, '\n');
    map <string, contactData> :: const_iterator itr, end = contactBook.end();
    for (itr = contactBook.begin(); itr != end; ++itr)
    {
        if (input == (itr->second).phone_number)
        {
            cout << input << " belongs to: " << itr->first << endl << endl;
            break;
        }
        else if (input == (itr->second).email)
        {
            cout << input << " belongs to: " << itr->first << endl << endl;
            break;
        }
    }
    if (itr == end)
    {
        cout << "There is no person with such a phone number or email in contact book!" << endl << endl;
    }
}

void addContact (map <string, contactData> &contactBook)
{
    string name = "";
    string phone_number = "";
    string email = "";
    cout << "Enter name of the person: ";
    getline(cin, name, '\n');
    if (checkIfContactExists(contactBook, name))
    {
        cout << "Person with such a name already exists in contactbook!" << endl << endl;
        return;
    }
    cout << "Enter person's phone number: ";
    getline(cin, phone_number, '\n');
    (contactBook[name]).phone_number = phone_number;
    cout << "Enter person's email: ";
    getline(cin, email, '\n');
    (contactBook[name]).email = email;
    cout << "Contact successfully added!" << endl << endl;
}

void contactEditor (map <string, contactData> &contactBook)
{
    string input = "", name = "", number = "", email = "";
    int indicator = 0;
    map <string, contactData> :: iterator itr = contactBook.begin();
    
    while (indicator != 5)
    {
        cout << endl;
        cout << "Contact editor: " << endl;
        cout << "1. Add/update contact number" << endl;
        cout << "2. Remove contact number" << endl;
        cout << "3. Add/update contact email" << endl;
        cout << "4. Remove contact email" << endl;
        cout << "5. Go back to contact book" << endl;
        cout << "Choose an option: ";
        
        getline(cin, input, '\n');
        try {indicator = stoi (input);}
        catch (...) {cout << "Wrong input!" << endl; continue;}
        
        switch (indicator)
        {
            case 1:
                cout << "Enter name of the person: ";
                getline(cin, name, '\n');
                itr = contactBook.find(name);
                if (itr != contactBook.end())
                {
                    if ((contactBook[name]).phone_number == "no number")
                    {
                        cout << "Enter number: ";
                        getline(cin, number, '\n');
                        (contactBook[name]).phone_number = number;
                        cout << "Number successfully added to contact!" << endl;
                    }
                    else
                    {
                        cout << "There is already a number associated with this name in contact book!" << endl;
                        cout << "Do you want to replace '" << (contactBook[name]).phone_number << "' with new number?" << endl;
                        cout << "1. Yes" << endl;
                        cout << "2. No" << endl;
                        cout << "Choose an option: ";
                        getline(cin, input, '\n');
                        try {indicator = stoi (input);}
                        catch (...) {cout << "Wrong input!" << endl; continue;}
                        switch (indicator)
                        {
                            case 1:
                                cout << "Enter number: ";
                                getline(cin, number, '\n');
                                (contactBook[name]).phone_number = number;
                                cout << "Number successfully added to contact!" << endl;
                                break;
                            case 2:
                                cout << "Original number preserved!" << endl;
                                break;
                            default:
                                cout << "There is not such option!" << endl;
                                break;
                        }
                    }
                }
                else cout << "There is no person with such a name in contact book!" << endl;
                break;
            case 2:
                cout << "Enter name of the person: ";
                getline(cin, name, '\n');
                itr = contactBook.find(name);
                if (itr != contactBook.end())
                {
                    if ((contactBook[name]).phone_number != "no number")
                    {
                        (contactBook[name]).phone_number = "no number";
                        cout << "Number successfully deleted from contact!" << endl;
                    }
                    else
                    {
                        cout << "There is no phone number associated with this name in contact book!" << endl;
                    }
                }
                else cout << "There is no person with such a name in contact book!" << endl;
                break;
            case 3:
                cout << "Enter name of the person: ";
                getline(cin, name, '\n');
                itr = contactBook.find(name);
                if (itr != contactBook.end())
                {
                    if ((contactBook[name]).email == "no email")
                    {
                        cout << "Enter email: ";
                        getline(cin, email, '\n');
                        (contactBook[name]).email = email;
                        cout << "Email successfully added to contact!" << endl;
                    }
                    else
                    {
                        cout << "There is already an email associated with this name in contact book!" << endl;
                        cout << "Do you want to replace '" << (contactBook[name]).email << "' with new email?" << endl;
                        cout << "1. Yes" << endl;
                        cout << "2. No" << endl;
                        cout << "Choose an option: ";
                        getline(cin, input, '\n');
                        try {indicator = stoi (input);}
                        catch (...) {cout << "Wrong input!" << endl; continue;}
                        switch (indicator)
                        {
                            case 1:
                                cout << "Enter email: ";
                                getline(cin, email, '\n');
                                (contactBook[name]).email = email;
                                cout << "Email successfully added to contact!" << endl;
                                break;
                            case 2:
                                cout << "Original email preserved!" << endl;
                                break;
                            default:
                                cout << "There is not such option!" << endl;
                                break;
                        }
                    }
                }
                else cout << "There is no person with such a name in contact book!" << endl;
                break;
            case 4:
                cout << "Enter name of the person: ";
                getline(cin, name, '\n');
                itr = contactBook.find(name);
                if (itr != contactBook.end())
                {
                    if ((contactBook[name]).email != "no email")
                    {
                        (contactBook[name]).email = "no email";
                        cout << "Email successfully deleted from contact!" << endl;
                    }
                    else
                    {
                        cout << "There is no email associated with this name in contact book!" << endl;
                    }
                }
                else cout << "There is no person with such a name in contact book!" << endl;
                break;
            case 5:
                cout << endl;
                return;
                break;
            default:
                cout << "There is not such option!" << endl;
                break;
        }
    }
}

void deleteContact (map <string, contactData> &contactBook)
{
    string name = "";
    cout << "Enter the name of person to delete: ";
    getline(cin, name, '\n');
    if (checkIfContactExists(contactBook, name))
    {
        contactBook.erase(name);
        cout << "Contact successfully deleted!" << endl << endl;
    }
    else cout << "There is no person with such a name in contact book!" << endl << endl;
}