#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	ScoreList s;
	s.add(20);
	s.add(30);
	s.add(40);
	s.add(25);
	assert(s.maximum() == 40);
	assert(s.minimum() == 20);
	assert(s.remove(20));
	assert(s.minimum() == 25);
	assert(s.size() == 3);
	cout << "Passed all tests" << endl;
}