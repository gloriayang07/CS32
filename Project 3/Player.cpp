#include "Player.h"
#include "Board.h"
#include <iostream>



//Player implementations

Player::Player(std::string name):m_name(name)
{}

std::string Player::name() const
{
	return m_name;
}

bool Player::isInteractive() const
{
	return false;
}

Player::~Player()
{}


//Human Player

HumanPlayer::HumanPlayer(std::string name) : Player(name)
{}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	int input;
	cout << "Enter hole number: ";
	std::cin >> input;
	while (input < 1 || input > b.holes())		//make sure hole is in range
	{
		cout << "Enter valid number"<<endl;
		std::cout << "Enter hole number: ";
		std::cin >> input;
	}
	while (b.beans(s, input) == 0)	//make sure hole is not empty
	{
		cout << "There are no beans in that pot" << endl;
		std::cout << "Enter hole number: ";
		std::cin >> input;
	}

	return input;
}

bool HumanPlayer::isInteractive() const
{
	return true;
}


HumanPlayer::~HumanPlayer()
{}


//Bad Player

BadPlayer::BadPlayer(std::string name) : Player(name)
{}

int BadPlayer::chooseMove(const Board& b, Side s) const
{

	for (int i = 1; i <= b.holes(); i++)	//alwas choose leftmost (on either side) hole that is not empty
	{
		if (b.beans(s, i) != 0)
			return i;
	}
	return -1;
}
BadPlayer::~BadPlayer()
{}


//Smart Player

SmartPlayer::SmartPlayer(std::string name) : Player(name)
{
}


int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	int bestHole = 0;

	int tempV = 0;
	int value = 0;

	AlarmClock ac(4900);	//start timer


	for (int i = 1; i <= b.holes(); i++)
	{
		miniMax(b, s, i, value, ac);
		if (s == SOUTH)
		{
			if (tempV > value)	//Southside value goes to +infinity
			{
				value = tempV;
				bestHole = i;
			}
		}
		else if (s == NORTH)
		{
			if (value<tempV)	//Northside value goes to +infinity
			{
				value = tempV;
				bestHole = i;
			}
		}
		
	}

	if (b.beans(s, bestHole) == 0 || bestHole == 0)			//if bestHole is invalid, set to arbituary hole
	{
		for (int i = 1; i <= b.holes(); i++)
		{
			if (b.beans(s, i) != 0)
			{
				bestHole = i;
				break;
			}
		}
	}
	return bestHole;
}

SmartPlayer::~SmartPlayer()
{}

int SmartPlayer::miniMax(const Board& b, Side s, int& bestHole, int & value, AlarmClock& ac) const
{
	int endHole;
	int v2;
	Side endSide;
	Board copy(b);
	if (ac.timedOut())	//check for time //base case 1 is if there is enough time
	{
		value = b.beans(SOUTH, POT) - b.beans(NORTH, POT);
		return value;
	}
	

	if (b.beansInPlay(s) == 0 || b.beansInPlay(opponent(s)) == 0)	//base case2 is when the end of the game is reached
	{

		for (int i = 1; i <= copy.holes(); i++)	//move remaining beans into puts
		{
			copy.moveToPot(opponent(s), i, opponent(s));
			copy.moveToPot(s, i, s);
		}
		value = copy.beans(SOUTH, POT) - copy.beans(NORTH, POT); //heuristic value is difference between beans in pots
		return value;
	}

	for (int j = 1; j <= b.holes(); j++)
	{
		if (copy.beans(s, j) == 0)	//skip pver if no beans in hole
			continue;

		copy.sow(s, j, endSide, endHole);	//sow beans in hole

		if (endSide == s && endHole == POT)	//if endHole is a pot, switch sides (will be switched back later, so no overall change in side
		{
			s = opponent(s);
		}

		if (endSide == s && endHole != POT)	//capture
		{
			if (copy.beans(s, endHole) == 0 && copy.beans(opponent(s), endHole) != 0)
			{
				copy.moveToPot(s, endHole, s);
				copy.moveToPot(opponent(s), endHole, opponent(s));
			}
		}
		v2 = miniMax(copy, opponent(s), bestHole, value, ac);	//call function on next move after current move


		if (s == SOUTH)
		{
			if (v2 > value)	//greatest value is at +infnity
			{
				bestHole = j;
				value = v2;	//value is set to largest possible value
			}
		}
		else if (s == NORTH)
		{
			if (value < v2)	//greatest value is at -infnity
			{
				bestHole = j;
				v2 = value;	//value is set to largest possible value
			}
		}
	}
	return value;
}