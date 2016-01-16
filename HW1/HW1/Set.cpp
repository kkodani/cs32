// Set.cpp

//#include <iostream>
#include "Set.h"

Set::Set():m_size(0)
{
	
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
	if(m_size>=DEFAULT_MAX_ITEMS || contains(value))
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
	int max;
	int otherSize=other.m_size;
	int thisSize=m_size;
	ItemType thisTemp;
	ItemType otherTemp;
	if(m_size>other.m_size)
	{
		max=m_size;
	}
	else
	{
		max=other.m_size;
	}
	
	m_size=otherSize;
	other.m_size=thisSize;
	for(int i=0; i<max; i++)
	{
		thisTemp=data[i];
		otherTemp=other.data[i];
		data[i]=otherTemp;
		other.data[i]=thisTemp;
	}
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

/*
void Set::print() const
{
	for(int i=0; i<m_size; i++)
	{
		std::cout << data[i] <<std::endl;
	}
}
*/

