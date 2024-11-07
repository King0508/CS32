#ifndef SET_H
#define SET_H
#include<string>
#include "OurType.h"
using ItemType = int;

class Set
{
public:
    Set();
    Set(const Set& other); 
    Set& operator=(const Set& rhs); 
    ~Set(); 
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
        ItemType value; 
        Node* next;
        Node* prev;
    }; 
    int m_size; 
    Node* head; 
};
void unite(const Set& s1, const Set& s2, Set& result);
void inOnlyOne(const Set& s1, const Set& s2, Set& result);
#endif // !SET_H

