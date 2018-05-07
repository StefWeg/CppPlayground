//
//  vector.hpp
//  vector replacement (template class)
//
//  Created by Stefan Węgrzyn on 10.08.2016.
//  Copyright © 2016 Stefan Węgrzyn. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

#include <stdio.h>
#include <string>

namespace custom {
    
    template <typename T>
    class intNode
    {
    public:
        intNode ();
        ~intNode ();
        void setValue (const T value);
        T& getValue ();
        T* getPointerToValue ();
        void setNext (intNode<T>* p_node);
        intNode<T>* getNext ();
        void setPrevious (intNode<T>* p_node);
        intNode<T>* getPrevious ();
    private:
        T _value;
        intNode<T>* _p_next;
        intNode<T>* _p_previous;
    };
    
    
    template <typename T>
    class base_iterator
    {
    public:
        base_iterator ();
        base_iterator<T>& operator= (const base_iterator<T>& other);
        bool operator== (const base_iterator<T>& other);
        bool operator!= (const base_iterator<T>& other);
        T& operator* ();
        bool operator<= (const base_iterator<T>& other);
        bool operator>= (const base_iterator<T>& other);
        void setPointer (intNode<T>* p_node);
        intNode<T>* getPointer ();
        void setPrevious (intNode<T>* p_node);
        intNode<T>* getPrevious ();
        virtual bool operator< (const base_iterator<T>& other) = 0;
        virtual bool operator> (const base_iterator<T>& other) = 0;
        virtual base_iterator<T>& operator++ () = 0;
        virtual base_iterator<T>& operator+ (const int number) = 0;
        virtual base_iterator<T>& operator-- () = 0;
        virtual base_iterator<T>& operator- (const int number) = 0;
        // '= 0' means base class does not supply universal implementation of method (it must be implemented by derived classes)
    protected:
        intNode<T>* _pointer;
        intNode<T>* _previous; // points to previous node when _pointer = NULL; otherwise _previous = NULL;
    };
    
    
    template <typename T>
    class iterator : public base_iterator<T>
    {
    public:
        bool operator< (const base_iterator<T>& other) override;
        bool operator> (const base_iterator<T>& other) override;
        iterator<T>& operator++ () override;
        iterator<T>& operator+ (const int number) override;
        iterator<T>& operator-- () override;
        iterator<T>& operator- (const int number) override;
    };
    
    template <typename T>
    class reverse_iterator : public base_iterator<T>
    {
    public:
        bool operator< (const base_iterator<T>& other) override;
        bool operator> (const base_iterator<T>& other) override;
        reverse_iterator<T>& operator++ () override;
        reverse_iterator<T>& operator+ (const int number) override;
        reverse_iterator<T>& operator-- () override;
        reverse_iterator<T>& operator- (const int number) override;
     };
    
    
    template <typename T>
    class vector
    {
    public: typedef iterator<T> iterator;
    public: typedef reverse_iterator<T> reverse_iterator;
    
    /*public: class iterator : public base_iterator<T>
            {
            public:
                bool operator< (const base_iterator<T>& other) override;
                bool operator> (const base_iterator<T>& other) override;
                iterator& operator++ () override;
                iterator& operator+ (const int number) override;
                iterator& operator-- () override;
                iterator& operator- (const int number) override;
            };
    public: class reverse_iterator : public base_iterator<T>
            {
            public:
                bool operator< (const base_iterator<T>& other) override;
                bool operator> (const base_iterator<T>& other) override;
                reverse_iterator& operator++ () override;
                reverse_iterator& operator+ (const int number) override;
                reverse_iterator& operator-- () override;
                reverse_iterator& operator- (const int number) override;
            };*/
        
    public:
        vector ();
        vector (int size);
        vector (const vector& other);
        vector& operator= (const vector& other);
        ~vector ();
        // element access
        T& at (const int index);
        T& operator[] (const int index);
        T& front ();
        T& back ();
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
        void push_back (T value);
        void push_front (T value);
        void pop_back ();
        void pop_front ();
        iterator insert (iterator position, const T value);
        iterator insert (iterator position, iterator first, iterator last);
        iterator erase (iterator position);
        iterator erase (iterator first, iterator last);
        void clear ();
    private:
        intNode<T>* _findNode (const int index);
        intNode<T>* _p_head;
    };
    
    
    // intNode definitions /////////////////////
    
    template <typename T>
    intNode<T>::intNode()
    // sets default field values
    : _value(0)
    , _p_previous(NULL)
    , _p_next(NULL)
    {}
    
    template <typename T>
    intNode<T>::~intNode()
    {
        // deleting head pointer in vectorOfInt destructor will cause all nodes of linked list to delete one after another till _p_next == NULL ('delete NULL' causes nothing)
        delete _p_next;
    }
    
    template <typename T>
    void intNode<T>::setValue(const T value)
    {
        // sets value of node
        _value = value;
    }
    
    template <typename T>
    T& intNode<T>::getValue()
    {
        // returns value stored in node
        return _value;
    }
    
    template <typename T>
    void intNode<T>::setNext(intNode<T>* p_node)
    {
        // sets pointer to next node
        _p_next = p_node;
    }
    
    template <typename T>
    intNode<T>* intNode<T>::getNext()
    {
        // returns pointer to next node
        return _p_next;
    }
    
    template <typename T>
    void intNode<T>::setPrevious(intNode<T>* p_node)
    {
        // sets pointer to previous node
        _p_previous = p_node;
    }
    
    template <typename T>
    intNode<T>* intNode<T>::getPrevious()
    {
        // returns pointer to previous node
        return _p_previous;
    }
    
    
    // base_iterator definitions /////////////////////
    
    template <typename T>
    base_iterator<T>::base_iterator()
    // makes pointer point to given node
    : _pointer(NULL)
    , _previous(NULL)
    {}
    
    template <typename T>
    base_iterator<T>& base_iterator<T>::operator= (const base_iterator<T>& other)
    {
        // handles assignment
        if (this == &other) return *this; // if iterator is asigned to itself
        _pointer = other._pointer;
        _previous = other._previous;
        return *this;
    }
    
    template <typename T>
    bool base_iterator<T>::operator== (const base_iterator<T>& other)
    {
        // handles comparison
        if (_pointer == other._pointer && _previous == other._previous) return true;
        else return false;
    }
    
    template <typename T>
    bool base_iterator<T>::operator!= (const base_iterator<T>& other)
    {
        // handles comparison
        return !operator==(other);
    }
    
    template <typename T>
    T& base_iterator<T>::operator*()
    {
        // handles dereference of iterator
        if (_pointer == NULL) {std::string error = "cannot dereference end pointer!"; throw error;}
        return _pointer->getValue();
    }
    
    template <typename T>
    bool base_iterator<T>::operator<= (const base_iterator<T>& other)
    {
        return (operator==(other) || operator<(other));
    }
    
    template <typename T>
    bool base_iterator<T>::operator>= (const base_iterator<T>& other)
    {
        return (operator==(other) || operator>(other));
    }
    
    template <typename T>
    void base_iterator<T>::setPointer (intNode<T>* p_node)
    {
        // makes _pointer point to particular node
        _pointer = p_node;
    }
    
    template <typename T>
    intNode<T>* base_iterator<T>::getPointer ()
    {
        // returns _pointer
        return _pointer;
    }
    
    template <typename T>
    void base_iterator<T>::setPrevious (intNode<T>* p_node)
    {
        // makes _previous point to particular node
        _previous = p_node;
    }
    
    template <typename T>
    intNode<T>* base_iterator<T>::getPrevious ()
    {
        // returns _previous
        return _previous;
    }
    
    
    // iterator definitions /////////////////////
    
    template <typename T>
    iterator<T>& iterator<T>::operator++ ()
    {
        // handles ++iteration of iterator
        if (this->_pointer == NULL) {std::string error = "pointing out of range!"; throw error;}
        if (this->_pointer->getNext() == NULL) {this->_previous = this->_pointer;}
        this->_pointer = this->_pointer->getNext(); // pointing to next node
        return *this;
    }
    
    template <typename T>
    iterator<T>& iterator<T>::operator+ (const int number)
    {
        // handles adding number to iterator
        for (int i = 0; i < number; i++)
        {
            if (this->_pointer == NULL) {std::string error = "pointing out of range!"; throw error;}
            if (this->_pointer->getNext() == NULL) {this->_previous = this->_pointer;}
            this->_pointer = this->_pointer->getNext(); // pointing to (number)th node after the original node
        }
        return *this;
    }
    
    template <typename T>
    iterator<T>& iterator<T>::operator-- ()
    {
        // handles --iteration of iterator
        if (this->_pointer == NULL) { // case when _pointer points to end node
            this->_pointer = this->_previous;
            this->_previous = NULL;
            return *this;
        } else {
            this->_pointer = this->_pointer->getPrevious(); // pointing to previous node
            if (this->_pointer == NULL) {std::string error = "pointing out of range!"; throw error;} // case when _pointer was origianlly pointing to begin node
            return *this;
        }
    }
    
    template <typename T>
    iterator<T>& iterator<T>::operator- (const int number)
    {
        // handles subtracing number from iterator
        for (int i = 0; i < number; i++)
        {
            if (this->_pointer == NULL) { // case when _pointer points to end node
                this->_pointer = this->_previous;
                this->_previous = NULL;
            } else {
                this->_pointer = this->_pointer->getPrevious(); // pointing to previous node
                if (this->_pointer == NULL) {std::string error = "pointing out of range!"; throw error;} // case when _pointer was origianlly pointing to begin node
            }
        }
        return *this;
    }
    
    template <typename T>
    bool iterator<T>::operator< (const base_iterator<T>& other)
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
    
    template <typename T>
    bool iterator<T>::operator> (const base_iterator<T>& other)
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
    
    template <typename T>
    reverse_iterator<T>& reverse_iterator<T>::operator++ ()
    {
        // handles ++iteration of iterator
        if (this->_pointer == NULL) {std::string error = "pointing out of range!"; throw error;}
        if (this->_pointer->getPrevious() == NULL) {this->_previous = this->_pointer;}
        this->_pointer = this->_pointer->getPrevious(); // pointing to next node
        return *this;
    }
    
    template <typename T>
    reverse_iterator<T>& reverse_iterator<T>::operator+ (const int number)
    {
        // handles adding number to iterator
        for (int i = 0; i < number; i++)
        {
            if (this->_pointer == NULL) {std::string error = "pointing out of range!"; throw error;}
            if (this->_pointer->getPrevious() == NULL) {this->_previous = this->_pointer;}
            this->_pointer = this->_pointer->getPrevious(); // pointing to (number)th node after the original node
        }
        return *this;
    }
    
    template <typename T>
    reverse_iterator<T>& reverse_iterator<T>::operator-- ()
    {
        // handles --iteration of iterator
        if (this->_pointer == NULL) { // case when _pointer points to end node
            this->_pointer = this->_previous;
            this->_previous = NULL;
            return *this;
        } else {
            this->_pointer = this->_pointer->getNext(); // pointing to previous node
            if (this->_pointer == NULL) {std::string error = "pointing out of range!"; throw error;} // case when _pointer was origianlly pointing to begin node
            return *this;
        }
    }
    
    template <typename T>
    reverse_iterator<T>& reverse_iterator<T>::operator- (const int number)
    {
        // handles subtracing number from iterator
        for (int i = 0; i < number; i++)
        {
            if (this->_pointer == NULL) { // case when _pointer points to end node
                this->_pointer = this->_previous;
                this->_previous = NULL;
            } else {
                this->_pointer = this->_pointer->getNext(); // pointing to previous node
                if (this->_pointer == NULL) {std::string error = "pointing out of range!"; throw error;} // case when _pointer was origianlly pointing to begin node
            }
        }
        return *this;
    }
    
    template <typename T>
    bool reverse_iterator<T>::operator< (const base_iterator<T>& other)
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
    
    template <typename T>
    bool reverse_iterator<T>::operator> (const base_iterator<T>& other)
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
    
    template <typename T>
    vector<T>::vector()
    : vector(0) // uses constructor with parameter
    {}
    
    template <typename T>
    vector<T>::vector(int size)
    : _p_head(NULL)
    {
        // allocates proper number of connected nodes
        intNode<T>* pointer;
        for (int i = 0; i < size; i++)
        {
            pointer = new intNode<T>;
            pointer->setNext(_p_head);
            pointer->setPrevious(NULL);
            if (_p_head != NULL) _p_head->setPrevious(pointer);
            _p_head = pointer;
        }
    }
    
    template <typename T>
    vector<T>::vector(const vector& other)
    : _p_head(NULL)
    {
        // copy constructor
        intNode<T>* temporary = other._p_head;
        if (temporary == NULL) _p_head = temporary;
        else
        {
            // searching last node
            while (temporary->getNext() != NULL) temporary = temporary->getNext();
            // creating new local linked list taking values from linked list from other vectorOfInt
            _p_head = NULL;
            while (temporary != NULL)
            {
                intNode<T>* newNode = new intNode<T>;
                newNode->setPrevious(NULL);
                newNode->setValue(temporary->getValue());
                newNode->setNext(_p_head);
                if (_p_head != NULL) _p_head->setPrevious(newNode);
                _p_head = newNode;
                temporary = temporary->getPrevious();
            }
        }
    }
    
    template <typename T>
    vector<T>& vector<T>::operator= (const vector<T>& other)
    {
        // handles assignment
        if (this == &other) return *this; // if vectorOfInt is asigned to itself
        intNode<T>* temporary = other._p_head;
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
            intNode<T>* newNode = new intNode<T>;
            newNode->setPrevious(NULL);
            newNode->setValue(temporary->getValue());
            newNode->setNext(_p_head);
            if (_p_head != NULL) _p_head->setPrevious(newNode);
            _p_head = newNode;
            temporary = temporary->getPrevious();
        }
        return *this;
    }
    
    template <typename T>
    vector<T>::~vector()
    {
        // destructor
        delete _p_head; // deleting head pointer trigger destruction of all nodes (look intNode destructor)
    }
    
    // element access //
    
    template <typename T>
    T& vector<T>::at(const int index)
    {
        // returns reference to value of node with given index
        return _findNode(index)->getValue();
    }
    
    template <typename T>
    T& vector<T>::operator[] (const int index)
    {
        // returns reference to value of node with given index
        return _findNode(index)->getValue();
    }
    
    template <typename T>
    T& vector<T>::front()
    {
        // returns reference to value of first node
        return _findNode(0)->getValue();
    }
    
    template <typename T>
    T& vector<T>::back()
    {
        // returns reference to value of last node
        int index = this->size() - 1;
        return _findNode(index)->getValue();
    }
    
    // iterators //
    
    template <typename T>
    iterator<T> vector<T>::begin()
    {
        // returns iterator to first element of vectorOfInt
        iterator begin;
        begin.setPointer(this->_findNode(0)); // index of the first element
        return begin;
    }
    
    template <typename T>
    iterator<T> vector<T>::end ()
    {
        // returns iterator to one after last element of vectorOfInt
        int max_index = this->size()-1;
        iterator end;
        end.setPointer(this->_findNode(max_index+1)); // index of the last element + 1
        end.setPrevious(this->_findNode(max_index)); // index of the last element
        return end;
    }
    
    template <typename T>
    reverse_iterator<T> vector<T>::rbegin()
    {
        // returns reverse_iterator to last element of vectorOfInt
        int index = this->size() - 1;
        reverse_iterator rbegin;
        rbegin.setPointer(this->_findNode(index)); // index of the last element
        return rbegin;
    }
    
    template <typename T>
    reverse_iterator<T> vector<T>::rend()
    {
        // returns reverse_iterator to one before first element of vectorOfInt
        reverse_iterator rend;
        rend.setPointer(this->_findNode(-1)); // index of the first element - 1
        rend.setPrevious(this->_findNode(0)); // index of the first element
        return rend;
    }
    
    // capacity //
    
    template <typename T>
    const int vector<T>::size()
    {
        // returns size of vector (number of nodes)
        int counter = 0;
        intNode<T>* pointer = _p_head;
        while (pointer != NULL)
        {
            pointer = pointer->getNext();
            counter++;
        }
        return counter;
    }
    
    template <typename T>
    const bool vector<T>::empty()
    {
        // returns true when vector is empty
        if (_p_head == NULL) return true;
        else return false;
    }
    
    // modifiers //
    
    template <typename T>
    void vector<T>::assign(iterator first, iterator last)
    {
        // makes vector store values of another vector
        // first is begin iterator and last is end iterator (pointing behind last element)
        // deleting original linked list
        delete _p_head;
        // creating new linked list from beginning
        intNode<T>* p_end_node = new intNode<T>;
        p_end_node->setPrevious(NULL);
        p_end_node->setValue(first.getPointer()->getValue());
        p_end_node->setNext(NULL);
        intNode<T>* temporary = p_end_node;
        for (first = first + 1; first != last; ++first)
        {
            temporary = new intNode<T>;
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
    
    template <typename T>
    void vector<T>::push_back(T value)
    {
        // adds element at the end
        intNode<T>* newNode = new intNode<T>;
        // finding end node
        if (_p_head == NULL)
        {
            newNode->setPrevious(NULL);
            newNode->setValue(value);
            newNode->setNext(NULL);
            _p_head = newNode;
            return;
        }
        intNode<T>* p_end_node = _p_head;
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
    
    template <typename T>
    void vector<T>::push_front(T value)
    {
        // adds element at the front
        intNode<T>* newNode = new intNode<T>;
        newNode->setPrevious(NULL);
        newNode->setValue(value);
        newNode->setNext(_p_head);
        _p_head->setPrevious(newNode);
        _p_head = newNode;
    }
    
    template <typename T>
    void vector<T>::pop_back()
    {
        // deletes last element
        if (_p_head == NULL) return;
        // finding end node
        intNode<T>* p_end_node = _p_head;
        while (p_end_node->getNext() != NULL)
        {
            p_end_node = p_end_node->getNext();
        }
        // deleting node at the end
        p_end_node->getPrevious()->setNext(NULL);
        delete p_end_node; // because last node is pointing to NULL intNode destructor won't delete other nodes
    }
    
    template <typename T>
    void vector<T>::pop_front()
    {
        // deletes first element
        if (_p_head == NULL) return;
        intNode<T>* secondNode = _p_head->getNext();
        if (secondNode != NULL) secondNode->setPrevious(NULL);
        _p_head->setNext(NULL); // to prevent from deleting all nodes (look intNode destructor)
        delete _p_head;
        _p_head = secondNode;
    }
    
    template <typename T>
    iterator<T> vector<T>::insert (iterator position, const T value)
    {
        // inserts node with given value before the node pointed to by iterator
        // returns iterator pointing to inserted node
        intNode<T>* currentNode = position.getPointer();
        if (currentNode == NULL) // case when position is end iterator
        {
            push_back(value);
            // finding end node
            intNode<T>* p_end_node = _p_head;
            while (p_end_node->getNext() != NULL) p_end_node = p_end_node->getNext();
            // creating iterator to return
            iterator end;
            end.setPointer(p_end_node);
            return end;
        }
        intNode<T>* previousNode = position.getPointer()->getPrevious();
        if (previousNode == NULL) {push_front(value); return --position;} // case when position is begin iterator
        intNode<T>* newNode = new intNode<T>;
        previousNode->setNext(newNode);
        newNode->setPrevious(previousNode);
        newNode->setValue(value);
        newNode->setNext(currentNode);
        currentNode->setPrevious(newNode);
        return --position;
    }
    
    template <typename T>
    iterator<T> vector<T>::insert (iterator position, iterator first, iterator last)
    {
        // insertrs range of nodes before the node pointed by position iterator
        // first is pointing to first element to insert and last is pointing behind last element to insert
        // returns iterator pointing to the first of inserted nodes
        if (first >= last) return position;
        intNode<T>* currentNode = position.getPointer();
        if (currentNode == NULL) // case when position is end iterator
        {
            // finding last node
            intNode<T>* temporary = _p_head;
            while (temporary->getNext() != NULL) temporary = temporary->getNext();
            // appending new linked list
            iterator itr = first;
            while (itr != last)
            {
                intNode<T>* newNode = new intNode<T>;
                temporary->setNext(newNode);
                newNode->setPrevious(temporary);
                newNode->setValue(itr.getPointer()->getValue());
                newNode->setNext(NULL);
                temporary = newNode;
                ++itr;
            }
            return first;
        }
        intNode<T>* previousNode = position.getPointer()->getPrevious();
        if (previousNode == NULL) // case when position is begin iterator
        {
            // creating new linked list at the front
            iterator itr = first;
            intNode<T>* temporary = NULL;
            intNode<T>* p_new_head = NULL;
            while (itr != last)
            {
                intNode<T>* newNode = new intNode<T>;
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
        intNode<T>* temporary = previousNode;
        while (itr != last)
        {
            intNode<T>* newNode = new intNode<T>;
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
    
    template <typename T>
    iterator<T> vector<T>::erase (iterator position)
    {
        // deletes element on given position
        // returns iterator pointing to element that followed the last element erased
        intNode<T>* currentNode = position.getPointer();
        if (currentNode == NULL) return this->end(); // case when position is end iterator
        intNode<T>* previousNode = position.getPointer()->getPrevious();
        if (previousNode == NULL) {pop_front(); return this->begin();} // case when position is begin iterator
        intNode<T>* nextNode = position.getPointer()->getNext();
        if (nextNode == NULL) {pop_back(); return this->end();} // case when position points to last element
        ++position; // preparing iterator for return
        previousNode->setNext(nextNode);
        nextNode->setPrevious(previousNode);
        currentNode->setNext(NULL); // to prevent from deleting all nodes (look intNode destructor)
        delete currentNode;
        return position;
    }
    
    template <typename T>
    iterator<T> vector<T>::erase (iterator first, iterator last)
    {
        // deletes given range of elements
        // first is pointing to first element to delete and last is pointing behind last element to delete
        // returns iterator pointing to element that followed the last element erased
        if (first >= last) return last; // case when iterators are in wrong order
        intNode<T>* firstToDeleteNode = first.getPointer();
        if (firstToDeleteNode == NULL) return last; // case when first is end iterator
        intNode<T>* beforeRangeNode = first.getPointer()->getPrevious();
        if (beforeRangeNode == NULL) {_p_head = last.getPointer();} // case when first is begin iterator
        intNode<T>* afterRangeNode = last.getPointer();
        if (afterRangeNode == NULL) // case when last is end iterator
        {
            if (beforeRangeNode != NULL) beforeRangeNode->setNext(NULL);
            delete firstToDeleteNode; // deleting all nodes from firstToDeleteNode (look intNode destructor)
            return last;
        }
        // other case
        intNode<T>* lastToDeleteNode = last.getPointer()->getPrevious();
        if (beforeRangeNode != NULL) beforeRangeNode->setNext(afterRangeNode);
        afterRangeNode->setPrevious(beforeRangeNode);
        lastToDeleteNode->setNext(NULL); // to prevent from deleting all nodes (look intNode destructor)
        delete firstToDeleteNode;
        return last;
    }
    
    template <typename T>
    void vector<T>::clear()
    {
        // deletes all nodes
        delete _p_head; // deleting head pointer trigger destruction of all nodes (look intNode destructor)
        _p_head = NULL;
    }
    
    // private //
    
    template <typename T>
    intNode<T>* vector<T>::_findNode (const int index)
    {
        if (index == -1) return _p_head->getPrevious();
        intNode<T>* pointer = _p_head;
        for (int i = 0; i < index; i++)
        {
            pointer = pointer->getNext();
        }
        return pointer;
    }
    
    
} // end of namespace

#endif /* vector_hpp */
