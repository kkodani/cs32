// testStudentSet.cpp

#include "Set.h"
#include <iostream>
#include <string>
#include "StudentSet.h"
using namespace std;

int main()
{
	StudentSet geo1;
	
	geo1.add(123451);
	geo1.add(123452);
	
	StudentSet geo2(geo1);
	
	geo1.add(123453);
	
	
	geo1.print();
	cout << endl;
	geo2.print();
	
	cout << endl;
}
