bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

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


#include <queue>
#include<iostream>
using namespace std;

int main()
{
	char maze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 3, 5, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	queue<Coord> coordStack;
	Coord start(sr, sc);
	coordStack.push(start);
	maze[sr][sc] = '@';

	int row = sr;
	int col = sc;
	while (!coordStack.empty())
	{
		row = coordStack.front().r();
		col = coordStack.front().c();
		coordStack.pop();

		if (row == er && col == ec) {
			return true;	//path found
		}
			
		if (maze[row + 1][col] != 'X' && maze[row + 1][col] != '@')
		{
			Coord south(row + 1, col);
			coordStack.push(south);
			maze[row + 1][col] = '@';
		}
		if (maze[row][col-1] != 'X' &&maze[row][col-1] != '@')
		{
			Coord west(row, col-1 );
			coordStack.push(west);
			maze[row][col-1] = '@';
		}
		if (maze[row - 1][col] != 'X' &&maze[row - 1][col] != '@')
		{
			Coord north(row - 1, col);
			coordStack.push(north);
			maze[row - 1][col] = '@';
		}
		if (maze[row][col + 1] != 'X' &&maze[row][col+1] != '@')
		{
			Coord east(row, col+1);
			coordStack.push(east);
			maze[row][col+1] = '@';
		}
		

	}
	return false;
}