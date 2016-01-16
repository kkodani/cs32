// Kyle Kodani
// Project 2

// main.cpp

#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
	Set s1;		// default constructor
		//for an empty set
	assert(s1.size() == 0);		// test size
	assert(s1.empty());			// test empty
	assert(!s1.erase(1));		// nothing to remove, also tests contains 
	
	assert(s1.insert(1));		// test insert, also tests contains
		// for a one item set
	assert(s1.size() == 1);		// test size
	assert(!s1.empty());		// test empty
	assert(!s1.erase(2));		// can't remove what isn't there, also tests contains
	assert(s1.erase(1));		// successful erase, also tests contains
	assert(s1.empty());			// set is now empty
	
	assert(s1.insert(1));		// test insert
	assert(s1.insert(2));		// test insert
		// for a two item set
	assert(!s1.insert(2));		// can't insert what is already there, also tests contains
	
		// test get function
	ItemType x=5;
	assert(!s1.get(5, x));		// can't get something out of bounds
	assert(x==5);				// x unchanged by useless get call
	assert(s1.get(0, x));		// test useful get call
	assert(x==1 || x==2);		// make sure get has changed x to something that is in the set
	
		// testing swap
	Set s2;						// create a set to swap with
	assert(s2.insert(3));
	assert(s2.insert(4));
	assert(s2.insert(5));
	s1.swap(s2);
	assert(s1.size()==3 && s2.size()==2);	// successful size swap
	assert(s1.erase(5));		// successful element swap
	assert(s2.contains(2));		// successful element swap
	s2.swap(s2);				// swap with itself
	assert(s2.size()==2);		// no size change
	assert(s1.get(1, x));		
	assert(x==3 || x==4);		// successful element swap
	
		// testing copy constructor
	Set s3;			// new set
	Set s4(s3);		// new set copied from s3
	assert(s3.empty() && s4.empty());	// both sets should be empty
	assert(s3.insert(1));		// fill s3 with data
	assert(s3.insert(2));
	assert(s3.insert(3));
	Set s5(s3);					// create set copied from s3
	assert(s5.erase(3));		// successful element copy
	assert(s3.contains(3));		// make sure s3 and s5 are distinct
	
		// testing the assignment operator
		// (this also tests the copy constructor and swap function)
	Set s6;						// create a new set
	assert(s6.insert(1));		// fill s6 with data
	assert(s6.insert(2));
	assert(s6.insert(3));
	Set s7;						// create a new set
	assert(s7.insert(4));		// fill s7 with data
	s6=s7;		// test assignment operator
	assert(s7.contains(4) && s7.size()==1);		// successful assignment
	assert(s6.erase(4) && s7.contains(4));	// make sure s6 and s7 are distinct
	s7=s7;		// assignment to itself
	assert(s7.contains(4) && s7.size()==1);		// no change
	
		// test unite
	Set sa, sb, sc;				// create new sets
	assert(sa.insert(1));		// fill sets
	assert(sb.insert(2));
	assert(sc.insert(3));
	unite(sa, sb, sc);
	assert(sc.contains(1) && sc.contains(2));	// successful unite
	assert(sc.size()==2);		// successful unite
	assert(!sc.contains(3));	// what sc had before is not still there
	unite(sa, sb, sa);			// aliasing test
	assert(sa.contains(1) && sa.contains(2));	// successful unite
	unite(sb, sb, sb);			// aliasing test
	assert(sc.contains(2));		// successful unite
	
		// test subtract
	Set sx, sy, sz;				// create new sets
	assert(sx.insert(1));		// fill sets
	assert(sx.insert(2));
	assert(sx.insert(3));
	assert(sy.insert(2));
	assert(sy.insert(3));
	assert(sy.insert(4));
	assert(sz.insert(5));
	subtract(sx, sy, sz);
	assert(sz.size()==1 && sz.contains(1));		// successful subtract
	subtract(sx, sy, sx);		// aliasing test
	assert(sx.size()==1 && sx.contains(1));		// successful subtract
	subtract(sy, sy, sy);		// aliasing test
	assert(sy.empty());			// successful subtract
	
}
