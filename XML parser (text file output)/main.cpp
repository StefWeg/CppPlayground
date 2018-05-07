//
//  main.cpp
//  XML parser (text file output)
//
//  Created by Stefan Węgrzyn on 09.08.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

// ------------------------------------------------------------------------------------------------------------------------

class XMLreader
{
public:
    XMLreader (string filePath);
    ~XMLreader ();
    void parse ();
private:
    fstream file;
    bool ready;
    int nodesOpen;
    void nodeStart ();
    void attributeRead ();
    void nodeTextRead ();
    void nodeEnd ();
};

XMLreader::XMLreader (string filePath)
    : file (filePath, ios::in)
    , ready (false)
{
    if (file.is_open()) {
        ready = true;
        file.seekg(0,ios::beg);
    }
}

XMLreader::~XMLreader()
{
    file.close();
}

void XMLreader::parse ()
{
    // displays each element of the file as it is parsed
    if (!ready) {cout << "Unable to read file!" << endl; return;}
    nodesOpen = 0;
    file.seekg(0,ios::beg);
    char currentChar;
    while (file.get(currentChar)) {
        if (currentChar == '<') nodeStart();
        else if (currentChar == '\r' || currentChar == '\t' || currentChar == '\n') continue;
        else if (nodesOpen != 0) {
            file.seekg(-1,ios::cur);
            nodeTextRead();
        }
    }
    if (file.fail() && !file.eof()) {
        cout << "Error reading file!" << endl; return;
    }
    if (nodesOpen != 0) {
        cout << "Some nodes unclosed! File cannot be read properly." << endl; return;
    }
}

void XMLreader::nodeStart()
{
    char currentChar;
    file.get(currentChar);
    if (file.eof()) return;
    else if (file.fail()) {cout << "Error reading file!" << endl;}
    else if (currentChar == ' ') attributeRead();
    else if (currentChar == '/') nodeEnd();
    else {
        ++nodesOpen;
        file.seekg(-1,ios::cur);
        string nodeName;
        getline(file,nodeName,'>');
        if (file.eof()) {cout << "Hit eof when reading node name!" << endl; return;}
        else if (file.fail()) {cout << "Error reading file!" << endl; return;}
        cout << "Node open: " << nodeName << endl;
    }
}

void XMLreader::attributeRead()
{
    string nodeAttribute;
    getline(file,nodeAttribute,'>');
    if (file.eof()) {cout << "Hit eof when reading node attribute!" << endl; return;}
    else if (file.fail()) {cout << "Error reading file!" << endl; return;}
    cout << "Node attribute: " << nodeAttribute << endl;
}

void XMLreader::nodeTextRead()
{
    string data;
    getline (file,data,'<');
    if (file.eof()) {cout << "Hit eof when reading data!" << endl; return;}
    else if (file.fail()) {cout << "Error reading file!" << endl; return;}
    cout << data << endl;
    file.seekg(-1,ios::cur);
}

void XMLreader::nodeEnd()
{
    --nodesOpen;
    string nodeName;
    getline(file,nodeName,'>');
    if (file.eof()) {cout << "Hit eof when reading node name!" << endl; return;}
    else if (file.fail()) {cout << "Error reading file!" << endl; return;}
    cout << "Node closed: " << nodeName << endl;
}

// ------------------------------------------------------------------------------------------------------------------------

int main ()
{
    string filePath = "/filepath/XMLfile.txt";
    XMLreader myFile(filePath);
    myFile.parse();
}
