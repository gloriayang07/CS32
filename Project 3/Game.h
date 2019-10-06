#ifndef game
#define game

class Player;
#include "Board.h"

class Game 
{
public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move();
	void play();
	int beans(Side s, int hole) const;
private:
	Board m_bd;
	Player* m_player1;
	Player* m_player2;
	Player* m_current;
	int m_endH;
	Side m_endS;
	Side m_playerSide;
	Side m_winner;
	bool m_hasWinner;
	void changePlayers(); //swap players function only used in Game
};


#endif // !game
