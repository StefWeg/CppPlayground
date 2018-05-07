//
//  main.cpp
//  case-insensitive string comparator (static method)
//
//  Created by Stefan Węgrzyn on 04.08.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <vector>

// ==================================================================================================

class CaseInsensitiveComparator
{
public:
    static int compare(const std::string& lhs, const std::string& rhs);
private:
    static int _compareChars(const char& lhs, const char& rhs);
};

int CaseInsensitiveComparator::compare (const std::string &lhs, const std::string& rhs)
// returns 1 when lhs > rhs, 0 when lhs == rhs, -1 lhs < rhs
{
    // ckecking if strings consists of letter chars
    for (int i = 0; i < lhs.size(); i++)
    {
        int ASCII_number = static_cast<int>(lhs[i]);
        if (!( (ASCII_number>=65 && ASCII_number<=90) || (ASCII_number>=97 && ASCII_number<=122) )) {
            std::string error = "non-letter chars included in string!"; throw error;
        }
    }
    for (int i = 0; i < rhs.size(); i++)
    {
        int ASCII_number = static_cast<int>(rhs[i]);
        if (!( (ASCII_number>=65 && ASCII_number<=90) || (ASCII_number>=97 && ASCII_number<=122) )) {
            std::string error = "non-letter chars included in string!"; throw error;
        }
    }
    // comparing strings
    if (lhs.size() <= rhs.size()) {
        for (int i = 0; i < lhs.size(); i++)
        {
            if (_compareChars(lhs[i],rhs[i]) != 0) return _compareChars(lhs[i],rhs[i]);
        }
        return -1; // if to this point all chars were the same than shorter lhs should be first in order
    } else { // lhs.size() > rhs.size()
        for (int i = 0; i < lhs.size(); i++)
        {
            if (_compareChars(lhs[i],rhs[i]) != 0) return _compareChars(lhs[i],rhs[i]);
        }
        return 1; // if to this point all chars were the same than shorter rhs should be first in order
    }
}

int CaseInsensitiveComparator::_compareChars(const char& lhchar, const char& rhchar)
// returns 1 when lhs > rhs, 0 when lhs == rhs, -1 lhs < rhs
{
    int lhs_number = static_cast<int>(lhchar);
    int rhs_number = static_cast<int>(rhchar);
    // case when lhchar is upper case and rhchar is lowercase
    if ( (lhs_number>=65 && lhs_number<=90) && (rhs_number>=97 && rhs_number<=122) ) lhs_number += 32;
    // case when lhchar is lower case and rhchar is uppercase
    else if ( (lhs_number>=97 && lhs_number<=122) && (rhs_number>=65 && rhs_number<=90) ) lhs_number -= 32;
    // returning values
    if (lhs_number > rhs_number) return 1;
    else if (lhs_number < rhs_number) return -1;
    else return 0;
}

// ==================================================================================================

std::vector<std::string> sort (std::vector<std::string>& inserted)
{
    int counter = 1;
    std::vector<std::string> newVector = inserted;
    while (counter)
    {
        counter = 0;
        for (std::vector<std::string>::iterator itr = newVector.begin()+1, end = newVector.end();
             itr != end; ++itr)
        {
            if (CaseInsensitiveComparator::compare(*(itr-1),*itr) == 1)
            {
                std::string temporary = *(itr-1);
                *(itr-1) = *itr;
                *itr = temporary;
                counter++;
            }
        }
    }
    return newVector;
}

// ==================================================================================================

int main()
{
    std::string first = "Stefan";
    std::string second = "Stefanon";
    std::string third = "aaron";
    std::string fourth = "Aaron";
    std::string fifth = "stefan";
    
    std::vector<std::string> my_vector;
    my_vector.push_back(first);
    my_vector.push_back(second);
    my_vector.push_back(third);
    my_vector.push_back(fourth);
    my_vector.push_back(fifth);
    
    for (std::vector<std::string>::iterator itr = my_vector.begin(), end = my_vector.end();
         itr != end; ++itr)
    {
        std::cout << *itr << std::endl;
    }
    
    std::cout << std::endl;
    my_vector = sort (my_vector);
    
    for (std::vector<std::string>::iterator itr = my_vector.begin(), end = my_vector.end();
         itr != end; ++itr)
    {
        std::cout << *itr << std::endl;
    }
    
    std::cout << std::endl;
    
    return 0;
}