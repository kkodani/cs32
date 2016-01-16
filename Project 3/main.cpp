// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;




int main()
{
	
	Scaffold s(7,6);
	HumanPlayer hp1("bob");
	HumanPlayer hp2("james");
	Game g(s, 4, &hp1, &hp2);
	g.play();
	
}
