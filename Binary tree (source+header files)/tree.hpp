//
//  tree.hpp
//  Binary tree (source+header files)
//
//  Created by Stefan Węgrzyn on 29.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include "node.h"

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

#endif /* tree_hpp */
