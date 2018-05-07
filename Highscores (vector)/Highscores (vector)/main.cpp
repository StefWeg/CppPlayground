//
//  main.cpp
//  Highscores (vector)
//
//  Created by Stefan Węgrzyn on 26.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <vector>

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
    
    while (option != "3")
    {
        cout << "MENU:" << endl;
        cout << "1. Show highscores" << endl;
        cout << "2. Add score" << endl;
        cout << "3. Leave program" << endl;
        cout << "Choose an option: ";
        getline (cin, option, '\n');
        
        if (option == "1")
        {
            cout << "Highscores:" << endl;
            for (int i = 0; i < highscores.size(); i++)
            {
                cout << i+1 << ". " << highscores[i].player << ": " << highscores[i].value << endl;
            }
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
        }
        else if (option == "3")
        {
            highscores.clear();
            break;
        }
        else cout << "Wront input!" << endl << endl;
    }
    return 0;
}