// Scaffold.cpp

#include "provided.h"
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nRows); 
    int cols() const;
    int rows() const;
    int numberEmpty() const;
    int checker(int c, int r) const; 
    void display() const; 
    bool makeMove(int c, int color); 
    int undoMove(int c);
  private:
	vector<vector<int> > grid;
	int m_columns;
	int m_rows;
};

// Constructor: builds a scaffold using a vector of vectors of ints
ScaffoldImpl::ScaffoldImpl(int nColumns, int nRows): m_columns(nColumns), m_rows(nRows)
{
	if(nColumns<=0 || nRows<=0)		//invalid column or row input
	{
		cerr << "ERROR: Illegal row or column size" << endl;
		exit(1);
	}
	
	grid.resize(nRows);				//construct the vector
	
	for (int r = 0; r < nRows; r++)
	{
		grid[r].resize(nColumns);
	}
	
	for (int r = 0; r < nRows; r++)		//fill the vector
	{
		for (int c = 0; c < nColumns; c++)
		{
			grid[r][c] = VACANT;
		}
	}
}

//return number of columns
int ScaffoldImpl::cols() const
{
    return m_columns;
}

//return number of rows
int ScaffoldImpl::rows() const
{
    return m_rows;
}

//return number of empty spots
int ScaffoldImpl::numberEmpty() const
{
	int count=0;
	
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_columns; c++)
		{
			if(grid[r][c]==VACANT)
			{
				count++;
			}
		}
	}
	
    return count;
}

//returns color of indicated spot
int ScaffoldImpl::checker(int c, int r) const
{
	if(r>m_rows || r<=0 || c>m_columns || c<=0)
	{
		return VACANT;
	}
	
	if(grid[r-1][c-1]==RED)
	{
		return RED;
	}
	
	if(grid[r-1][c-1]==BLACK)
	{
		return BLACK;
	}
	
    return VACANT;
}

// prints out the scaffold
void ScaffoldImpl::display() const
{
	int gridRow=0;			//stores grid coordinates, to not get confused with display coordinates
	int gridColumn=0;		
	for(int r=0; r<m_rows+1; r++)
	{
		gridColumn=0;
		
		if(r==m_rows)		//only applies to bottom line
		{
			for(int c=0; c<((m_columns*2)+1); c++)
			{
				if(c%2==0)
				{
					cout << "+";
				}
				
				if(c%2==1)
				{
					cout << "-";
				}
			}
		}
		else
		{
			for(int c=0; c<((m_columns*2)+1); c++)
			{
				if(c%2==0)
				{
					cout << "|";
				}
				
				if(c%2==1)
				{
					if(grid[gridRow][gridColumn]==VACANT)
					{
						cout << " ";
					}
					
					if(grid[gridRow][gridColumn]==RED)
					{
						cout << "R";
					}
					
					if(grid[gridRow][gridColumn]==BLACK)
					{
						cout << "B";
					}
					
					gridColumn++;
				}
			}
			
		}
		
		gridRow++;
		cout << endl;
	}
}

//plays piece in column c if possible
bool ScaffoldImpl::makeMove(int c, int color)
{
	if(c>m_columns || c<=0)
	{
		return false;
	}
	
	for(int r=m_rows-1; r>=0; r--)		//start at bottom of column
	{
		if(grid[r][c-1]==VACANT)
		{
			grid[r][c-1]=color;
			return true;
		}
	}
	
    return false;
}

// removes top piece in column c
int ScaffoldImpl::undoMove(int c)
{
	int color;
	if(c>m_columns || c<=0)
	{
		return VACANT;
	}
	
	for(int r=0; r<m_rows; r++)		//start from top of column
	{
		if(grid[r][c-1]!=VACANT)
		{
			color=grid[r][c-1];
			grid[r][c-1]=VACANT;
			return color;
		}
	}
	
    return VACANT;
}


//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nRows)
{
    m_impl = new ScaffoldImpl(nColumns, nRows);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::rows() const
{
    return m_impl->rows();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checker(int c, int r) const
{
    return m_impl->checker(c, r);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int c, int color)
{
    return m_impl->makeMove(c, color);
}
 
int Scaffold::undoMove(int c)
{
    return m_impl->undoMove(c);
}
