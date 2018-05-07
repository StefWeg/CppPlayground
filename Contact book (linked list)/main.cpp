//
//  main.cpp
//  Contact book (linked list) v2
//
//  Created by Stefan Węgrzyn on 18.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include <iostream>

using namespace std;

struct friendData
{
    string name;
    int daysSinceLastContact;
    friendData* next_friend;
};


/// HANDLING LINKED LIST
void deleteFriend (friendData** p_friendList, int position);
void insertFriend (friendData** p_friendList, friendData** p_friendInserted, int position);
void sortFriendList (friendData** p_friendList);
void deallocateLinkedList (friendData* friendList);

/// MENU FUNCTIONS
void addNewFriend (friendData** p_friendList);
void deleteExistingFriend (friendData** p_friendList);
void updateTime (friendData** p_friendList);
void displayFriendList (friendData** p_friendList);


int main ()
{
    friendData* friendList = NULL;
    
    string input;
    int chosenOption = 0;
    
    do
    {
        cout << "MENU:" << endl;
        cout << "1. Add new friend" << endl;
        cout << "2. Delete a friend" << endl;
        cout << "3. Update time of the last contact" << endl;
        cout << "4. Display list of friends" << endl;
        cout << "5. End of program" << endl;
        cout << "Choose an option: ";
        
        getline(cin, input, '\n');
        
        // checking if input is int
        try
        {
            chosenOption = stoi (input);
        }
        catch (...)  // handles exceptions
        {
            cout << "Wrong input!" << endl << endl;
            continue;
        }
        
        // handling user's request
        switch (chosenOption)
        {
            case 1:
            {
                addNewFriend (&friendList);
                break;
            }
            case 2:
            {
                deleteExistingFriend (&friendList);
                break;
            }
            case 3:
            {
                updateTime (&friendList);
                break;
            }
            case 4:
            {
                displayFriendList (&friendList);
                break;
            }
            case 5:
            {
                break;
            }
            default:
            {
                cout << "There is no such option!" << endl << endl;
                continue;
                break;
            }
        }
        
    } while (chosenOption != 5);
    
    // deallocation of pointers
    if (friendList != NULL) // when friendList == NULL deallocation is not needed
    {
        deallocateLinkedList(friendList);
    }
    
    return 0;
}


//// HANDLING LINKED LIST ////////////////////////////////////////////

void deleteFriend (friendData** p_friendList, int position)
{
    int counter = 1;
    friendData* previousFriend = *p_friendList;
    friendData* currentFriend = (*p_friendList)->next_friend;
    
    // case: position = 1
    if (position == 1)
    {
        delete previousFriend;
        *p_friendList = currentFriend;
        return;
    }
    
    // case: position > 1
    while (currentFriend != NULL)
    {
        counter++;
        
        if (counter == position)
        {
            previousFriend->next_friend = currentFriend->next_friend;
            delete currentFriend;
            return;
        }
        
        previousFriend = currentFriend;
        currentFriend = currentFriend->next_friend;
    }
    
    // no such position
    return;
}


void insertFriend (friendData** p_friendList, friendData** p_friendInserted, int position)
{
    // case: position = 1
    if (position == 1)
    {
        (*p_friendInserted)->next_friend = *p_friendList;
        *p_friendList = *p_friendInserted;
        return;
    }
    
    // case: position > 1
    int counter = 1;
    friendData* previousFriend = *p_friendList;
    friendData* currentFriend = (*p_friendList)->next_friend;
    
    while (currentFriend != NULL)
    {
        counter++;
        
        if (counter == position)
        {
            previousFriend->next_friend = *p_friendInserted;
            (*p_friendInserted)->next_friend = currentFriend;
            return;
        }
        
        previousFriend = currentFriend;
        currentFriend = currentFriend->next_friend;
    }
    
    // case: position outside the list (appending inserted friend at the end of the list)
    previousFriend->next_friend = *p_friendInserted; // here previousFriend is last valid list element
    (*p_friendInserted)->next_friend = currentFriend; // here currentFriend == NULL
    return;
}


void sortFriendList (friendData** p_friendList)
{
    // case: inserting empty or one-element linked list into function
    if (*p_friendList == NULL || (*p_friendList)->next_friend == NULL)
    {
        return;
    }
    
    // sorting by growing number of daysSinceLastContact
    friendData* currentFriend = NULL;
    int indicatorOfFlip = 1;
    int counter = 0;
    
    while (indicatorOfFlip != 0)
    {
        currentFriend = *p_friendList;
        indicatorOfFlip = 0;
        counter = 0;
        
        while (currentFriend->next_friend != NULL)
        {
            counter++; // counting index' of curentFriend on the list
            
            if ((currentFriend->next_friend)->daysSinceLastContact < currentFriend->daysSinceLastContact)
            {
                indicatorOfFlip++; // counting flips
                
                friendData* temporary = new friendData; // needed as curentFriend is going to be deleted
                *temporary = *currentFriend;
                
                deleteFriend(p_friendList, counter);
                insertFriend(p_friendList, &temporary, counter+1);
                
                currentFriend = temporary;
                continue;
            }
            
            currentFriend = currentFriend->next_friend;
        }
    }
    
    return;
}


void deallocateLinkedList (friendData* friendList)
{
    if (friendList->next_friend != NULL)
    {
        deallocateLinkedList(friendList->next_friend);  // recursion !
        delete friendList;
    }
    else
    {
        delete friendList;
    }
}


//// MENU FUNCTIONS ////////////////////////////////////////////

void addNewFriend (friendData** p_friendList)
{
    friendData* newFriend = new friendData;
    
    cout << endl << "Enter friend's name: ";
    getline(cin, newFriend->name, '\n');
    
    
    string input;
    do
    {
        cout << "Enter number of days since last contact: ";
        getline(cin, input, '\n');
        
        try  // checking if input is int
        {
            newFriend->daysSinceLastContact = stoi (input);
        }
        catch (...)  // handles exceptions
        {
            cout << "Wrong input!" << endl << endl;
            return;
        }
    } while (newFriend->daysSinceLastContact < 0);  // enforcing logically correct input
    
    cout << endl;
    
    insertFriend(p_friendList, &newFriend, 1);
    
    return;
}


void deleteExistingFriend (friendData** p_friendList)
{
    // case of inserting empty linked list into function
    if (*p_friendList == NULL)
    {
        cout << endl << "No friends to delete!" << endl << endl;
        return;
    }
    
    // prompting user for name of friend to delete
    string friendToDelete;
    
    cout << endl << "Enter the name of the friend: ";
    getline(cin, friendToDelete, '\n');
    
    // finding indeks of friend on the list
    friendData* currentFriend = *p_friendList;
    int counter = 0;
    
    while (currentFriend != NULL)
    {
        counter++;
        
        if (currentFriend->name == friendToDelete)
        {
            deleteFriend(p_friendList, counter);
            
            cout << "Friend successfully deleted!" << endl << endl;
            return;
        }
        
        currentFriend = currentFriend->next_friend;
    }
    
    // if program gets here it means there is no such friend
    cout << "There is no such friend in your contact book!" << endl << endl;
    return;
}


void updateTime (friendData** p_friendList)
{
    // prompting user for name of friend to update
    string friendToUpdate;
    
    cout << endl << "Enter the name of the friend: ";
    getline(cin, friendToUpdate, '\n');
    
    // finding friend and updating time
    friendData* currentFriend = *p_friendList;
    while (currentFriend != NULL)
    {
        if (currentFriend->name == friendToUpdate)
        {
            string input;
            do
            {
                cout << "Enter number of days since last contact: ";
                getline(cin, input, '\n');
                
                try  // checking if input is int
                {
                    currentFriend->daysSinceLastContact = stoi (input);
                }
                catch (...)  // handles exceptions
                {
                    cout << "Wrong input!" << endl;
                    return;
                }
            } while (currentFriend->daysSinceLastContact < 0); // enforcing logically correct input
            
            cout << "Time of last contact successfully updated!" << endl << endl;
            return;
        }
        
        currentFriend = currentFriend->next_friend;
    }
    
    // if program gets here it means there is no such friend
    cout << "There is no such friend in your contact book!" << endl << endl;
}


void displayFriendList (friendData** p_friendList)
{
    sortFriendList(p_friendList);
    
    cout << endl;
    
    friendData* currentFriend = *p_friendList;
    
    if (currentFriend == NULL)
    {
        cout << "No friends to display!" << endl;
    }
    
    while (currentFriend != NULL)
    {
        cout << "Name: " << currentFriend->name << endl;
        cout << "last contact " << currentFriend->daysSinceLastContact << " days ago" << endl;
        
        currentFriend = currentFriend->next_friend;
    }
    
    cout << endl;
}
