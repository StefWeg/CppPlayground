//
//  main.cpp
//  Binary tree (basic functions)
//
//  Created by Stefan Węgrzyn on 24.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

using namespace std;

struct node
{
    int key_value;
    node* p_left;
    node* p_right;
};

node* insert (node* p_tree, int key);
node* search (node* p_tree, int key);
void destroyTree (node* p_tree);
node* find_max (node* p_tree);
node* remove_max_node (node* p_tree, node* p_max_node);
node* remove (node* p_tree, int key);
void display (node* p_tree);
void displayReversed (node* p_tree);
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


node* insert (node* p_tree, int key)
{
    // returns pointer to the tree
    if (p_tree == NULL)
    {
        node* p_newTree = new node;
        p_newTree->key_value = key;
        p_newTree->p_left = NULL;
        p_newTree->p_right = NULL;
        return p_newTree;
    }
    
    if (key < p_tree->key_value)
    {
        p_tree->p_left = insert (p_tree->p_left, key);
    }
    else if (key > p_tree->key_value)
    {
        p_tree->p_right = insert (p_tree->p_right, key);
    }
    return p_tree; // when key == p_tree->key_value function will hit return and do nothing overall
}

node* search (node* p_tree, int key)
{
    // returns pointer to node with key_value == key
    if (p_tree == NULL)
    {
        return NULL;
    }
    if (key == p_tree->key_value)
    {
        return p_tree;
    }
    else if (key < p_tree->key_value)
    {
        return search (p_tree->p_left, key);
    }
    else
    {
        return search (p_tree->p_right, key);
    }
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

node* remove (node* p_tree, int key)
{
    // returns pointer to the tree
    if (p_tree == NULL)
    {
        return NULL;
    }
    if (key == p_tree->key_value)
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
    else if (key < p_tree->key_value)
    {
        p_tree->p_left = remove (p_tree->p_left, key);
    }
    else
    {
        p_tree->p_right = remove (p_tree->p_right, key);
    }
    return p_tree;
}

void display (node* p_tree)
{
    if (p_tree != NULL)
    {
        display(p_tree->p_left);
        cout << p_tree->key_value << " "; // desplaying key_value after left subtree and before right subtree
        display(p_tree->p_right);
    }
    return; // simply returns when p_tree == NULL
}

void displayReversed (node* p_tree)
{
    if (p_tree != NULL)
    {
        displayReversed(p_tree->p_right);
        cout << p_tree->key_value << " "; // desplaying key_value after left subtree and before right subtree
        displayReversed(p_tree->p_left);
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
    if (p_tree->p_left == NULL && (p_tree->p_right)->key_value > p_tree->key_value)
    {
        if (checkTreeOrganization(p_tree->p_right))
        {
            return true;
        }
    }
    if ((p_tree->p_left)->key_value < p_tree->key_value && p_tree->p_right == NULL)
    {
        if (checkTreeOrganization(p_tree->p_left))
        {
            return true;
        }
    }
    if ((p_tree->p_left)->key_value < p_tree->key_value && (p_tree->p_right)->key_value > p_tree->key_value)
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
        if (find_n_node(p_tree, countNodes(p_tree)/2)->key_value == p_tree->key_value) return true;
        else if (find_n_node(p_tree, (countNodes(p_tree)/2)+1)->key_value == p_tree->key_value) return true;
        else return false;
    }
    else // odd number of nodes
    {
        if (find_n_node(p_tree, (countNodes(p_tree)/2)+1)->key_value == p_tree->key_value) return true;
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
    // returns array of sorted nods
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
    // returns pointer to new tree created from array of nodes
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