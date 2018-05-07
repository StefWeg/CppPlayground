//
//  main.cpp
//  Contact book (binary tree database)
//
//  Created by Stefan Węgrzyn on 24.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

using namespace std;

struct node
{
    string key_name;
    string email;
    node* p_left;
    node* p_right;
};

void contactEditor (node* p_tree);
bool checkIfBeginsFromCapitalLetter (string name);
void advancedOptions (node** p_p_tree);
node* insert (node* p_tree, string key_name);
node* searchByName (node* p_tree, string key_name);
node* searchByEmail (node* p_tree, string email);
void destroyTree (node* p_tree);
node* find_max (node* p_tree);
node* remove_max_node (node* p_tree, node* p_max_node);
node* remove (node* p_tree, string key_name);
void display (node* p_tree);
int countNodes (node* p_tree);
bool checkTreeOrganization (node* p_tree);
node* find_n_node (node* p_tree, int n);
bool checkTreeBalance (node* p_tree);
bool fullTreeBalanceCheck (node* p_tree);
node* createArrayOfNodes (node* p_tree);
node* transformArrayIntoTree (node *array, int length);
node* balanceTree (node* p_tree);


int main ()
{
    int indicator = 0;
    node* p_tree = NULL;
    node* p_searchedNode = NULL;
    
    while (indicator != 8)
    {
        cout << "CONTACT BOOK:" << endl;
        cout << "1. Print contacts in alphabetical order" << endl;
        cout << "2. Find email by name" << endl;
        cout << "3. Find name by email" << endl;
        cout << "4. Add new contact" << endl;
        cout << "5. Edit existing contact" << endl;
        cout << "6. Remove contact" << endl;
        cout << "7. Advanced options" << endl;
        cout << "8. Exit contact book" << endl;
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
        
        switch (indicator)
        {
            case 1:
                cout << "--------------------" << endl;
                cout << "Contacts: " << endl;
                display(p_tree);
                cout << "--------------------" << endl << endl;
                break;
            case 2:
                cout << "Enter the name of the person: ";
                getline(cin, input, '\n');
                p_searchedNode = searchByName (p_tree, input);
                if (p_searchedNode != NULL)
                {
                    if (p_searchedNode->email != "")
                    {
                        cout << p_searchedNode->key_name << "'s email: " << p_searchedNode->email << endl << endl;
                    }
                    else
                    {
                        cout << p_searchedNode->key_name << "'s email unknown" << endl << endl;
                    }
                }
                else cout << "There is no person with such a name in contactbook!" << endl << endl;
                break;
            case 3:
                cout << "Enter email of the person: ";
                getline(cin, input, '\n');
                p_searchedNode = searchByEmail (p_tree, input);
                if (p_searchedNode != NULL)
                {
                    cout << p_searchedNode->email << " belongs to: " << p_searchedNode->key_name << endl << endl;
                }
                else cout << "There is no person with such an email in contactbook!" << endl << endl;
                break;
            case 4:
                cout << "Enter name of the person: ";
                getline(cin, input, '\n');
                if (!checkIfBeginsFromCapitalLetter(input))
                {
                    cout << "The name you entered is incorrect (should start with capital letter)" << endl << endl;
                    continue;
                }
                p_searchedNode = searchByName (p_tree, input);
                if (p_searchedNode == NULL)
                {
                    p_tree = insert(p_tree, input);
                }
                else
                {
                    cout << "Person with such a name already exists in contactbook!" << endl << endl;
                    continue;
                }
                p_searchedNode = searchByName (p_tree, input);
                cout << "Enter person's email: ";
                getline(cin, input, '\n');
                p_searchedNode->email = input;
                cout << "Contact successfully added!" << endl << endl;
                break;
            case 5:
                contactEditor (p_tree);
                break;
            case 6:
                cout << "Enter the name of person to delete: ";
                getline(cin, input, '\n');
                p_searchedNode = searchByName (p_tree, input);
                if (p_searchedNode != NULL)
                {
                    p_tree = remove (p_tree, input);
                    cout << "Contact successfully deleted!" << endl << endl;
                    break;
                }
                else cout << "There is no person with such a name in contact book!" << endl << endl;
                break;
            case 7:
                advancedOptions(&p_tree);
                break;
            case 8:
                destroyTree(p_tree);
                break;
            default:
                cout << "There is not such option!" << endl << endl;
                break;
        }
    }
    
    return 0;
}


void contactEditor (node* p_tree)
{
    string input;
    int indicator;
    node* p_searchedNode = NULL;
    
    while (indicator != 3)
    {
        cout << endl;
        cout << "Contact editor: " << endl;
        cout << "1. Add/update contact email" << endl;
        cout << "2. Remove contact email" << endl;
        cout << "3. Go back to contact book" << endl;
        cout << "Choose an option: ";
        
        getline(cin, input, '\n');
        try {indicator = stoi (input);}
        catch (...) {cout << "Wrong input!" << endl; continue;}
        
        switch (indicator)
        {
            case 1:
                cout << "Enter name of the person: ";
                getline(cin, input, '\n');
                p_searchedNode = searchByName(p_tree, input);
                if (p_searchedNode != NULL)
                {
                    if (p_searchedNode->email == "")
                    {
                        cout << "Enter email: ";
                        getline(cin, input, '\n');
                        p_searchedNode->email = input;
                        cout << "Email successfully added to contact!" << endl;
                    }
                    else
                    {
                        cout << "There is already an email associated with this name in contact book!" << endl;
                        cout << "Do you want to replace '" << p_searchedNode->email << "' with new email?" << endl;
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
                                getline(cin, input, '\n');
                                p_searchedNode->email = input;
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
            case 2:
                cout << "Enter name of the person: ";
                getline(cin, input, '\n');
                p_searchedNode = searchByName(p_tree, input);
                if (p_searchedNode != NULL)
                {
                    if (p_searchedNode->email != "")
                    {
                        p_searchedNode->email = "";
                        cout << "Email successfully deleted from contact!" << endl;
                    }
                    else
                    {
                        cout << "There is no email associated with this name in contact book!" << endl;
                    }
                }
                else cout << "There is no person with such a name in contact book!" << endl;
                break;
            case 3:
                cout << endl;
                return;
                break;
            default:
                cout << "There is not such option!" << endl;
                break;
        }
    }
}

bool checkIfBeginsFromCapitalLetter (string name)
{
    if (static_cast<int>(name[0]) >= 65 && static_cast<int>(name[0]) <= 90) return true;
    else return false;
}

void advancedOptions (node** p_p_tree)
{
    string input;
    int indicator;
    
    while (indicator != 4)
    {
        cout << endl;
        cout << "Advanced options: " << endl;
        cout << "1. Check if contact database is properly organized" << endl;
        cout << "2. Check if contact database is properly balanced" << endl;
        cout << "3. Balance database" << endl;
        cout << "4. Go back to contact book" << endl;
        cout << "Choose an option: ";
        
        getline(cin, input, '\n');
        try {indicator = stoi (input);}
        catch (...) {cout << "Wrong input!" << endl; continue;}
        
        switch (indicator)
        {
            case 1:
                if (checkTreeOrganization(*p_p_tree)) cout << "Binary tree is properly organized!" << endl;
                else cout << "Oops! Binary tree is not correctly organized!" << endl;
                break;
            case 2:
                if (fullTreeBalanceCheck(*p_p_tree)) cout << "Binary tree is properly balanced!" << endl;
                else cout << "Oops! Binary tree is not propperly balanced!" << endl;
                break;
            case 3:
                *p_p_tree = balanceTree (*p_p_tree);
                cout << "Tree successfully balanced!" << endl;
                break;
            case 4:
                cout << endl;
                return;
                break;
            default:
                cout << "There is not such option!" << endl;
                break;
        }
    }
}

node* insert (node* p_tree, string key_name)
{
    // returns pointer to the tree
    if (p_tree == NULL)
    {
        node* p_newTree = new node;
        p_newTree->key_name = key_name;
        p_newTree->p_left = NULL;
        p_newTree->p_right = NULL;
        return p_newTree;
    }
    
    if (key_name < p_tree->key_name)
    {
        p_tree->p_left = insert (p_tree->p_left, key_name);
    }
    else if (key_name > p_tree->key_name)
    {
        p_tree->p_right = insert (p_tree->p_right, key_name);
    }
    return p_tree; // when key_name == p_tree->key_name function will hit return and do nothing overall
}

node* searchByName (node* p_tree, string key_name)
{
    // returns pointer to node with key_name provided
    if (p_tree == NULL)
    {
        return NULL;
    }
    if (key_name == p_tree->key_name)
    {
        return p_tree;
    }
    else if (key_name < p_tree->key_name)
    {
        return searchByName (p_tree->p_left, key_name);
    }
    else
    {
        return searchByName (p_tree->p_right, key_name);
    }
}

node* searchByEmail (node* p_tree, string email)
{
    // returns pointer to node with email provided
    if (p_tree != NULL)
    {
        if (p_tree->email == email)
        {
            return p_tree;
        }
        
        if (searchByEmail(p_tree->p_left, email) != NULL)
        {
            return searchByEmail(p_tree->p_left, email);
        }
        else if (searchByEmail(p_tree->p_right, email) != NULL)
        {
            return searchByEmail(p_tree->p_right, email);
        }
    }
    return NULL; // simply returns when p_tree == NULL
}

void destroyTree (node* p_tree)
{
    // deallocates all pointers in the tree
    if (p_tree != NULL)
    {
        destroyTree(p_tree->p_left);
        destroyTree(p_tree->p_right);
        delete p_tree;
    }
    return; // simply returns when p_tree == NULL
}

node* find_max (node* p_tree)
{
    // function needed to realize 'remove' and 'find_n_node' function
    // returns pointer to node with max value in the tree
    if (p_tree == NULL)
    {
        return NULL;
    }
    if (p_tree->p_right == NULL)
    {
        return p_tree;
    }
    return find_max(p_tree->p_right);
}

node* remove_max_node (node* p_tree, node* p_max_node)
{
    // function needed to realize 'remove' function
    // returns pointer to the tree with removed max_node
    // (removing here means redirecting pointers to and from max_node)
    // (we are not deleting p_max_node as 'remove' funcion uses max_node)
    if (p_tree == NULL)
    {
        return NULL;
    }
    if (p_tree == p_max_node)
    {
        return p_max_node->p_left; // p_right of p_max_node is empty
    }
    p_tree->p_right = remove_max_node(p_tree->p_right, p_max_node);
    return p_tree;
}

node* remove (node* p_tree, string key_name)
{
    // returns pointer to the tree
    if (p_tree == NULL)
    {
        return NULL;
    }
    if (key_name == p_tree->key_name)
    {
        if (p_tree->p_left == NULL) // handles situation when left subtree is empty or both
        {
            node* p_right_subtree = p_tree->p_right;
            delete p_tree;
            return p_right_subtree; // if right subtree is also empty will return NULL which is fine
        }
        else if (p_tree->p_right == NULL) // handles situation when right subtree is empty (left is not: checked earlier)
        {
            node* p_left_subtree = p_tree->p_left;
            delete p_tree;
            return p_left_subtree;
        }
        else // handling situation when neither subtree is empty
        {
            node* p_max_node = find_max (p_tree->p_left); // max_node of left subtree will be the next parent node
            p_max_node->p_left = remove_max_node(p_tree->p_left, p_max_node); // max_node' left subtree: left subtree of the original parent node with no max_node inside
            p_max_node->p_right = p_tree->p_right; // max_node' right subtree: right subtree of the original parent node
            delete p_tree;
            return p_max_node;
        }
    }
    else if (key_name < p_tree->key_name)
    {
        p_tree->p_left = remove (p_tree->p_left, key_name);
    }
    else
    {
        p_tree->p_right = remove (p_tree->p_right, key_name);
    }
    return p_tree;
}

void display (node* p_tree)
{
    if (p_tree != NULL)
    {
        display(p_tree->p_left);
        // desplaying key_name and email after left subtree and before right subtree
        cout << p_tree->key_name << ": " << p_tree->email << endl;
        display(p_tree->p_right);
    }
    return; // simply returns when p_tree == NULL
}

int countNodes (node* p_tree)
{
    // returns number of nodes
    if (p_tree != NULL)
    {
        return countNodes(p_tree->p_left) + countNodes(p_tree->p_right) + 1;
    }
    return 0; // returns 0 when p_tree == NULL
}

bool checkTreeOrganization (node* p_tree)
{
    // returns true when nodes are properly arranged (left < parent && right > parent)
    if (p_tree->p_left == NULL && p_tree->p_right == NULL)
    {
        return true;
    }
    if (p_tree->p_left == NULL && (p_tree->p_right)->key_name > p_tree->key_name)
    {
        if (checkTreeOrganization(p_tree->p_right))
        {
            return true;
        }
    }
    if ((p_tree->p_left)->key_name < p_tree->key_name && p_tree->p_right == NULL)
    {
        if (checkTreeOrganization(p_tree->p_left))
        {
            return true;
        }
    }
    if ((p_tree->p_left)->key_name < p_tree->key_name && (p_tree->p_right)->key_name > p_tree->key_name)
    {
        if (checkTreeOrganization(p_tree->p_left) && checkTreeOrganization(p_tree->p_right))
        {
            return true;
        }
    }
    return false;
}

node* find_n_node (node* p_tree, int n)
{
    // returns pointer to n node
    if (countNodes(p_tree) < n) return NULL; // handles case when parameters are wrong
    
    if (countNodes(p_tree) == n)
        // if current subtree consists of n nodes find max_node and return it
    {
        return find_max(p_tree);
    }
    if (countNodes(p_tree->p_left) < n)
        // if left subtree consists of less than n nodes decrement n by number of nodes in left subtree + 1 (parent node) and make a recursive call with right subtree as an argument
    {
        n = n - (countNodes(p_tree->p_left) + 1);
        if (n == 0) return p_tree; // handles the situation when parent node is the searched one
        else return find_n_node(p_tree->p_right, n);
    }
    else
        // in case when countNodes(p_tree->p_left) >= n make a recursive call with left subtree as an argument
    {
        return find_n_node(p_tree->p_left, n);
    }
}

bool checkTreeBalance (node* p_tree)
{
    // returns true when tree is properly balanced
    if (p_tree == NULL) // no nodes
    {
        return true;
    }
    if (countNodes(p_tree)%2 == 0) // even number of nodes
    {
        if (find_n_node(p_tree, countNodes(p_tree)/2)->key_name == p_tree->key_name) return true;
        else if (find_n_node(p_tree, (countNodes(p_tree)/2)+1)->key_name == p_tree->key_name) return true;
        else return false;
    }
    else // odd number of nodes
    {
        if (find_n_node(p_tree, (countNodes(p_tree)/2)+1)->key_name == p_tree->key_name) return true;
        else return false;
    }
}

bool fullTreeBalanceCheck (node* p_tree)
{
    // returns true when every subtree of the tree is properly balanced
    if (p_tree != NULL)
    {
        if (checkTreeBalance(p_tree->p_left) && checkTreeBalance(p_tree->p_right))
        {
            if (checkTreeBalance(p_tree)) return true;
            else return false;
        }
        else return false;
    }
    else return true;
}

node* createArrayOfNodes (node* p_tree)
{
    // returns array of sorted nods (function used by 'balanceTree' function)
    node* array = new node[countNodes(p_tree)];
    for (int i = 0; i < countNodes(p_tree); i++)
    {
        array[i] = *find_n_node(p_tree,i+1);
    }
    // clearing left and right pointers of each node
    for (int i = 0; i < countNodes(p_tree); i++)
    {
        array[i].p_left = NULL;
        array[i].p_right = NULL;
    }
    return array;
}

node* transformArrayIntoTree (node* array, int indexArray)
{
    // returns pointer to new tree created from array of nodes (function used by 'balanceTree' function)
    // (function divides array into ever smaller chunks and sets middle value of each chunk as a new parent node)
    if (indexArray >= 0)
    {
        node* p_new_tree = new node;
        *p_new_tree = array[indexArray/2];
        
        p_new_tree->p_left = transformArrayIntoTree(array, indexArray/2-1);
        
        array = &array[indexArray/2+1];
        p_new_tree->p_right = transformArrayIntoTree(array, indexArray-indexArray/2-1);
        
        return p_new_tree;
    }
    else return NULL;
}

node* balanceTree (node* p_tree)
{
    // returns pointer to new balanced tree
    
    // creating array of nodes from original tree
    node* array = createArrayOfNodes(p_tree);
    
    // creating new tree
    node* p_new_tree = NULL;
    p_new_tree = transformArrayIntoTree(array, countNodes(p_tree)-1);
    
    // deallocation of array and pointers in original tree
    destroyTree(p_tree);
    delete[] array;
    
    // returning new tree
    return p_new_tree;
}