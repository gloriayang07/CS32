#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole)
{
	if (nHoles < 1)
		nHoles = 1;
	if (nInitialBeansPerHole < 0)
		nInitialBeansPerHole = 0;
	m_numHoles = nHoles;
	m_nBeans = nHoles * nInitialBeansPerHole;
	m_nSide.push_back(0);
	m_sSide.push_back(0);
	for (int i = 0; i < nHoles; i++)
	{
		m_nSide.push_back(nInitialBeansPerHole);
		m_sSide.push_back(nInitialBeansPerHole);
	}
	

	//construct board

}

int Board::holes() const
{
	return m_numHoles;
}

int Board::beans(Side s, int hole) const
{
	if (hole < 0 || hole > m_numHoles)	//invalid hole number
		return -1;
	if (s == SOUTH)
		return m_sSide[hole];
	else if (s == NORTH)
		return m_nSide[hole];
	else
		return -1;
}

int Board::beansInPlay(Side s) const
{
	int total = 0;
	//calculate realtime no. of beans in play
	if (s == NORTH)
	{
		for (int i = 1; i <= m_numHoles; i++)
			total += m_nSide[i];
	}
	else if (s == SOUTH)
	{
		for (int i = 1; i <= m_numHoles; i++)
			total += m_sSide[i];

	}
	else
		return -1;

	return total;
}

int Board::totalBeans() const
{
	int total = 0;
	//calculate realtime no. of beans in play
	for (int i = 0; i <= m_numHoles; i++)
	{
		total += m_nSide[i];
		total += m_sSide[i];
	}
	return total;
}


bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	if (beans(s,hole) < 1)
		return false;
	if (hole < 1 || hole > holes())
		return false;
	//sow beans
	Side temp = s; //make a copy to switch sides
	int nBeans = beans(s, hole);

	if (s == SOUTH)
	{
		m_sSide[hole] = 0;
		hole++;
	}
	else if (s == NORTH)
	{
		m_nSide[hole] = 0;
		hole--;
	}
	else
		return false;

	while (nBeans > 0)
	{
		if (temp == NORTH)
		{

			for (; nBeans > 0; nBeans--) //move beans counter clockwise (so large to small)
			{
				if (hole < 1)
					break;
				m_nSide[hole] += 1;
				endHole = hole;
				hole--;
			}
			if (nBeans > 0 && s == NORTH)
			{ 
				m_nSide[POT] += 1;//add to own pot if there are more beans
				endHole = POT;
				nBeans--;
			}
			endSide = NORTH;
		}
		if (temp == SOUTH)
		{
			for (;nBeans > 0; nBeans--) //move beans counter clockwise (so small to large)
			{
				if (hole > m_numHoles)
					break;
				m_sSide[hole] += 1;
				endHole = hole;
				hole++;

			}
			if (nBeans > 0 && s == SOUTH)
			{ 
				m_sSide[POT] += 1;//add to own pot if encountered there are more beans
				endHole = POT;
				nBeans--;
			}
			endSide = SOUTH;

		}
		if (nBeans > 0)
		{
			temp = opponent(temp);	// switch sides
			if (temp == SOUTH)
				hole = 1;
			else
				hole = holes();
		}
	}
	return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	if (hole < 1 || hole > m_numHoles)
		return false;
	if (s == NORTH)
	{
		if (potOwner == NORTH)
			m_nSide[POT] += m_nSide[hole]; //add to pot
		else if (potOwner == SOUTH)
			m_sSide[POT] += m_nSide[hole]; //add to pot
		m_nSide[hole] = 0;
	}
	else if (s == SOUTH)
	{
		if (potOwner == NORTH)
			m_nSide[POT] += m_sSide[hole]; //add to pot
		else if (potOwner == SOUTH)
			m_sSide[POT] += m_sSide[hole]; //add to pot
		m_sSide[hole] = 0;
	}
	else
		return false;
	return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole > m_numHoles || hole < 0)	//invalid hole number
		return false;
	if (s == NORTH)
		m_nSide[hole] = beans;
	else if (s == SOUTH)
		m_sSide[hole] = beans;
	else
		return false;
	return true;
}

