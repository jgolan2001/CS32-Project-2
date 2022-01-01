//
//  Set.hpp
//  Project 2
//
//  Created by Jordan Golan on 4/18/21.
//

#ifndef Set_h
#define Set_h

#include <stdio.h>
#include <string>

using ItemType = std::string;
// declaring Set class
class Set
{
public:
    Set();
    ~Set(); // destructor
    Set (const Set& other); // copy constructor
    Set& operator = (const Set& rhs); // assignment operator
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    
private:
    struct Node
    {
        ItemType m_value;
        Node* m_next; // pointer to next element in linked list
        Node* m_prev; // pointer to previous element in linked list
    };
    
    Node* m_head; // pointer to first element in linked list
    Node* m_tail; // pointer to last element in linked list
    int m_numElements; // number of elements in linked list
    
};

//declaring set algorithms
void unite(const Set& s1, const Set& s2, Set& result);

void difference(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
