//
//  main.cpp
//  HTML interpreter (text file output)
//
//  Created by Stefan Węgrzyn on 09.08.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void htmlTag(string &HTMLtext)
{
    // extracts text between html tags
    long int startPosition = HTMLtext.find("<html>",0);
    long int endPosition = HTMLtext.find("</html>",startPosition+6);
    if (startPosition == string::npos) {string error = "html open tag not found!"; throw error;}
    if (endPosition == string::npos) {string error = "html closing tag not found!"; throw error;}
    long int lengthOfTextInside = (endPosition-1)-(startPosition+5);
    HTMLtext = HTMLtext.substr(startPosition+6,lengthOfTextInside);
}

void headTag(long int startPosition, string &HTMLtext)
{
    // removes text between all head tags with tags themselves
    startPosition = HTMLtext.find("<head>",startPosition);
    if (startPosition == string::npos) return;
    long int endPosition = HTMLtext.find("</head>",startPosition);
    if (endPosition == string::npos) return;
    headTag(endPosition+7, HTMLtext); // recursive call
    long int lengthOfTextInsideWithTags = (endPosition+6)-(startPosition-1);
    HTMLtext.erase(startPosition,lengthOfTextInsideWithTags);
}

void bodyTag(long int startPosition, string &HTMLtext)
{
    // extracts text between all body tags
    long int openTagPosition = HTMLtext.find("<body>",startPosition);
    if (openTagPosition == string::npos)
    {
        long int lengthFromStartToEndOfString = (HTMLtext.length()-1)-(startPosition-1);
        HTMLtext.erase(startPosition,lengthFromStartToEndOfString);
        return;
    }
    long int closingTagPosition = HTMLtext.find("</body>",startPosition);
    if (closingTagPosition == string::npos)
    {
        long int lengthFromStartToEndOfString = (HTMLtext.length()-1)-(startPosition-1);
        HTMLtext.erase(startPosition,lengthFromStartToEndOfString);
        return;
    }
    bodyTag(closingTagPosition+7, HTMLtext); // recursive all
    HTMLtext.erase(closingTagPosition,7);
    long int lengthFromStartToEndOfOpeningTag = (HTMLtext.find("<body>",startPosition)+5)-(startPosition-1);
    HTMLtext.erase(startPosition,lengthFromStartToEndOfOpeningTag);
}

void bTag(long int startPosition, string &HTMLtext)
{
    // marks text between b tags with * on both sides
    startPosition = HTMLtext.find("<b>",startPosition);
    if (startPosition == string::npos) return;
    long int endPosition = HTMLtext.find("</b>",startPosition);
    if (endPosition == string::npos) return;
    bTag(endPosition+4, HTMLtext); // recursive all
    HTMLtext.insert(endPosition+4,"*");
    HTMLtext.erase(endPosition,4);
    HTMLtext.erase(startPosition,3);
    HTMLtext.insert(startPosition,"*");
}

void iTag(long int startPosition, string &HTMLtext)
{
    // marks text between i tags with _ on both sides
    startPosition = HTMLtext.find("<i>",startPosition);
    if (startPosition == string::npos) return;
    long int endPosition = HTMLtext.find("</i>",startPosition);
    if (endPosition == string::npos) return;
    iTag(endPosition+4, HTMLtext); // recursive all
    HTMLtext.insert(endPosition+4,"_");
    HTMLtext.erase(endPosition,4);
    HTMLtext.erase(startPosition,3);
    HTMLtext.insert(startPosition,"_");
}

void aTag(long int startPosition, string &HTMLtext)
{
    // removes a tags and insert (linkURL) after hypertext
    startPosition = HTMLtext.find("<a href=",startPosition);
    if (startPosition == string::npos) return;
    long int endPosition = HTMLtext.find("</a>",startPosition);
    if (endPosition == string::npos) return;
    aTag(endPosition+4, HTMLtext); // recursive all
    long int endOfOpeningTagPosition = HTMLtext.find(">",startPosition);
    if (endOfOpeningTagPosition > endPosition) return;
    long int URLlength = (endOfOpeningTagPosition-1)-(startPosition+7);
    string URL = HTMLtext.substr(startPosition+8,URLlength);
    HTMLtext.insert(endPosition+4," ()");
    HTMLtext.insert(endPosition+6,URL);
    HTMLtext.erase(endPosition,4);
    long int openingTagLength = endOfOpeningTagPosition-(startPosition-1);
    HTMLtext.erase(startPosition,openingTagLength);
}


int main ()
{
    // reading from file -----------------------
    string filePath = "/filepath/htmlfile.txt";
    fstream htmlFile (filePath, ios::in);
    if (! htmlFile.is_open()) {
        cout << "Could not read the file!" << endl;
        return 1;
    }
    string HTMLtext;
    htmlFile.seekg(0,ios::end);
    long int size = htmlFile.tellg();
    size++; // to insert '\0'
    char HTMLcstring[size];
    htmlFile.seekg(0,ios::beg);
    htmlFile.getline(HTMLcstring,size);
    if ( htmlFile.fail() ) {
        cout << "Error reading text file!" << endl;
        return 1;
    }
    HTMLtext = HTMLcstring;
    htmlFile.clear();
    htmlFile.close();
    // -----------------------------------------
    
    cout << HTMLtext << endl << endl;
    
    try {htmlTag(HTMLtext);}
    catch (string error) {cout << error << endl; return 0;}
    cout << HTMLtext << endl << endl;
    
    headTag(0,HTMLtext);
    cout << HTMLtext << endl << endl;
    
    bodyTag(0,HTMLtext);
    cout << HTMLtext << endl << endl;
    
    bTag(0,HTMLtext);
    cout << HTMLtext << endl << endl;
    
    iTag(0,HTMLtext);
    cout << HTMLtext << endl << endl;
    
    aTag(0,HTMLtext);
    cout << HTMLtext << endl << endl;
    
    return 0;
}
