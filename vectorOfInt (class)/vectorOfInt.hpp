//
//  vectorOfInt.hpp
//  vectorOfInt (class)
//
//  Created by Stefan Węgrzyn on 31.07.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#ifndef vectorOfInt_hpp
#define vectorOfInt_hpp

#include <stdio.h>

namespace custom {

class intNode
{
public:
    intNode ();
    ~intNode ();
    void setValue (const int value);
    int& getValue ();
    int* getPointerToValue ();
    void setNext (intNode* p_node);
    intNode* getNext ();
    void setPrevious (intNode* p_node);
    intNode* getPrevious ();
private:
    int _value;
    intNode* _p_next;
    intNode* _p_previous;
};


class base_iterator
{
public:
    base_iterator ();
    base_iterator& operator= (const base_iterator& other);
    bool operator== (const base_iterator& other);
    bool operator!= (const base_iterator& other);
    int& operator* ();
    bool operator<= (const base_iterator& other);
    bool operator>= (const base_iterator& other);
    void setPointer (intNode* p_node);
    intNode* getPointer ();
    void setPrevious (intNode* p_node);
    intNode* getPrevious ();
    virtual bool operator< (const base_iterator& other) = 0;
    virtual bool operator> (const base_iterator& other) = 0;
    virtual base_iterator& operator++ () = 0;
    virtual base_iterator& operator+ (const int number) = 0;
    virtual base_iterator& operator-- () = 0;
    virtual base_iterator& operator- (const int number) = 0;
    // '= 0' means base class does not supply universal implementation of method (it must be implemented by derived classes)
protected:
    intNode* _pointer;
    intNode* _previous; // points to previous node when _pointer = NULL; otherwise _previous = NULL;
};
    

class vectorOfInt
{
public: class iterator;
public: class reverse_iterator;
    
public:
    vectorOfInt ();
    vectorOfInt (int size);
    vectorOfInt (const vectorOfInt& other);
    vectorOfInt& operator= (const vectorOfInt& other);
    ~vectorOfInt ();
    // element access
    int& at (const int index);
    int& operator[] (const int index);
    int& front ();
    int& back ();
    // iterators
    iterator begin ();
    iterator end ();
    reverse_iterator rbegin ();
    reverse_iterator rend ();
    // capacity
    const int size ();
    const bool empty ();
    // modifiers
    void assign (iterator first, iterator last);
    void push_back (int value);
    void push_front (int value);
    void pop_back ();
    void pop_front ();
    iterator insert (iterator position, const int value);
    iterator insert (iterator position, iterator first, iterator last);
    iterator erase (iterator position);
    iterator erase (iterator first, iterator last);
    void clear ();
private:
    intNode* _findNode (const int index);
    intNode* _p_head;
};


class vectorOfInt::iterator : public base_iterator
{
public:
    bool operator< (const base_iterator& other) override;
    bool operator> (const base_iterator& other) override;
    iterator& operator++ () override;
    iterator& operator+ (const int number) override;
    iterator& operator-- () override;
    iterator& operator- (const int number) override;
};

class vectorOfInt::reverse_iterator : public base_iterator
{
public:
    bool operator< (const base_iterator& other) override;
    bool operator> (const base_iterator& other) override;
    reverse_iterator& operator++ () override;
    reverse_iterator& operator+ (const int number) override;
    reverse_iterator& operator-- () override;
    reverse_iterator& operator- (const int number) override;
};


} // end of namespace

#endif /* vectorOfInt_hpp */