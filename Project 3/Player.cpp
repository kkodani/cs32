// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
	/*
	int determineBestComputerMove(Scaffold& s, int N, int color);
	int determineBestHumanMove(Scaffold& s, int N, int color);
	int rating(Scaffold& s, int N, int color);
	bool checkWin(int c, int r, Scaffold& s, int N);
	bool connectedN(int c, int r, int cmod, int rmod, Scaffold& s, int N);
	*/
};

//prompts user for column number, plays in that column if possible
int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	for(int i=1; i<=s.cols(); i++)
	{
		if(s.checker(i, 1)==VACANT)
		{
			return i;
		}
	}
    return -1;
}


//prompts user for column number, plays in that column if possible
int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	if(s.numberEmpty()==0)
	{
		return -1;
	}
	int choice;
	bool invalid=true;
	cout << "Please select a column where you would like to drop your piece" << endl;
	while(invalid)
	{
		cin >> choice;
		cin.ignore(1000, '\n');
		
		if(choice<1 || choice>s.cols())
		{
			cout << "Invalid column, please try again." << endl;
		}
		
		else if(s.checker(choice, 1)!=VACANT)
		{
			cout << "Column is full, please try again." << endl;
		}
		
		else
		{
			invalid=false;
		}
	}
	
	return choice;
}

 
//always chooses the leftmost non-full column
int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	for(int i=1; i<=s.cols(); i++)
	{
		if(s.checker(i, 1)==VACANT)
		{
			return i;
		}
	}
    return -1;
}

/*
int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	Scaffold test(s);
	//int computer=color;
    return determineBestComputerMove(test, N, color);
}

int SmartPlayerImpl::determineBestComputerMove(Scaffold& s, int N, int color)
{
	vector<vector<int> > paths;
	vector<int> path;
	
	for(int i=1; i<=s.cols(); i++)
	{
		path.clear();
		
		if(s.checker(i, 1)==VACANT)
		{
			s.makeMove(i, color);
			int score=rating(s, N, color);
			if(score==color || score==0)
			{
				path.push_back(score);
			}
			else
			{
				path.push_back(determineBestHumanMove(s, N, color));
			}
			//s.display();
			s.undoMove(i);
			//s.display();
			paths.push_back(path);
		}
		
	}
	
	int end=2;
	int length=paths[0].size();
	int choice;
	//int current;
	
	for(int i=0; i<paths.size(); i++)		//check for win
	{
		//current=paths[i][paths[i].size()-1];
		if(paths[i][paths[i].size()-1]==1 && paths[i].size()<=length)
		{
			
			end=1;
			length=paths[i].size();
			choice=i+1;
		}
	}
	
	if(end!=1)			//no win
	{
		for(int i=0; i<paths.size(); i++)		//check for tie
		{
			//current=paths[i][paths[i].size()-1];
			if(paths[i][paths[i].size()-1]==0 && paths[i].size()>=length)
			{
				end=0;
				length=paths[i].size();
				choice=i+1;
			}
		}
	}
	
	if(end!=1 && end!=0)			//no win or tie
	{
		for(int i=0; i<paths.size(); i++)		//check for loss
		{
			//current=paths[i][paths[i].size()-1];
			if(paths[i][paths[i].size()-1]==-1 && paths[i].size()>=length)
			{
				
				end=-1;
				length=paths[i].size();
				choice=i+1;
				
			}
		}
	}
	
	//s.display();
	
	for(int i=1; i<=s.cols(); i++)
	{
		//int u=s.checker(i, 1);
		if(s.checker(i, 1)==VACANT)
		{
			choice--;
			if(choice==0)
			{
				return i;
			}
		}
	}
	
	return -1;
}

int SmartPlayerImpl::determineBestHumanMove(Scaffold& s, int N, int color)
{
	vector<vector<int> > paths;
	vector<int> path;
	
	for(int i=1; i<=s.cols(); i++)
	{
		path.clear();
		
		if(s.checker(i, 1)==VACANT)
		{
			s.makeMove(i, color);
			int score=rating(s, N, color);
			if(score==-1 || score==0)
			{
				path.push_back(score);
			}
			else
			{
				path.push_back(determineBestComputerMove(s, N, color));
			}
			//s.display();
			s.undoMove(i);
			//s.display();
			paths.push_back(path);
		}
		
	}
	
	int end=2;
	int length=paths[0].size();
	int choice;
	//int current;
	
	for(int i=0; i<paths.size(); i++)		//check for win
	{
		//current=paths[i][paths[i].size()-1];
		if(paths[i][paths[i].size()-1]==-1 && paths[i].size()<=length)
		{
			
			end=-1;
			length=paths[i].size();
			choice=i+1;
		}
	}
	
	if(end!=-1)			//no win
	{
		for(int i=0; i<paths.size(); i++)		//check for tie
		{
			//current=paths[i][paths[i].size()-1];
			if(paths[i][paths[i].size()-1]==0 && paths[i].size()>=length)
			{
				end=0;
				length=paths[i].size();
				choice=i+1;
			}
		}
	}
	
	if(end!=-1 && end!=0)			//no win or tie
	{
		for(int i=0; i<paths.size(); i++)		//check for loss
		{
			//current=paths[i][paths[i].size()-1];
			if(paths[i][paths[i].size()-1]==1 && paths[i].size()>=length)
			{
				
				end=1;
				length=paths[i].size();
				choice=i+1;
			}
		}
	}
	
	//s.display();
	
	for(int i=1; i<=s.cols(); i++)
	{
		//int u=s.checker(i, 1);
		if(s.checker(i, 1)==VACANT)
		{
			choice--;
			if(choice==0)
			{
				return i;
			}
		}
	}
	
	return -1;
	
}

int SmartPlayerImpl::rating(Scaffold& s, int N, int color)
{
	for(int r=1; r<=s.rows(); r++)
	{
		for(int c=1; c<=s.cols(); c++)
		{
			if(s.checker(c, r)==color)			
			{												
				if(checkWin(c, r, s, N))		//color wins
				{
					return 1;
				}
				
			}
			
			else if(s.checker(c, r)!=color && s.checker(c, r)!=VACANT)	
			{													
				if(checkWin(c, r, s, N))		//other color win
				{
					return -1;
				}
			}
		}
	}
	
	
	if(s.numberEmpty()==0)		//no winner and board is full, therefore tie game
	{
		return 0;
	}
	
    return 2;				//board is not full and no winner, therefore game is not over
}

//calls connectedN with horizontal, vertical, diagonal up, and diagonal down possibilities
bool SmartPlayerImpl::checkWin(int c, int r, Scaffold& s, int N)
{
	return (connectedN(c, r, 1,  0, s, N) ||			// Horizontal
		    connectedN(c, r, 0,  1, s, N) ||			// Vertical
		    connectedN(c, r, 1,  1, s, N) ||			// Diagonal up
		    connectedN(c, r, 1, -1, s, N));				// Diagonal down
}

//checks to see if there is a connected N pieces is a direction staring at (r,c) and in a direction determined by rmod and cmod
bool SmartPlayerImpl::connectedN(int c, int r, int cmod, int rmod, Scaffold& s, int N)
{
    int color = s.checker(c, r);
	
    for (int i = 0; i < N; i++)
	{
        if (s.checker(c+(i*cmod), r+(i*rmod))!=color)		//checks if each piece starting at (r,c)
		{													//and going in a direction determined by rmod and cmod
            return false;									//is the same color as the color of (r,c)
		}
	}
	
    return true;
}
*/

//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
