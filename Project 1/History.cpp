// History.cpp

#include <iostream>
#include "History.h"

History::History(int nRows, int nCols): m_rows(nRows), m_cols(nCols)
{
	for (int r = 0; r < m_rows; r++)
	{
        for (int c = 0; c < m_cols; c++)
		{
            grid[r][c] = '.';
		}
	}
}

bool History::record(int r, int c)
{
	if(r-1<0 || r-1>m_rows || c-1<0 || c-1>m_cols)
	{
		return false;
	}
	
	else
	{
		if(grid[r-1][c-1]=='9')
		{
			// do nothing
		}
		
		else if(grid[r-1][c-1]>='1' && grid[r-1][c-1]<='8')
		{
			grid[r-1][c-1]++;
		}
		
		else  //gird location is '.'
		{
			grid[r-1][c-1]='1';
		}

	}
	
	return true;
}

void History::display() const
{
	clearScreen();
	
	for(int r=0; r<m_rows; r++)
	{
		std::cout << grid[r] << std::endl;
	}
	std::cout << std::endl;
}

