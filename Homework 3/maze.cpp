#include <iostream>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec)
		return true;
	int row = sr;
	int col = sc;
	maze[row][col] = '@';
	if (maze[row + 1][col] != 'X' && maze[row + 1][col] != '@')
	{
		if (pathExists(maze, row + 1, col, er, ec))
			return true;
	}
	if (maze[row][col - 1] != 'X' &&maze[row][col - 1] != '@')
	{
		if (pathExists(maze, row, col - 1, er, ec))
			return true;
	}
	if (maze[row - 1][col] != 'X' &&maze[row - 1][col] != '@')
	{
		if (pathExists(maze, row - 1, col, er, ec))
			return true;
	}
	if (maze[row][col + 1] != 'X' &&maze[row][col + 1] != '@')
	{
		if (pathExists(maze, row, col + 1, er, ec))
			return true;
	}
	return false;
}

