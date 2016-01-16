// Set.h

#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>
typedef unsigned long ItemType;

class Set
{
	public:
		Set();
		Set(const Set& other);
		~Set();
		Set& operator=(const Set& other);
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
			ItemType data;
			Node* next;
			Node* prev;
		};
		int m_size;
		Node* head;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif