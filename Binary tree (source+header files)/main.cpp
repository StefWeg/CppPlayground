//
//  main.cpp
//  Binary tree (source+header files)
//
//  Created by Stefan Węgrzyn on 29.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>
#include "tree.hpp"

using namespace std;

int main ()
{
    int indicator = 0;
    node* p_tree = NULL;
    node* p_searchedNode = NULL;
    
    while (indicator != 9)
    {
        cout << "MENU:" << endl;
        cout << "1. Print nodes in binary tree in sorted order" << endl;
        cout << "2. Print nodes in binary tree in reverse sorded order" << endl;
        cout << "3. Add new node" << endl;
        cout << "4. Delete existing node" << endl;
        cout << "5. Count nodes" << endl;
        cout << "6. Check if tree is properly organized" << endl;
        cout << "7. Check if tree is properly balanced" << endl;
        cout << "8. Balance tree" << endl;
        cout << "9. Exit database" << endl;
        cout << "Choose an option: ";
        
        string input = "";
        getline(cin, input, '\n');
        try
        {
            indicator = stoi (input);
        } catch (...)
        {
            cout << "Wrong input!" << endl;
            continue;
        }
        
        int key = 0;
        switch (indicator)
        {
            case 1:
                display(p_tree);
                cout << endl << endl;
                break;
            case 2:
                displayReversed(p_tree);
                cout << endl << endl;
                break;
            case 3:
                cout << "Enter new key value: ";
                getline(cin, input, '\n');
                try {key = stoi (input);}
                catch (...) {cout << "Wrong input!" << endl << endl; break;}
                p_searchedNode = search (p_tree, key);
                if (p_searchedNode == NULL)
                {
                    p_tree = insert(p_tree, key);
                    cout << "New node successfully added!" << endl << endl;
                    break;
                }
                else cout << "Node with such key value already exists!" << endl << endl;
                break;
            case 4:
                cout << "Enter key value of node to delete: ";
                getline(cin, input, '\n');
                try {key = stoi (input);}
                catch (...) {cout << "Wrong input!" << endl << endl; break;}
                p_searchedNode = search (p_tree, key);
                if (p_searchedNode != NULL)
                {
                    p_tree = remove (p_tree, key);
                    cout << "Node successfully deleted!" << endl << endl;
                    break;
                }
                else cout << "Node with such key value does not exists!" << endl << endl;
                break;
            case 5:
                cout << "Binary tree consists of " << countNodes(p_tree) << " nodes." << endl << endl;
                break;
            case 6:
                if (checkTreeOrganization(p_tree)) cout << "Binary tree is properly organized!" << endl << endl;
                else cout << "Oops! Binary tree is not correctly organized!" << endl << endl;
                break;
            case 7:
                if (fullTreeBalanceCheck(p_tree)) cout << "Binary tree is properly balanced!" << endl << endl;
                else cout << "Oops! Binary tree is not propperly balanced!" << endl << endl;
                break;
            case 8:
                p_tree = balanceTree (p_tree);
                cout << "Tree successfully balanced!" << endl << endl;
                break;
            case 9:
                destroyTree(p_tree);
                break;
            default:
                cout << "There is not such option!" << endl << endl;
                break;
        }
    }
    
    return 0;
}