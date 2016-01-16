// Game.cpp

#include "provided.h"
#include <iostream>
using namespace std;

class GameImpl
{
  public:
    GameImpl(const Scaffold& s, int N, Player* red, Player* black);
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checker(int c, int r) const;
	bool checkWin(int c, int r) const;
	bool connectedN(int c, int r, int cmod, int rmod) const;
  private:
	Scaffold m_scaffold;
	int m_win;
	Player* m_red;
	Player* m_black;
	int m_turn;
	int m_winner;
};

//construct a game: assign all input to data members, set m_turn to 0 and m_winner to some arbitrary value
GameImpl::GameImpl(const Scaffold& s, int N, Player* red, Player* black):
	m_scaffold(s), m_win(N), m_red(red), m_black(black), m_turn(1), m_winner(5)
{
	
}

//calls connectedN with horizontal, vertical, diagonal up, and diagonal down possibilities
bool GameImpl::checkWin(int c, int r) const
{
	return (connectedN(c, r, 1,  0) ||			// Horizontal
		    connectedN(c, r, 0,  1) ||			// Vertical
		    connectedN(c, r, 1,  1) ||			// Diagonal up
		    connectedN(c, r, 1, -1));			// Diagonal down
}

//checks to see if there is a connected N pieces is a direction staring at (r,c) and in a direction determined by rmod and cmod
bool GameImpl::connectedN(int c, int r, int cmod, int rmod) const
{
    int color = m_scaffold.checker(c, r);
	
    for (int i = 0; i < m_win; i++)
	{
        if (m_scaffold.checker(c+(i*cmod), r+(i*rmod))!=color)	//checks if each piece starting at (r,c)
		{														//and going in a direction determined by rmod and cmod
            return false;										//is the same color as the color of (r,c)
		}
	}
	
    return true;
}

//checks to see if the game has been won or if there is a tie, or if the game is not over
// changes m_winner to reflect the endgame condition
bool GameImpl::completed(int& winner) const
{
	for(int r=1; r<=m_scaffold.rows(); r++)
	{
		for(int c=1; c<=m_scaffold.cols(); c++)
		{
			if(checker(c, r)==RED && m_turn%2==0)			// red just played, currently black's turn,
			{												// so check for red win
				if(checkWin(c, r))		//red win
				{
					winner=RED;
					return true;
				}
					
			}
			
			else if(checker(c, r)==BLACK && m_turn%2==1)	// Black just played, currently red's turn,
			{												// so check for black win
				if(checkWin(c, r))		//black win
				{
					winner=BLACK;
					return true;
				}
			}
		}
	}
	
	
	if(m_scaffold.numberEmpty()==0)		//no winner and board is full, therefore tie game
	{
		winner=TIE_GAME;
		return true;
	}
	
    return false;					//board is not full and no winner, therefore game is not over
}

//completes one players turn
bool GameImpl::takeTurn()
{
	if(completed(m_winner))		//checkif game is over
	{
		return false;
	}
	
	if(m_turn%2==1)		//red's turn
	{
		cout << m_red->name() << "'s turn" << endl;
		m_scaffold.makeMove(m_red->chooseMove(m_scaffold, m_win, RED) , RED);		//make red's move
		m_turn++;
		return true;
	}
	
	else				//black's turn
	{
		cout << m_black->name() << "'s turn" << endl;
		m_scaffold.makeMove(m_black->chooseMove(m_scaffold, m_win, BLACK) , BLACK);	//make black's move
		m_turn++;
		return true;
	}
}

//plays the game
void GameImpl::play()
{
	cout << "Connect " << m_win << endl;				//intro messages
	cout << m_red->name() << " is red." << endl;
	cout << m_black->name() << " is black." << endl;
	
	m_scaffold.display();
	while(!completed(m_winner))		//make sure the game isn't over
	{
		takeTurn();					//take a turn
		m_scaffold.display();		//display the scaffold to see what happened during the turn
		
		if(!(m_red->isInteractive()) && !(m_black->isInteractive()))	//if both players are computers, allow user
		{																//to control progress through game
			cout << " Press enter to continue" << endl;
			cin.ignore();
		}
		cout << endl;
	}
	
	if(m_winner==RED)								//print out message reflecting game outcome
	{
		cout << m_red->name() << " wins!" << endl;
	}
	
	if(m_winner==BLACK)
	{
		cout << m_black->name() << " wins!" << endl;
	}
	
	if(m_winner==TIE_GAME)
	{
		cout << "Tie game!" << endl;
	}
}

//returns the color of the piece at (r,c)
int GameImpl::checker(int c, int r) const
{
    return m_scaffold.checker(c, r);	//just call scaffolds checker function
} 

//******************** Game functions *******************************

// These functions simply delegate to GameImpl's functions.
// You probably don't want to change any of this code.

Game::Game(const Scaffold& s, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(s, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checker(int c, int r) const
{
    return m_impl->checker(c, r);
}
