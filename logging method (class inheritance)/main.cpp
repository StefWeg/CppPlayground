//
//  main.cpp
//  logging method (class inheritance)
//
//  Created by Stefan Węgrzyn on 05.08.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

// ==================================================================================================

#include <ctime>

class StringConvertable
{
public:
    virtual ~StringConvertable ();
    std::string log ();
protected:
    virtual std::string toString () = 0;
};

StringConvertable::~StringConvertable ()
{}

std::string StringConvertable::log ()
{
    time_t timespan = time(NULL);
    struct tm* timeParameters;
    timeParameters = localtime(&timespan);
    char* timeInfo = asctime(timeParameters);
    std::string message = timeInfo;
    message = message + "  " + toString();
    return message;
}

// ==================================================================================================

class Player : public StringConvertable
{
public:
    ~Player ();
    std::string toString ();
    void setPlayer (std::string nickname, int level, std::string profession, std::string game_world);
private:
    std::string _nickname;
    int _level;
    std::string _profession;
    std::string _game_world;
};

Player::~Player ()
{}

std::string Player::toString ()
{
    std::string level = std::to_string(_level);
    std::string output_string = _game_world + ": " + _nickname + " (" + level + ", " + _profession + ")";
    return output_string;
}

void Player::setPlayer (std::string nickname, int level, std::string profession, std::string game_world)
{
    _nickname = nickname;
    _level = level;
    _profession = profession;
    _game_world = game_world;
}

// ==================================================================================================

int main()
{
    Player firstPlayer;
    firstPlayer.setPlayer("Sztosumitsu", 100, "knight", "Harmonia");
    std::cout << firstPlayer.log() << std::endl;
    Player secondPlayer;
    secondPlayer.setPlayer("Werpulewski", 89, "sorcerer", "Xantera");
    std::cout << secondPlayer.log() << std::endl;
}
