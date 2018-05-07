//
//  main.cpp
//  Highscores (binary file IO)
//
//  Created by Stefan Węgrzyn on 08.08.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct score
{
    string player;
    int value;
};


int main ()
{
    vector <score> highscores(0);
    string option = "", score_value = "";
    string filePath = "/filepath/highscores.bin";
    
    // loading highscores from the binary file into vector
    fstream dataFile (filePath, ios::binary | ios::in);
    if (! dataFile.is_open()) {cout << "Could not open the file!" << endl; return 1;}
    dataFile.seekg(0, ios::beg); // setting get position for beginning of the file
    int i = 0;
    while (true)
    {
        int readValue;
        if (! dataFile.read (reinterpret_cast<char*>(&readValue), sizeof(readValue))) {
            if (dataFile.eof()) break; // end of file
            cout << "Reading error!" << endl;
            return 1;
        }
        long int stringLength;
        if (! dataFile.read (reinterpret_cast<char*>(&stringLength), sizeof(stringLength))) {
            cout << "Reading error!" << endl;
            return 1;
        }
        if (stringLength > 1000) {cout << "Tried to allocate to much memory!" << endl; return 1;}
        char* readString = new char[stringLength];
        if (! dataFile.read (readString, stringLength+1)) { // +1 to read '\0' symbol from the file
            cout << "Reading error!" << endl;
            return 1;
        }
        string string(readString);
        score* newScore = new score;
        newScore->player = string;
        newScore->value = readValue;
        highscores.push_back(*newScore);
        ++i;
    }
    dataFile.close();
    
    // main program loop
    while (option != "4")
    {
        cout << "MENU:" << endl;
        cout << "1. Show highscores" << endl;
        cout << "2. Add score" << endl;
        cout << "3. Clear highscores" << endl;
        cout << "4. Leave program" << endl;
        cout << "Choose an option: ";
        getline (cin, option, '\n');
        
        if (option == "1")
        {
            cout << "Highscores:" << endl;
            
            // reading from vector
            /* for (int i = 0; i < highscores.size(); i++)
            {
                cout << i+1 << ". " << highscores[i].player << ": " << highscores[i].value << endl;
            } */
            
            // reading from binary file
            fstream dataFile (filePath, ios::binary | ios::in);
            if (! dataFile.is_open()) {cout << "Could not open the file!" << endl; return 1;}
            dataFile.seekg(0, ios::beg); // setting get position for beginning of the file
            for (int i = 0; i < highscores.size(); i++)
            {
                int valueToDisplay;
                if (! dataFile.read (reinterpret_cast<char*>(&valueToDisplay), sizeof(valueToDisplay))) {
                    cout << "Reading from file error!" << endl;
                    return 1;
                }
                long int stringLength;
                if (! dataFile.read (reinterpret_cast<char*>(&stringLength), sizeof(stringLength))) {
                    cout << "Reading from file error!" << endl;
                    return 1;
                }
                if (stringLength > 1000) {cout << "Tried to allocate to much memory!" << endl; return 1;}
                char* stringToDisplay = new char[stringLength];
                if (! dataFile.read (stringToDisplay, stringLength+1)) { // +1 to read '\0' symbol from the file
                    cout << "Reading from file error!" << endl;
                    return 1;
                }
                cout << i+1 << ". " << stringToDisplay << ": " << valueToDisplay << endl;
            }
            dataFile.close();
            cout << endl;
        }
        else if (option == "2")
        {
            score new_score;
            cout << "Enter the name o the player: ";
            getline (cin, new_score.player, '\n');
            cout << "Enter the score: ";
            getline (cin, score_value, '\n');
            try {new_score.value = stoi(score_value);}
            catch (...) {cout << "Wrong input!" << endl << endl; continue;}
            
            if (highscores.size() == 0)
            {
                highscores.push_back(new_score);
                cout << endl;
            }
            else
            {
                vector<score>::iterator itr;
                for (itr = highscores.begin(); itr != highscores.end(); ++itr)
                {
                    if (new_score.value > (*itr).value)
                    {
                        highscores.insert(itr,new_score);
                        cout << endl;
                        break;
                    }
                }
                if (itr == highscores.end())
                {
                    highscores.emplace(itr, new_score);
                    cout << endl;
                }
            }
            // writing to binary file
            fstream dataFile (filePath, ios::binary | ios::trunc | ios::out);
            if (! dataFile.is_open()) {cout << "Could not open the file!" << endl; return 1;}
            dataFile.seekp(0, ios::beg); // setting get position for beginning of the file
            for (int i = 0; i < highscores.size(); i++)
            {
                dataFile.write (reinterpret_cast<char*>(&highscores[i].value), sizeof(highscores[i].value));
                long int stringLength = highscores[i].player.length();
                dataFile.write (reinterpret_cast<char*>(&stringLength), sizeof(stringLength));
                dataFile.write (highscores[i].player.c_str(), stringLength+1); // +1 to write also '\0' symbol to the file
            }
            dataFile.close();
        }
        else if (option == "3")
        {
            fstream dataFile (filePath, ios::binary | ios::trunc | ios::out);
            dataFile.close();
            highscores.clear();
            cout << "Highscores cleared!" << endl << endl;
        }
        else if (option == "4")
        {
            highscores.clear();
            break;
        }
        else cout << "Wront input!" << endl << endl;
    }
    return 0;
}
