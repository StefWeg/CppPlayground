//
//  vectorOfInt.cpp
//  vectorOfInt (class)
//
//  Created by Stefan Węgrzyn on 31.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#include "vectorOfInt.hpp"
#include <string>
#include <stdio.h>

namespace custom {

typedef vectorOfInt::iterator iterator;
typedef vectorOfInt::reverse_iterator reverse_iterator;
    
// intNode definitions /////////////////////

intNode::intNode()
    // sets default field values
    : _value(0)
    , _p_previous(NULL)
    , _p_next(NULL)
{}

intNode::~intNode()
{
    // deleting head pointer in vectorOfInt destructor will cause all nodes of linked list to delete one after another till _p_next == NULL ('delete NULL' causes nothing)
    delete _p_next;
}

void intNode::setValue(const int value)
{
    // sets value of node
    _value = value;
}

int& intNode::getValue()
{
    // returns value stored in node
    return _value;
}

void intNode::setNext(intNode* p_node)
{
    // sets pointer to next node
    _p_next = p_node;
}

intNode* intNode::getNext()
{
    // returns pointer to next node
    return _p_next;
}

void intNode::setPrevious(intNode* p_node)
{
    // sets pointer to previous node
    _p_previous = p_node;
}

intNode* intNode::getPrevious()
{
    // returns pointer to previous node
    return _p_previous;
}


// base_iterator definitions /////////////////////

base_iterator::base_iterator()
    // makes pointer point to given node
    : _pointer(NULL)
    , _previous(NULL)
{}

base_iterator& base_iterator::operator= (const base_iterator& other)
{
    // handles assignment
    if (this == &other) return *this; // if iterator is asigned to itself
    _pointer = other._pointer;
    _previous = other._previous;
    return *this;
}

bool base_iterator::operator== (const base_iterator& other)
{
    // handles comparison
    if (_pointer == other._pointer && _previous == other._previous) return true;
    else return false;
}

bool base_iterator::operator!= (const base_iterator& other)
{
    // handles comparison
    return !operator==(other);
}

int& base_iterator::operator*()
{
    // handles dereference of iterator
    if (_pointer == NULL) {std::string error = "cannot dereference end pointer!"; throw error;}
    return _pointer->getValue();
}
    
bool base_iterator::operator<= (const base_iterator& other)
{
    return (operator==(other) || operator<(other));
}
    
bool base_iterator::operator>= (const base_iterator& other)
{
    return (operator==(other) || operator>(other));
}

void base_iterator::setPointer (intNode* p_node)
{
    // makes _pointer point to particular node
    _pointer = p_node;
}

intNode* base_iterator::getPointer ()
{
    // returns _pointer
    return _pointer;
}
    
void base_iterator::setPrevious (intNode* p_node)
{
    // makes _previous point to particular node
    _previous = p_node;
}
    
intNode* base_iterator::getPrevious ()
{
    // returns _previous
    return _previous;
}


// iterator definitions /////////////////////

iterator& iterator::operator++ ()
{
    // handles ++iteration of iterator
    if (_pointer == NULL) {std::string error = "pointing out of range!"; throw error;}
    if (_pointer->getNext() == NULL) {_previous = _pointer;}
    _pointer = _pointer->getNext(); // pointing to next node
    return *this;
}

iterator& iterator::operator+ (const int number)
{
    // handles adding number to iterator
    for (int i = 0; i < number; i++)
    {
        if (_pointer == NULL) {std::string error = "pointing out of range!"; throw error;}
        if (_pointer->getNext() == NULL) {_previous = _pointer;}
        _pointer = _pointer->getNext(); // pointing to (number)th node after the original node
    }
    return *this;
}

iterator& iterator::operator-- ()
{
    // handles --iteration of iterator
    if (_pointer == NULL) { // case when _pointer points to end node
        _pointer = _previous;
        _previous = NULL;
        return *this;
    } else {
        _pointer = _pointer->getPrevious(); // pointing to previous node
        if (_pointer == NULL) {std::string error = "pointing out of range!"; throw error;} // case when _pointer was origianlly pointing to begin node
        return *this;
    }
}

iterator& iterator::operator- (const int number)
{
    // handles subtracing number from iterator
    for (int i = 0; i < number; i++)
    {
        if (_pointer == NULL) { // case when _pointer points to end node
            _pointer = _previous;
            _previous = NULL;
        } else {
            _pointer = _pointer->getPrevious(); // pointing to previous node
            if (_pointer == NULL) {std::string error = "pointing out of range!"; throw error;} // case when _pointer was origianlly pointing to begin node
        }
    }
    return *this;
}
    
bool iterator::operator< (const base_iterator& other)
{
    iterator itr = *this;
    if (itr.getPointer() == NULL) return false; // case when *this is the end iterator from the beginning
    while (true)
    {
        ++itr;
        if (itr == other) return true;
        if (itr.getPointer() == NULL) return false; // if got to end iterator
    }
}
    
bool iterator::operator> (const base_iterator& other)
{
    iterator itr = *this;
    if (itr.getPointer() == NULL && itr != other) return true; // case when *this is the end iterator from the beginning and is not equal to 'other' iterator
    if (itr.getPointer() == NULL && itr == other) return false; // case when *this is the end iterator from the beginning and is equal to 'other' iterator
    if (itr.getPointer()->getPrevious() == NULL) return false; // case when *this begin iterator at the beginning
    while (true)
    {
        --itr;
        if (itr == other) return true;
        if (itr.getPointer()->getPrevious() == NULL) return false; // if got to begin iterator
    }
}


// reverse_iterator definitions /////////////////////

reverse_iterator& reverse_iterator::operator++ ()
{
    // handles ++iteration of iterator
    if (_pointer == NULL) {std::string error = "pointing out of range!"; throw error;}
    if (_pointer->getPrevious() == NULL) {_previous = _pointer;}
    _pointer = _pointer->getPrevious(); // pointing to next node
    return *this;
}
    
reverse_iterator& reverse_iterator::operator+ (const int number)
{
    // handles adding number to iterator
    for (int i = 0; i < number; i++)
    {
        if (_pointer == NULL) {std::string error = "pointing out of range!"; throw error;}
        if (_pointer->getPrevious() == NULL) {_previous = _pointer;}
        _pointer = _pointer->getPrevious(); // pointing to (number)th node after the original node
    }
    return *this;
}

reverse_iterator& reverse_iterator::operator-- ()
{
    // handles --iteration of iterator
    if (_pointer == NULL) { // case when _pointer points to end node
        _pointer = _previous;
        _previous = NULL;
        return *this;
    } else {
        _pointer = _pointer->getNext(); // pointing to previous node
        if (_pointer == NULL) {std::string error = "pointing out of range!"; throw error;} // case when _pointer was origianlly pointing to begin node
        return *this;
    }
}
    
reverse_iterator& reverse_iterator::operator- (const int number)
{
    // handles subtracing number from iterator
    for (int i = 0; i < number; i++)
    {
        if (_pointer == NULL) { // case when _pointer points to end node
            _pointer = _previous;
            _previous = NULL;
        } else {
            _pointer = _pointer->getNext(); // pointing to previous node
            if (_pointer == NULL) {std::string error = "pointing out of range!"; throw error;} // case when _pointer was origianlly pointing to begin node
        }
    }
    return *this;
}

bool reverse_iterator::operator< (const base_iterator& other)
{
    reverse_iterator itr = *this;
    if (itr.getPointer() == NULL) return false; // case when *this is the end iterator from the beginning
    while (true)
    {
        ++itr;
        if (itr == other) return true;
        if (itr.getPointer() == NULL) return false; // if got to end iterator
    }
}

bool reverse_iterator::operator> (const base_iterator& other)
{
    reverse_iterator itr = *this;
    if (itr.getPointer() == NULL && itr != other) return true; // case when *this is the end iterator from the beginning and is not equal to 'other' iterator
    if (itr.getPointer() == NULL && itr == other) return false; // case when *this is the end iterator from the beginning and is equal to 'other' iterator
    while (true)
    {
        --itr;
        if (itr == other) return true;
        if (itr.getPointer()->getPrevious() == NULL) return false; // if got to begin iterator
    }
}


// vectorOfInt definitions /////////////////////

vectorOfInt::vectorOfInt()
    : vectorOfInt(0) // uses constructor with parameter
{}

vectorOfInt::vectorOfInt(int size)
    : _p_head(NULL)
{
    // allocates proper number of connected nodes
    intNode* pointer;
    for (int i = 0; i < size; i++)
    {
        pointer = new intNode;
        pointer->setNext(_p_head);
        pointer->setPrevious(NULL);
        if (_p_head != NULL) _p_head->setPrevious(pointer);
        _p_head = pointer;
    }
}

vectorOfInt::vectorOfInt(const vectorOfInt& other)
    : _p_head(NULL)
{
    // copy constructor
    intNode* temporary = other._p_head;
    if (temporary == NULL) _p_head = temporary;
    else
    {
        // searching last node
        while (temporary->getNext() != NULL) temporary = temporary->getNext();
        // creating new local linked list taking values from linked list from other vectorOfInt
        _p_head = NULL;
        while (temporary != NULL)
        {
            intNode* newNode = new intNode;
            newNode->setPrevious(NULL);
            newNode->setValue(temporary->getValue());
            newNode->setNext(_p_head);
            if (_p_head != NULL) _p_head->setPrevious(newNode);
            _p_head = newNode;
            temporary = temporary->getPrevious();
        }
    }
}

vectorOfInt& vectorOfInt::operator= (const vectorOfInt& other)
{
    // handles assignment
    if (this == &other) return *this; // if vectorOfInt is asigned to itself
    intNode* temporary = other._p_head;
    if (temporary == NULL) {_p_head = temporary; return *this;}
    // searching last node
    while (temporary->getNext() != NULL)
    {
        temporary = temporary->getNext();
    }
    // creating new local linked list taking values from linked list from other vectorOfInt
    _p_head = NULL;
    while (temporary != NULL)
    {
        intNode* newNode = new intNode;
        newNode->setPrevious(NULL);
        newNode->setValue(temporary->getValue());
        newNode->setNext(_p_head);
        if (_p_head != NULL) _p_head->setPrevious(newNode);
        _p_head = newNode;
        temporary = temporary->getPrevious();
    }
    return *this;
}

vectorOfInt::~vectorOfInt()
{
    // destructor
    delete _p_head; // deleting head pointer trigger destruction of all nodes (look intNode destructor)
}

// element access //

int& vectorOfInt::at(const int index)
{
    // returns reference to value of node with given index
    return _findNode(index)->getValue();
}

int& vectorOfInt::operator[] (const int index)
{
    // returns reference to value of node with given index
    return _findNode(index)->getValue();
}

int& vectorOfInt::front()
{
    // returns reference to value of first node
    return _findNode(0)->getValue();
}

int& vectorOfInt::back()
{
    // returns reference to value of last node
    int index = this->size() - 1;
    return _findNode(index)->getValue();
}

// iterators //

iterator vectorOfInt::begin()
{
    // returns iterator to first element of vectorOfInt
    iterator begin;
    begin.setPointer(this->_findNode(0)); // index of the first element
    return begin;
}

iterator vectorOfInt::end ()
{
    // returns iterator to one after last element of vectorOfInt
    int max_index = this->size()-1;
    iterator end;
    end.setPointer(this->_findNode(max_index+1)); // index of the last element + 1
    end.setPrevious(this->_findNode(max_index)); // index of the last element
    return end;
}

reverse_iterator vectorOfInt::rbegin()
{
    // returns reverse_iterator to last element of vectorOfInt
    int index = this->size() - 1;
    reverse_iterator rbegin;
    rbegin.setPointer(this->_findNode(index)); // index of the last element
    return rbegin;
}

reverse_iterator vectorOfInt::rend()
{
    // returns reverse_iterator to one before first element of vectorOfInt
    reverse_iterator rend;
    rend.setPointer(this->_findNode(-1)); // index of the first element - 1
    rend.setPrevious(this->_findNode(0)); // index of the first element
    return rend;
}

// capacity //

const int vectorOfInt::size()
{
    // returns size of vector (number of nodes)
    int counter = 0;
    intNode* pointer = _p_head;
    while (pointer != NULL)
    {
        pointer = pointer->getNext();
        counter++;
    }
    return counter;
}

const bool vectorOfInt::empty()
{
    // returns true when vector is empty
    if (_p_head == NULL) return true;
    else return false;
}

// modifiers //

void vectorOfInt::assign(iterator first, iterator last)
{
    // makes vector store values of another vector
    // first is begin iterator and last is end iterator (pointing behind last element)
    // deleting original linked list
    delete _p_head;
    // creating new linked list from beginning
    intNode* p_end_node = new intNode;
    p_end_node->setPrevious(NULL);
    p_end_node->setValue(first.getPointer()->getValue());
    p_end_node->setNext(NULL);
    intNode* temporary = p_end_node;
    for (first = first + 1; first != last; ++first)
    {
        temporary = new intNode;
        temporary->setPrevious(p_end_node);
        temporary->setValue(first.getPointer()->getValue());
        temporary->setNext(NULL);
        p_end_node->setNext(temporary);
        p_end_node = temporary;
    }
    // setting new _p_head (temporary here points to ultimate p_end_node)
    while (temporary->getPrevious() != NULL)
    {
        temporary = temporary->getPrevious();
    }
    _p_head = temporary; // temporary points now to first node
}

void vectorOfInt::push_back(int value)
{
    // adds element at the end
    intNode* newNode = new intNode;
    // finding end node
    if (_p_head == NULL)
    {
        newNode->setPrevious(NULL);
        newNode->setValue(value);
        newNode->setNext(NULL);
        _p_head = newNode;
        return;
    }
    intNode* p_end_node = _p_head;
    while (p_end_node->getNext() != NULL)
    {
        p_end_node = p_end_node->getNext();
    }
    // adding new node at the end
    p_end_node->setNext(newNode);
    newNode->setPrevious(p_end_node);
    newNode->setValue(value);
    newNode->setNext(NULL);
}

void vectorOfInt::push_front(int value)
{
    // adds element at the front
    intNode* newNode = new intNode;
    newNode->setPrevious(NULL);
    newNode->setValue(value);
    newNode->setNext(_p_head);
    _p_head->setPrevious(newNode);
    _p_head = newNode;
}

void vectorOfInt::pop_back()
{
    // deletes last element
    if (_p_head == NULL) return;
    // finding end node
    intNode* p_end_node = _p_head;
    while (p_end_node->getNext() != NULL)
    {
        p_end_node = p_end_node->getNext();
    }
    // deleting node at the end
    p_end_node->getPrevious()->setNext(NULL);
    delete p_end_node; // because last node is pointing to NULL intNode destructor won't delete other nodes
}

void vectorOfInt::pop_front()
{
    // deletes first element
    if (_p_head == NULL) return;
    intNode* secondNode = _p_head->getNext();
    if (secondNode != NULL) secondNode->setPrevious(NULL);
    _p_head->setNext(NULL); // to prevent from deleting all nodes (look intNode destructor)
    delete _p_head;
    _p_head = secondNode;
}

iterator vectorOfInt::insert (iterator position, const int value)
{
    // inserts node with given value before the node pointed to by iterator
    // returns iterator pointing to inserted node
    intNode* currentNode = position.getPointer();
    if (currentNode == NULL) // case when position is end iterator
    {
        push_back(value);
        // finding end node
        intNode* p_end_node = _p_head;
        while (p_end_node->getNext() != NULL) p_end_node = p_end_node->getNext();
        // creating iterator to return
        iterator end;
        end.setPointer(p_end_node);
        return end;
    }
    intNode* previousNode = position.getPointer()->getPrevious();
    if (previousNode == NULL) {push_front(value); return --position;} // case when position is begin iterator
    intNode* newNode = new intNode;
    previousNode->setNext(newNode);
    newNode->setPrevious(previousNode);
    newNode->setValue(value);
    newNode->setNext(currentNode);
    currentNode->setPrevious(newNode);
    return --position;
}
    
iterator vectorOfInt::insert (iterator position, iterator first, iterator last)
{
    // insertrs range of nodes before the node pointed by position iterator
    // first is pointing to first element to insert and last is pointing behind last element to insert
    // returns iterator pointing to the first of inserted nodes
    if (first >= last) return position;
    intNode* currentNode = position.getPointer();
    if (currentNode == NULL) // case when position is end iterator
    {
        // finding last node
        intNode* temporary = _p_head;
        while (temporary->getNext() != NULL) temporary = temporary->getNext();
        // appending new linked list
        iterator itr = first;
        while (itr != last)
        {
            intNode* newNode = new intNode;
            temporary->setNext(newNode);
            newNode->setPrevious(temporary);
            newNode->setValue(itr.getPointer()->getValue());
            newNode->setNext(NULL);
            temporary = newNode;
            ++itr;
        }
        return first;
    }
    intNode* previousNode = position.getPointer()->getPrevious();
    if (previousNode == NULL) // case when position is begin iterator
    {
        // creating new linked list at the front
        iterator itr = first;
        intNode* temporary = NULL;
        intNode* p_new_head = NULL;
        while (itr != last)
        {
            intNode* newNode = new intNode;
            if (temporary != NULL) temporary->setNext(newNode);
            newNode->setPrevious(temporary);
            newNode->setValue(itr.getPointer()->getValue());
            newNode->setNext(NULL);
            if (temporary == NULL) p_new_head = newNode;
            temporary = newNode;
            ++itr;
        }
        temporary->setNext(_p_head);
        _p_head = p_new_head;
        return first;
    }
    // creating new linked list inside existing
    iterator itr = first;
    intNode* temporary = previousNode;
    while (itr != last)
    {
        intNode* newNode = new intNode;
        temporary->setNext(newNode);
        newNode->setPrevious(temporary);
        newNode->setValue(itr.getPointer()->getValue());
        newNode->setNext(NULL);
        temporary = newNode;
        ++itr;
    }
    temporary->setNext(currentNode);
    currentNode->setPrevious(temporary);
    return first;
}

iterator vectorOfInt::erase (iterator position)
{
    // deletes element on given position
    // returns iterator pointing to element that followed the last element erased
    intNode* currentNode = position.getPointer();
    if (currentNode == NULL) return this->end(); // case when position is end iterator
    intNode* previousNode = position.getPointer()->getPrevious();
    if (previousNode == NULL) {pop_front(); return this->begin();} // case when position is begin iterator
    intNode* nextNode = position.getPointer()->getNext();
    if (nextNode == NULL) {pop_back(); return this->end();} // case when position points to last element
    ++position; // preparing iterator for return
    previousNode->setNext(nextNode);
    nextNode->setPrevious(previousNode);
    currentNode->setNext(NULL); // to prevent from deleting all nodes (look intNode destructor)
    delete currentNode;
    return position;
}

iterator vectorOfInt::erase (iterator first, iterator last)
{
    // deletes given range of elements
    // first is pointing to first element to delete and last is pointing behind last element to delete
    // returns iterator pointing to element that followed the last element erased
    if (first >= last) return last; // case when iterators are in wrong order
    intNode* firstToDeleteNode = first.getPointer();
    if (firstToDeleteNode == NULL) return last; // case when first is end iterator
    intNode* beforeRangeNode = first.getPointer()->getPrevious();
    if (beforeRangeNode == NULL) {_p_head = last.getPointer();} // case when first is begin iterator
    intNode* afterRangeNode = last.getPointer();
    if (afterRangeNode == NULL) // case when last is end iterator
    {
        if (beforeRangeNode != NULL) beforeRangeNode->setNext(NULL);
        delete firstToDeleteNode; // deleting all nodes from firstToDeleteNode (look intNode destructor)
        return last;
    }
    // other case
    intNode* lastToDeleteNode = last.getPointer()->getPrevious();
    if (beforeRangeNode != NULL) beforeRangeNode->setNext(afterRangeNode);
    afterRangeNode->setPrevious(beforeRangeNode);
    lastToDeleteNode->setNext(NULL); // to prevent from deleting all nodes (look intNode destructor)
    delete firstToDeleteNode;
    return last;
}

void vectorOfInt::clear()
{
    // deletes all nodes
    delete _p_head; // deleting head pointer trigger destruction of all nodes (look intNode destructor)
    _p_head = NULL;
}

// private //

intNode* vectorOfInt::_findNode (const int index)
{
    if (index == -1) return _p_head->getPrevious();
    intNode* pointer = _p_head;
    for (int i = 0; i < index; i++)
    {
        pointer = pointer->getNext();
    }
    return pointer;
}
    
} // end of namespace