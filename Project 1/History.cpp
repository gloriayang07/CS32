#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
	:m_hRows(nRows), m_hCols(nCols)
{
	int r, c;
	for (r = 0; r < m_hRows; r++) {
		for (c = 0; c < m_hCols; c++)
			m_hGrid[r][c] = '.'; //initialize all positions to '.'
	}
}

bool History::record(int r, int c)
{

	if ( r<1 || c<1 || c>MAXCOLS || r>MAXROWS)
	{
		return false;
	}
	r--;
	c--;
	if (m_hGrid[r][c] == '.')
	{
		m_hGrid[r][c] = 'A';	//if zombie is killed for the first time, change to 'A'
		return true;
	}
	else if (m_hGrid[r][c] == 'Z') //if zombies killed exceeds 26, do not increment
		return true;
	else
	{
		m_hGrid[r][c]++;	//else, increment number of zombies killed
		return true;
	}

	return true;
}

void History::display() const
{
	clearScreen();
	for (int row = 0; row < m_hRows; row++)
	{
		for (int column = 0; column < m_hCols; column++)
			cout << m_hGrid[row][column];
		cout << endl;
	}
	cout << endl;

}


