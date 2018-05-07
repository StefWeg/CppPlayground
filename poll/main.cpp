//
//  main.cpp
//  cwieczenia
//
//  Created by Stefan Węgrzyn on 04.06.2015.
//  Copyright (c) 2015 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

using namespace std;

int main ()
{
    cout << "What's the subject of the poll?" << endl;
    string question;
    getline (cin, question, '\n');
    cout << "Enter first possible answer: " << endl;
    string first_answer;
    getline (cin, first_answer, '\n');
    cout << "Enter second possible answer: " << endl;
    string second_answer;
    getline (cin, second_answer, '\n');
    cout << "Enter third possible answer: " << endl;
    string third_answer;
    getline (cin, third_answer, '\n');
    cout << "Poll is ready to be conducted. Let's begin!" << endl;
    int voter_number = 0;
    int vote;
    double first_option_votes = 0;
    double second_option_votes = 0;
    double third_option_votes = 0;
    
    do
    {
        cout << endl;
        voter_number++;
        cout << "Hello you are " << voter_number << " voter today." << endl;
        cout << "The question of today's poll is: " << endl << question << endl;
        cout << "1. " << first_answer << endl << "2. " << second_answer << endl << "3. " << third_answer << endl;
        cout << "(Enter 1, 2 or 3 to cast your vote. Enter 0 to finish the poll.)" << endl;
        cout << "Answer: ";
        cin >> vote;
        if ( !( vote == 0 || vote == 1 || vote == 2 || vote == 3 ) )
        {
            cout << "Failed to cast vote." << endl;
            voter_number--;
        }
        if ( vote == 1 )
        {
            first_option_votes++;
        }
        else if ( vote == 2 )
        {
            second_option_votes++;
        }
        else if ( vote == 3 )
        {
            third_option_votes++;
        }
    } while ( vote != 0 );
    cout << endl << "Poll came to an end." << endl << endl;
    
    voter_number--; // trzeba zmniejszyc o jeden, bo ostatni oddany glos to wyjście z sondy
    cout << voter_number << " people voted in the poll." << endl << endl;
   
    cout << "RESULTS:" << endl;
    
    int votes_all_together;
    votes_all_together = first_option_votes + second_option_votes + third_option_votes;
    double first_percentage;
    double second_percentage;
    double third_percentage;
    first_percentage = (first_option_votes/votes_all_together)*100;
    second_percentage = (second_option_votes/votes_all_together)*100;
    third_percentage = (third_option_votes/votes_all_together)*100;
    
    cout << first_option_votes << " voted " << first_answer << "." << endl;
    cout << second_option_votes << " voted " << second_answer << "." << endl;
    cout << third_option_votes << " voted " << third_answer << "." << endl;
    
    // która odpowiedź jest najdłuższa
    string the_longest;
    the_longest = first_answer;
    if (second_answer.length() > the_longest.length())
    {
        the_longest = second_answer;
    }
    if (third_answer.length() > the_longest.length())
    {
        the_longest = third_answer;
    }
    while (first_answer.length() < the_longest.length())
    {
        first_answer = first_answer + " ";
    }
    while (second_answer.length() < the_longest.length())
    {
        second_answer = second_answer + " ";
    }
    while (third_answer.length() < the_longest.length())
    {
        third_answer = third_answer + " ";
    }
    // dzieki temu będą wyrównane słupki
    
    cout << endl;
    
    cout << first_answer << " ";
    for ( int i = 0; i < (first_percentage/2); i++)
    {
        cout << "|";
    }
    cout << '\t' << first_percentage << '%' << endl;
    
    cout << second_answer << " ";
    for ( int i = 0; i < (second_percentage/2); i++)
    {
        cout << "|";
    }
    cout << '\t' << second_percentage << '%' << endl;
    
    cout << third_answer << " ";
    for ( int i = 0; i < (third_percentage/2); i++)
    {
        cout << "|";
    }
    cout << '\t' << third_percentage << '%' << endl;
}