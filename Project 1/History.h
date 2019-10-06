#ifndef History_defined
#define History_defined
#include"globals.h"
class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;

private:
	char m_hGrid[MAXROWS][MAXCOLS];
	int m_hRows;
	int m_hCols;
};
#endif // !History_defined
