#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std; 

Game::Game(const Board& b, Player* south, Player* north) : m_bd(b), m_player1(south), m_player2(north), m_current(south)
{
	m_endH = 0;
	m_endS = SOUTH;
	m_playerSide = SOUTH;
	m_hasWinner = false;
}

void Game::display() const
{
	cout << "-----------------North-----------------" << endl;
	cout << "                      ";
	for (int i = 1; i <= m_bd.holes(); i++)
		cout << m_bd.beans(NORTH, i) << "  ";
	cout << endl << m_player2->name() <<"(N)'s pot " << m_bd.beans(NORTH, 0) << "                    " << m_bd.beans(SOUTH, 0) << " " << m_player1->name() << " (S)'s pot" << endl;
	cout << "                      ";
	for (int i = 1; i <= m_bd.holes(); i++)
		cout << m_bd.beans(SOUTH, i) << "  ";
	cout << endl << "-----------------South-----------------" << endl;
	cout << "==========================================================" << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	if (m_bd.beansInPlay(NORTH) == 0 || m_bd.beansInPlay(SOUTH) == 0)
		over = true;
	else
		over = false;
	if (!over)
	{
		return;	//dont change the rest of the parameters
	}

	int North = m_bd.beans(NORTH, POT);
	int South = m_bd.beans(SOUTH, POT);
	hasWinner = true;	
	if (North == South)		//if equal beans in both pots, no winner
	{
		hasWinner = false;	
		return;
	}
	if (North > South)
		winner = NORTH;
	else
		winner = SOUTH;
		
}
bool Game::move()
{
	bool isOver;
	status(isOver, m_hasWinner, m_winner);	//checks for beans in both sides
	if (isOver)
	{
		for (int i = 0; i <= m_bd.holes(); i++)
		{
			m_bd.moveToPot(NORTH, i, NORTH);	
			m_bd.moveToPot(SOUTH, i, SOUTH);
		}
		status(isOver, m_hasWinner, m_winner);
		return false;
	}
	int n = m_current->chooseMove(m_bd, m_playerSide);
	cout << m_current->name() << " has chosen hole " << n << endl;
	if (m_bd.sow(m_playerSide, n, m_endS, m_endH))
	{
		display();
		
		if (m_endS == m_playerSide && m_endH !=0)
			
		{
			if (beans(m_endS, m_endH) == 1 && beans(opponent(m_endS), m_endH) != 0) //was empty moments before
			{
				m_bd.moveToPot(opponent(m_playerSide), m_endH, m_playerSide);
				m_bd.moveToPot(m_playerSide, m_endH, m_playerSide);
				cout << "Capture!" << endl;
				display();
			}

		}
		if (m_endS == m_playerSide && m_endH == POT)	//lands in pot
		{
			cout << "Player gets another turn" << endl;
			
			changePlayers(); //make another turn, or else side will be switched to opponents later

		}
		changePlayers();
	}
	else
	{
		cout << m_current->name() << " has not made a move" << endl;
		changePlayers();
		return true;
	}
	status(isOver, m_hasWinner, m_winner);	//check status after move
	if (isOver)
	{
		for (int i = 1; i <= m_bd.holes(); i++)
		{
			m_bd.moveToPot(NORTH, i, NORTH);	//move all beans to pots
			m_bd.moveToPot(SOUTH, i, SOUTH);
		}
		status(isOver, m_hasWinner, m_winner);
	}
	return true;
}
void Game::play()
{
	display();
	bool status = true;
	while (status) {
		if (!m_player1->isInteractive() && !m_player2->isInteractive())
		{
			cout << "Press Enter to coninue. ";
			cin.ignore();
		}
		status = move();	//keep taking turns until winner is reached
	}
	if (!status)
	{
		display();
		if (m_hasWinner)
		{
			if (m_winner == SOUTH)
				cout << "Winner is " << m_player1->name();	//player 1 is south side
			else
				cout << "Winner is " << m_player2->name(); //player 2 is north side
		}
		else
			cout << "It's a tie!";
	}
	
}
int Game::beans(Side s, int hole) const
{
	return m_bd.beans(s, hole);
}

void Game::changePlayers()	//swap member functions to opposide side
{
	m_playerSide = opponent(m_playerSide);
	if (m_current == m_player1)
		m_current = m_player2;
	else
		m_current = m_player1;
}