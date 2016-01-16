// landmark.cpp

#include <iostream>
#include <string>
using namespace std;

class Landmark
{
	public:
		Landmark(string n);
		virtual ~Landmark();
		string name() const;
		virtual string color() const;
		virtual string icon() const=0;
	private:
		string m_name;
};

Landmark::Landmark(string n): m_name(n)
{
	
}

Landmark::~Landmark()
{
	
}

string Landmark::name() const
{
	return m_name;
}

string Landmark::color() const
{
	return "yellow";
}



class Hotel: public Landmark
{
	public:
		Hotel(string n);
		~Hotel();
		string icon() const;
};

Hotel::Hotel(string n): Landmark(n)
{
	
}

Hotel::~Hotel()
{
	cout << "Destroying the hotel " << name() << "." << endl;
}

string Hotel::icon() const
{
	return "bed";
}



class Restaurant: public Landmark
{
	public:
		Restaurant(string n, int c);
		~Restaurant();
		string icon() const;
	private:
		int m_capacity;
};

Restaurant::Restaurant(string n, int c): Landmark(n), m_capacity(c)
{
	
}

Restaurant::~Restaurant()
{
	cout << "Destroying the restaurant " << name() << "." << endl;
}

string Restaurant::icon() const
{
	if(m_capacity>=40)
	{
		return "large knife/fork";
	}
	else
	{
		return "small knife/fork";
	}

}



class Hospital: public Landmark
{
	public:
		Hospital(string n);
		~Hospital();
		string color() const;
		string icon() const;
};

Hospital::Hospital(string n): Landmark(n)
{
	
}

Hospital::~Hospital()
{
	cout << "Destroying the hospital " << name() << "." << endl;
}

string Hospital::color() const
{
	return "blue";
}

string Hospital::icon() const
{
	return "H";
}

int main()
{
	Landmark* h=new Hospital("john");
	cout << h->icon() << h->color();
}


