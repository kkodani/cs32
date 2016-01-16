// Set.cpp


#include "Set.h"

// Constructor
Set::Set():m_size(0)
{
	head=new Node;		// Makes head point to a dummy node
	head->next=head;	// The dummy node points to itself
	head->prev=head;
}

// Copy Constructor
Set::Set(const Set& other):m_size(0)
{
	head=new Node;		// Makes head point to a dummy node
	head->next=head;	// The dummy node points to itself
	head->prev=head;
	Node* p=(other.head)->next;
	for(int i=0; i<other.m_size; i++)	// loops through the other Set, inserting data
	{									// from other Set into this Set
		insert(p->data);
		p=p->next;
	}
}

// Destructor
Set::~Set()
{
	Node* p=head->next;
	for(int i=0; i<m_size; i++)		// loops through set, while deleting the nodes
	{								// pointed to by the prev pointer
		p=p->next;
		delete p->prev;
	}
	delete head;					// deletes head, the last remaining node
}

// Assignment Operator
Set& Set::operator=(const Set& other)
{
	if(this!=&other)		// check to make sure the two sets are different sets.
	{
		Set temp(other);	// copy and swap
		swap(temp);
	}
	return *this;
}

// Empty: returns true if Set is empty, false otherwise
bool Set::empty() const
{
	if(m_size==0)		// Set is empty if size is 0
	{
		return true;
	}
	
	return false;
}

// Size: returns size of set
int Set::size() const
{
	return m_size;
}

// Insert: inserts an item at the end of a Set.  returns trues if successful, false otherwise.
bool Set::insert(const ItemType& value)
{
	if(contains(value))		// check to make sure value is not already in set
	{
		return false;
	}
	Node* newNode=new Node;				// create new node and adjust its pointers, 
	newNode->data=value;				// the pointers of the dummy node, and the 
	newNode->next=head;					// pointers of head's previous node such that
	newNode->prev=head->prev;			// the new node is properly inserted at the
	(*(head->prev)).next=newNode;		// end of the set.
	head->prev=newNode;
	m_size++;							// increment size of set
	
	return true;
}

// Erase: erase an item from a set.  returns true if successful, false otherwise.
bool Set::erase(const ItemType& value)
{
	if(!contains(value))		// check to make sure value is actually in set.
	{
		return false;
	}
	
	m_size--;		// decrement size of set
	Node* p;
	for(p=head->next; p->data!=value; p=p->next)	// loop through the set such that p 
	{												// points to the node we want to erase
		// do nothing
	}
	
	(*(p->prev)).next=p->next;		// adjust the pointers surrounding p's node to
	(*(p->next)).prev=p->prev;		// point around p's node
	
	delete p;			// delete p's node to prevent memory leak
	return true;
}

// Contains: returns true if value can be found within the set, false otherwise
bool Set::contains(const ItemType& value) const
{
	for(Node* p=head->next; p!=head; p=p->next)		// loop through set
	{
		if(value==p->data)		// check if value is at current node
		{
			return true;
		}
	}
	
	return false;
}

// Get: takes a value from the set and places it into value.  returns true if successful, false otherwise
bool Set::get(int i, ItemType& value) const
{
	if(i>=0 && i<m_size)		// check to make sure i is within scope of set
	{
		Node* p=head->next;
		for(int index=0; index<i; index++)		// loop through set i times
		{
			p=p->next;
		}
		value=p->data;		// place data at position i into value
		return true;
	}
	
	return false;	
}

// Swap: swaps two sets with each other
void Set::swap(Set& other)
{
	Node* temp=head;		// swap the head pointers of each set
	head=other.head;
	other.head=temp;
	
	int tempSize=m_size;	// swap the sizes of each set
	m_size=other.m_size;
	other.m_size=tempSize;
}

// Unite: stores the values that are contined in s1 or s2 in result
void unite(const Set& s1, const Set& s2, Set& result)
{
	Set united;		// empty set
	ItemType x;		// element holder
	for(int j=0; j<s1.size(); j++)		// loop through s1
	{
		s1.get(j, x);					// add s1's elements to united
		united.insert(x);
	}
	
	for(int k=0; k<s2.size(); k++)		// loop through s2
	{
		s2.get(k, x);					// add s2's elements to united
		united.insert(x);
	}
	
	result=united;		// make it so result is the set that has been united
}

// Subtract: stores the values that are contined in s1 but not s2 in result
void subtract(const Set& s1, const Set& s2, Set& result)
{
	Set subtracted;		// empty set
	ItemType x;			// element holder
	for(int j=0; j<s1.size(); j++)		// loop through s1
	{
		s1.get(j, x);					// add s1's elements to subtracted
		subtracted.insert(x);
	}
	
	for(int k=0; k<s2.size(); k++)		// loop through s2
	{
		s2.get(k, x);					// remove s2's elements from subtracted
		subtracted.erase(x);
	}
	
	result=subtracted;		// make it so result is the set that has been subtracted
}


