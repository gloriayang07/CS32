#ifndef Zombie_defined
#define Zombie_defined
class Arena;
class Zombie
{
public:
	// Constructor
	Zombie(Arena* ap, int r, int c);

	// Accessors
	int  row() const;
	int  col() const;

	// Mutators
	void move();
	bool getAttacked(int dir);

private:
	Arena* m_arena;
	int    m_row;
	int    m_col;
	int    m_health;
};
#endif // !Zombie_defined

