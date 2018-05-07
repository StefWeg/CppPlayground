//
//  main.cpp
//  Hanoi tower solver (recursion)
//
//  Created by Stefan Węgrzyn on 21.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

using namespace std;

struct block
{
    int size;
    block* next_block;
};

void moveBlock (block** fromStack, block** toStack)
{
    block* temporaryPointer = (*fromStack)->next_block;
    
    (*fromStack)->next_block = *toStack;
    *toStack = *fromStack;
    
    *fromStack = temporaryPointer;
}

void displayColumn (block* stack)
{
    if (stack == NULL)
    {
        cout << "|";
        return;
    }
    
    if (stack->next_block != NULL)
    {
        displayColumn (stack->next_block);
    }
    
    cout << stack->size << " ";
    return;
}

// global pointers to stackABC
block** globalPointerToStackA = NULL;
block** globalPointerToStackB = NULL;
block** globalPointerToStackC = NULL;
//

void display ()
{
    displayColumn(*globalPointerToStackA);
    cout << endl;
    displayColumn(*globalPointerToStackB);
    cout << endl;
    displayColumn(*globalPointerToStackC);
    cout << endl;
}

void hanoiSolver (int currentHeight, block** p_stack1, block** p_stack2, block** p_stack3, int* p_movesCounter)
{
    if (currentHeight > 0)
    {
        hanoiSolver (currentHeight-1, p_stack1, p_stack3, p_stack2, p_movesCounter);
        
        moveBlock (p_stack1, p_stack3);
        
        // display
        (*p_movesCounter)++;
        cout << endl << "Move no. " << *p_movesCounter << ":" << endl;
        display ();
        //
        
        hanoiSolver (currentHeight-1, p_stack2, p_stack1, p_stack3, p_movesCounter);
    }
    return;
}

void deallocate (block* stack)
{
    if (stack == NULL)
    {
        return;
    }
    if (stack->next_block != NULL)
    {
        deallocate(stack->next_block);
    }
    delete stack;
    return;
}


int main ()
{
    block* stackA = NULL;
    block* stackB = NULL;
    block* stackC = NULL;
    
    int height = 0;
    int movesCounter = 0;
    
    cout << "Enter the height of the hanoi tower: ";
    cin >> height;
    
    // creating hanoi blocks in stackA
    block* temporaryPointer = NULL;
    for (int i = height; i > 0; i--)
    {
        temporaryPointer = stackA;
        stackA = new block;
        stackA->size = i;
        stackA->next_block = temporaryPointer;
    }
    
    // setting global pointers to stackABC
    globalPointerToStackA = &stackA;
    globalPointerToStackB = &stackB;
    globalPointerToStackC = &stackC;
    
    // first display
    cout << endl << "Original arrangement:" << endl;
    display ();
    
    // solving hanoi
    hanoiSolver(height, &stackA, &stackB, &stackC, &movesCounter);
    
    // deallocate pointers
    deallocate (stackA);
    deallocate (stackB);
    deallocate (stackC);
    
    cout << endl;
    
    return 0;
}
