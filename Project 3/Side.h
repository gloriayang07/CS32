#ifndef side_defined
#define side_defined

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
	return Side(NSIDES - 1 - s);
}

class Board;
class Player;

#endif // !side_defined
