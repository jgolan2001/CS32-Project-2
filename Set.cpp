//
//  Set.cpp
//  Project 2
//
//  Created by Jordan Golan on 4/18/21.
//
#include <iostream>
#include "Set.h"
using namespace std;

Set::Set()
{
    // initialize variables, create empty list
    m_numElements = 0;
    m_head = nullptr;
    m_tail = nullptr;
}

Set::~Set()
{
    Node *temp; // create temporaroy node
    while (m_head != nullptr)
    {
        temp = m_head;
        m_head = m_head->m_next;
        delete temp;
    }
}


Set::Set(const Set& other)
{
    
    m_numElements = other.m_numElements;
    
    // if empty, then set tail and head both to nullptr
    if (other.m_numElements == 0)
    {
        m_tail = nullptr;
        m_head = nullptr;
    }
    
    m_head = new Node;
    
    m_head -> m_prev = nullptr;
    
    Node* Copy = m_head;
    //copies all but last node
    for (Node* p = other.m_head; p->m_next != nullptr; p = p->m_next)
    {
        Node* newGuy = new Node;
        Copy->m_value = p->m_value;
        Copy->m_next = newGuy;
        newGuy->m_prev = Copy;
        
        Copy = newGuy;
    }
    
    // copy the data into last node, and makes the next nullptr
    Copy -> m_value = other.m_tail->m_value;
    Copy -> m_next = nullptr;
    
    m_tail = Copy;//set tail pointer
}


Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

bool Set::empty() const
{
    // returns true if set is empty
    bool result = false;
    
    if (m_numElements == 0)
    {
        result  = true;
    }
    return result;
}

int Set::size() const
{
    return m_numElements; //returns number of Nodes
}

bool Set::insert(const ItemType& value)
{
    
    if (contains(value)) //checks its values is already in set
    {
        return false;
    }
    
    if (m_numElements == 0) // case for when this is first node inserted
    {
        Node* newGuy = new Node;
        newGuy->m_value = value;
        newGuy->m_prev = nullptr;
        newGuy->m_next = nullptr;
        m_numElements++;
        
        m_head = newGuy;
        m_tail = newGuy;
        
        return true;
    }
    
    // creates new nodes inserting at end of list
    Node* newGuy = new Node;
    newGuy->m_value = value;
    newGuy->m_prev = m_tail;
    newGuy->m_next = nullptr;
    
    m_tail->m_next = newGuy;
    m_tail = newGuy;
    
    m_numElements++;
    return true;
}

bool Set::erase(const ItemType& value)
{
    if (!contains(value)) // checks to see if value is in set
    {
        return false;
    }
    
    Node* p;
    for (p = m_head; p != nullptr; p = p->m_next) // assigned pointer p to value
    {
        if (p->m_value == value)
        {
            break;
        }
    }
    
    // adjusts head and tail pointer if first or last node is removed
    if (p->m_prev != nullptr)
    {
        p->m_prev->m_next = p->m_next;
    }
    else
    {
        m_head = p->m_next; // if head node is removed, m_head points to next node
    }
    
    if (p->m_next != nullptr)
    {
        p->m_next->m_prev = p->m_prev;
    }
    else
    {
        m_tail = p->m_prev; // if tail node is removed, m_tail points to prev node
    }
    
    delete p; // delete node that contains value
    m_numElements--;
    return true;
}

bool Set::contains(const ItemType& value) const
{
    // iterate through list seeing if it contains value
    Node* p;
    for (p = m_head; p != nullptr; p = p->m_next)
    {
        if (p->m_value == value)
        {
            return true;
        }
    }
    
    return false;
}

bool Set::get(int pos, ItemType& value) const
{
    // check to see if index is valid
    if (pos >= m_numElements || pos < 0)
    {
        return false;
    }
    
    //create temp copy of set so we can delete nodes
    Set temp(*this);
    
    //Delete the max value i-times
    for (int i = 0; i < pos; i++)
    {
        ItemType max = temp.m_head->m_value;
        
        //iterate through set to find max
        for (Node* p = temp.m_head; p != nullptr; p = p->m_next)
        {
            if (p->m_value > max)
            {
                max = p->m_value;
            }
        }
        temp.erase(max); //delete max value
    }
    
    // Find new max value
    ItemType max = temp.m_head->m_value;
    for (Node* p = temp.m_head; p != nullptr; p = p->m_next)
    {
        if (p->m_value > max)
        {
            max = p->m_value;
        }
    }
    value = max; // set value equal to new found max
    
    return true;
}

void Set::swap(Set& other)
{
    // number of elements in each set swapped
    int nElements = m_numElements;
    m_numElements = other.m_numElements;
    other.m_numElements = nElements;
    
    // heads of each set swapped
    Node* nhead = m_head;
    m_head = other.m_head;
    other.m_head = nhead;
    
    // tails of each set swapped
    Node* ntail = m_tail;
    m_tail = other.m_tail;
    other.m_tail = ntail;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
    result = s2; //copies s2 into result
    
    //inserts elements of s1 into results
    for (int i = 0; i < s1.size(); i++)
    {
        ItemType toBeInserted; // temporary variable
        s1.get(i, toBeInserted);
        result.insert(toBeInserted); // insert already checks for repeats
    }
}

void difference(const Set& s1, const Set& s2, Set& result)
{
    unite(s1, s2, result); // creates a united result set
    
    for (int i = 0; i < s1.size(); i++) // iterates through s1
    {
        for (int j = 0; j < s2.size(); j++) // iterates through s2
        {
            ItemType var1;
            ItemType var2;
            s1.get(i, var1);
            s2.get(j, var2);
            if (var1==var2) // if values in s1 and s2 match erase them in result
            {
                result.erase(var1);
            }
        }
        
    }
}
