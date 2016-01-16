// newSet.cpp

#include <iostream>
#include "newSet.h"

Set::Set():m_size(0), maxsize(DEFAULT_MAX_ITEMS)
{
	data=new ItemType[DEFAULT_MAX_ITEMS];
}

Set::Set(int a):m_size(0), maxsize(a)
{
	data=new ItemType[a];
}

Set::Set(const Set& other):m_size(other.m_size), maxsize(other.maxsize)
{
	data=new ItemType[maxsize];
	for(int i=0; i<other.m_size; i++)
	{
		data[i]=other.data[i];
	}
}

Set::~Set()
{
	delete [] data;
}

Set& Set::operator=(const Set& other)
{
	if(this!=&other)
	{
		Set temp(other);
		swap(temp);
		
	}
	return *this;
}

bool Set::empty() const
{
	if(m_size==0)
	{
		return true;
	}
	
	return false;
}

int Set::size() const
{
	return m_size;
}

bool Set::insert(const ItemType& value)
{
	if(m_size>=maxsize || contains(value))
	{
		return false;
	}
	
	data[m_size]=value;
	m_size++;
	return true;
}

bool Set::erase(const ItemType& value)
{
	if(!contains(value))
	{
		return false;
	}
	
	m_size--;
	for(int i=find(value); i<m_size; i++)
	{
		data[i]=data[i+1];
	}
	
	return true;
}

bool Set::contains(const ItemType& value) const
{
	for(int i=0; i<m_size; i++)
	{
		if(value==data[i])
		{
			return true;
		}
	}
	
	return false;
}

bool Set::get(int i, ItemType& value) const
{
	if(i>=0 && i<m_size)
	{
		value=data[i];
		return true;
	}
	
	return false;
}

void Set::swap(Set& other)
{
	ItemType* temp=data;
	data=other.data;
	other.data=temp;
	
	int tempSize=m_size;
	m_size=other.m_size;
	other.m_size=tempSize;
	
	int tempMaxSize=maxsize;
	maxsize=other.maxsize;
	other.maxsize=tempMaxSize;
}

int Set::find(const ItemType& value) const
{
	for(int i=0; i<m_size; i++)
	{
		if(value==data[i])
		{
			return i;
		}
	}
	return -1;
}


void Set::print() const
{
	for(int i=0; i<m_size; i++)
	{
		std::cout << data[i] <<std::endl;
	}
}


