// mazestack.cpp


#include <iostream>
#include <stack>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};


bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise



bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;
	Coord current(sr, sc);
	Coord start(sr, sc);
	Coord end(er, ec);
	
	//Push the starting coordinate (sr,sc) onto the coordinate stack and
		//update maze[sr][sc] to indicate that the algorithm has encountered
		//it (i.e., set maze[sr][sc] to have a value other than '.').
	coordStack.push(start);
	maze[sr][sc]='o';
	
	//While the stack is not empty,
	while(!coordStack.empty())
	{   
		//Pop the top coordinate off the stack. This gives you the current
			//(r,c) location that your algorithm is exploring.
		current=coordStack.top();
		coordStack.pop();
		
		
	    //If the current (r,c) coordinate is equal to the ending coordinate,
			//then we've solved the maze so return true! 
		if(current.r()==end.r() && current.c()==end.c())
		{
			return true;
		}
		
	    //Check each place you can move from the current cell:
			//If you can move NORTH and haven't encountered that cell yet,
				//then push the coordinate (r-1,c) onto the stack and update
				//maze[r-1][c] to indicate the algorithm has encountered it.
		if(maze[current.r()-1][current.c()]=='.')
		{
			coordStack.push(Coord(current.r()-1, current.c()));
			maze[current.r()-1][current.c()]='o';
		}
		
			//If you can move EAST and haven't encountered that cell yet,
				//then push the coordinate (r,c+1) onto the stack and update
				//maze[r][c+1] to indicate the algorithm has encountered it.
		if(maze[current.r()][current.c()+1]=='.')
		{
			coordStack.push(Coord(current.r(), current.c()+1));
			maze[current.r()][current.c()+1]='o';
		}
		
			//If you can move SOUTH and haven't encountered that cell yet,
				//then push the coordinate (r+1,c) onto the stack and update
				//maze[r+1][c] to indicate the algorithm has encountered it.
		if(maze[current.r()+1][current.c()]=='.')
		{
			coordStack.push(Coord(current.r()+1, current.c()));
			maze[current.r()+1][current.c()]='o';
		}
		
			//If you can move WEST and haven't encountered that cell yet,
				//then push the coordinate (r,c-1) onto the stack and update
				//maze[r][c-1] to indicate the algorithm has encountered it.
		if(maze[current.r()][current.c()-1]=='.')
		{
			coordStack.push(Coord(current.r(), current.c()-1));
			maze[current.r()][current.c()-1]='o';
		}
		
	}
	
	//There was no solution, so return false
	return false;
}

int main()
{
	char maze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X'},
		{ 'X','.','.','.','.','X','.','.','.','X'},
		{ 'X','.','X','X','.','X','X','.','.','X'},     //north east south west
		{ 'X','.','X','.','.','.','X','.','.','X'},
		{ 'X','X','X','X','X','.','X','.','.','X'},
		{ 'X','.','X','.','.','.','X','.','.','X'},
		{ 'X','.','.','.','X','.','X','.','.','X'},
		{ 'X','X','X','X','X','.','X','X','X','X'},
		{ 'X','.','.','.','.','.','.','.','.','X'},
		{ 'X','X','X','X','X','X','X','X','X','X'}
	};
	
	if (pathExists(maze,1,1,8,8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}