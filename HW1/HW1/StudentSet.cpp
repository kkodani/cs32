// StudentSet.cpp

#include "StudentSet.h"
#include <iostream>

StudentSet::StudentSet()
{
	
}

bool StudentSet::add(unsigned long id)
{
	return s.insert(id);
}

int StudentSet::size() const
{
	return s.size();
}

void StudentSet::print() const
{
	unsigned long x;
	for(int i=0; i<s.size(); i++)
	{
		if(s.get(i, x))
		{
			std::cout << x <<std::endl;
		}
	}
	
}
