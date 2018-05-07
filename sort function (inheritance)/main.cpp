//
//  main.cpp
//  sort function (inheritance)
//
//  Created by Stefan Węgrzyn on 03.08.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <vector>

// =========================================================================

class Comparable
{
public:
    Comparable (std::string name, int score);
    virtual ~Comparable ();
    Comparable& operator= (const Comparable& other);
    int compare (const Comparable& other);
    const std::string& getName () const;
    const int& getScore () const;
protected:
    virtual bool operator== (const Comparable& other) = 0;
    virtual bool operator> (const Comparable& other) = 0;
    virtual bool operator< (const Comparable& other) = 0;
private:
    std::string _name;
    int _score;
};

Comparable::Comparable(std::string name, int score)
    : _name(name)
    , _score(score)
{}

Comparable::~Comparable()
{}

Comparable& Comparable::operator= (const Comparable& other)
{
    if (this == &other) return *this;
    _name = other._name;
    _score = other._score;
    return *this;
}

int Comparable::compare (const Comparable& other)
{
    if (*this < other) return -1;
    else if (*this > other) return 1;
    else return 0; // (*this == other)
}

const std::string& Comparable::getName() const
{
    return _name;
}

const int& Comparable::getScore() const
{
    return _score;
}

// =========================================================================

class HighScoreElement : public Comparable
{
public:
    HighScoreElement (std::string name, int score);
    ~HighScoreElement () override;
    bool operator== (const Comparable& other) override;
    bool operator> (const Comparable& other) override;
    bool operator< (const Comparable& other) override;
};

HighScoreElement::HighScoreElement(std::string name, int score)
    : Comparable(name,score)
{}

HighScoreElement::~HighScoreElement()
{}

bool HighScoreElement::operator==(const Comparable& other)
{
    if (other.getName() == this->getName() && other.getScore() == this->getScore()) return true;
    else return false;
}

bool HighScoreElement::operator>(const Comparable& other)
{
    if (this->getScore() == other.getScore()) {
        if (this->getName() < other.getName()) return true;
        else return false;
    } else {
        if (getScore() > other.getScore()) return true;
        else return false;
    }
}

bool HighScoreElement::operator<(const Comparable& other)
{
    if (this->getScore() == other.getScore()) {
        if (this->getName() > other.getName()) return true;
        else return false;
    } else {
        if (getScore() < other.getScore()) return true;
        else return false;
    }
}

// =========================================================================

std::vector<Comparable*> sort (std::vector<Comparable*>& inserted)
{
    int counter = 1;
    std::vector<Comparable*> newVector = inserted;
    while (counter)
    {
        counter = 0;
        for (std::vector<Comparable*>::iterator itr = newVector.begin()+1, end = newVector.end();
             itr != end; ++itr)
        {
            if ((*itr)->compare(*(*(itr-1))) == 1)
            {
                Comparable* temporary = *(itr-1);
                *(itr-1) = *itr;
                *itr = temporary;
                counter++;
            }
        }
    }
    return newVector;
}

// =========================================================================

int main()
{
    HighScoreElement first("Stefan",100);
    HighScoreElement second("Aaron",100);
    HighScoreElement third("Jan",120);
    HighScoreElement fourth("Kuba",80);
    HighScoreElement fifth("Marcin",90);
    
    std::vector<Comparable*> my_vector;
    my_vector.push_back(&first);
    my_vector.push_back(&second);
    my_vector.push_back(&third);
    my_vector.push_back(&fourth);
    my_vector.push_back(&fifth);
    
    for (std::vector<Comparable*>::iterator itr = my_vector.begin(), end = my_vector.end();
         itr != end; ++itr)
    {
        std::cout << (*itr)->getScore() << " " << (*itr)->getName() << std::endl;
    }
    
    std::cout << std::endl;
    my_vector = sort (my_vector);
    
    for (std::vector<Comparable*>::iterator itr = my_vector.begin(), end = my_vector.end();
         itr != end; ++itr)
    {
        std::cout << (*itr)->getScore() << " " << (*itr)->getName() << std::endl;
    }
    
    std::cout << std::endl;
}
