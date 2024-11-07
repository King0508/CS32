#include "Set.h"
Set::Set(): m_size(0)//default constructor to make a Set containing a circular doubly linked list 
{
	head = new Node; 
	head->next = head;//when the Set is empty, the dummy node has pointers pointing to itself 
	head->prev = head; 
}
Set::Set(const Set& other): m_size(0)//copy constructor for the Set class 
{
	head = new Node; 
	head->next = head;//intialize the Set with a dummy Node
	head->prev = head;
	Node* n = other.head->next;
	while (n!=other.head) //while n is not pointing to other's dummy node 
	{
		insert(n->value);//insert the value at n into this Set 
		n = n->next;//increment n to point to the next node in other 
	}
}
Set& Set::operator= (const Set& rhs)
{
	if (this != &rhs)//makes sure rhs is different than this 
	{
		Set temp(rhs); //makes a copy of rhs 
		swap(temp);//swaps the copy with this*
	}
	return *this; 
}
Set::~Set()
{
	Node* temp = head->next;
	Node* tbd;//pointer to be deleted 
	while (temp != head)
	{
		tbd = temp;
		temp = temp->next; //increment to the next node so it can be deleted 
		delete tbd; 
	}
	delete temp; 
}
bool Set::empty() const
{
	if (head->next == head)
		return true;//head's next pointing to head implies the list is empty with a singular dummy node 
	return false; 
}

int Set::size() const
{
	return(m_size);
}
bool Set::insert(const ItemType& value)
{
	Node* p; 
	for (p = head->next; p != head; p = p->next)//loop from the node after the dummy node back to the dummy node 
	{
		if (value == p->value)
			return false; //return false if value already in the list 

		if (value > p->value)//ensures the list is automatically sorted from big to small when a new node is inserted 
		{
			Node* temp;
			temp = new Node;
			temp->value = value;
			temp->next = p;
			temp->prev = p->prev;
			p->prev->next = temp;//points p->prev's next to temp, and not p, effectively inserting the new Node into the list 
			p->prev = temp;//points p's previous to temp, and not p-prev, effectively inserting the new Node into the list 
			m_size++;//increment size 
			return true;
		}
	}	
	Node* temp;//repeat what is in the for loop for an empty Set, since an empty set will not enter the for loop 
	temp = new Node;
	temp->value = value;
	temp->next = p;
	temp->prev = p->prev;
	p->prev->next = temp;
	p->prev = temp;
	m_size++;
	return true;
}
bool Set::erase(const ItemType& value)
{
	for (Node* p = head->next; p != head; p = p->next)//loop from the node after the dummy node back to the dummy node 
	{
		if (value == p->value)
		{
			p->prev->next = p->next;//p->prev->next should no longer point to p, since we are deleting p. It should point to p->next 
			p->next->prev = p->prev;//p->next->prev should no longer point to p, since we are deleting p. It should point to p->prev 
			delete p;//delete the memory we allocated for p 
			m_size--;//decrement the sizes 
			return true;//return true as the function worked as intended 
		}
	}
	return false;//nothing was erased 
}
bool Set::contains(const ItemType& value) const
{
	for (Node* p = head->next; p != head; p = p->next) //loop from the node after the dummy node back to the dummy node 
	{
		if(value == p->value)
			return true; 
	}
	return false; 
}
bool Set::get(int pos, ItemType& value) const
{
	if (pos <= (m_size - 1) && pos >= 0)//pos can maximally be size-1 because if a number is less than all values in the list, it cannot be in the list. pos also cannot be negative 
	{
		Node* temp = head;
		for (int i = 0; i <= pos; i++)
		{
			temp = temp->next;//move temp to the location of the node that contains the correct position 
		}
		value = temp->value; 
		return true; 
	}
	return false; 
}
void Set::swap(Set& other)
{
	Node* temp = other.head;//temp pointer to hold other.head 
	other.head = head;
	head = temp; 
	int tempSize = other.m_size;//temp pointer to hold other.m_size 
	other.m_size = m_size; 
	m_size = tempSize; 
}
void unite(const Set& s1, const Set& s2, Set& result)
{		
	Set empty; //result could be non-empty so work will be done on an empty set
	for (int i = 0; i < s1.size(); i++)//loop through s1 
	{
		ItemType x;
		s1.get(i, x);
		empty.insert(x);//insert all of s1 into an empty set 
	}
	for (int k = 0; k < s2.size(); k++)//loop through s2 
	{
		ItemType x; 
		s2.get(k, x); 
		if (!empty.contains(x))//if the set does not contain x, then insert x into the set 
			empty.insert(x);  
	}
	result.swap(empty);//swap empty with result 
}
void inOnlyOne(const Set& s1, const Set& s2, Set& result)
{
	Set empty; //result could be non-empty so work will be done on an empty set 
	for (int i = 0; i < s1.size(); i++)//loop through s1 
	{
		ItemType x;
		s1.get(i, x);
		empty.insert(x);//insert all of s1 into an empty set 
	}
	for (int k = 0; k < s2.size(); k++)//loop throuhg s2 
	{
		ItemType x;
		s2.get(k, x);
		if (!empty.contains(x))//if the set does not contain x, then insert x into the set 
			empty.insert(x);
		else//otherwise the set does contain x, erase x 
			empty.erase(x); 
	}
	result.swap(empty);//swap empty with result 
}
