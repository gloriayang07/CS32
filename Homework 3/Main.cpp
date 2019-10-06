#include <iostream>
#include <streambuf>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>

using namespace std;



void xxxtestone(int n)
{
	char maze1[10][10] = {
	  { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	  { 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X' },
	  { 'X', '.', 'X', 'X', '.', 'X', '.', 'X', 'X', 'X' },
	  { 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X' },
	  { 'X', 'X', '.', 'X', '.', 'X', '.', '.', '.', 'X' },
	  { 'X', 'X', 'X', '.', '.', 'X', '.', 'X', '.', 'X' },
	  { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
	  { 'X', '.', 'X', 'X', '.', '.', 'X', '.', 'X', 'X' },
	  { 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X' },
	  { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	};

	char maze2[10][10] = {
	  { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	  { 'X', '.', 'X', '.', '.', 'X', '.', '.', '.', 'X' },
	  { 'X', 'X', 'X', 'X', '.', 'X', '.', 'X', 'X', 'X' },
	  { 'X', '.', '.', '.', '.', 'X', '.', 'X', '.', 'X' },
	  { 'X', 'X', '.', 'X', '.', 'X', '.', '.', '.', 'X' },
	  { 'X', 'X', 'X', '.', '.', 'X', '.', 'X', '.', 'X' },
	  { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
	  { 'X', '.', 'X', 'X', '.', '.', 'X', '.', 'X', 'X' },
	  { 'X', '.', '.', '.', '.', 'X', '.', '.', '.', 'X' },
	  { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	};

	char maze3[10][10] = {
	  { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	  { 'X', 'X', '.', '.', '.', '.', '.', 'X', 'X', 'X' },
	  { 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X' },
	  { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
	  { 'X', '.', 'X', '.', 'X', 'X', 'X', '.', '.', 'X' },
	  { 'X', 'X', 'X', 'X', '.', '.', 'X', '.', '.', 'X' },
	  { 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X' },
	  { 'X', '.', '.', '.', '.', '.', '.', '.', 'X', 'X' },
	  { 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	  { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	};

	char maze4[10][10] = {
	  { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	  { 'X', 'X', '.', '.', '.', '.', '.', 'X', 'X', 'X' },
	  { 'X', '.', '.', 'X', 'X', '.', '.', '.', '.', 'X' },
	  { 'X', '.', '.', '.', 'X', '.', '.', '.', 'X', 'X' },
	  { 'X', '.', 'X', '.', 'X', 'X', 'X', '.', '.', 'X' },
	  { 'X', 'X', 'X', 'X', '.', '.', 'X', '.', '.', 'X' },
	  { 'X', 'X', '.', '.', '.', '.', 'X', '.', '.', 'X' },
	  { 'X', '.', 'X', '.', '.', '.', '.', '.', 'X', 'X' },
	  { 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	  { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
	};

	string a[10] = { "", "", "#", "", "#", "", "#", "#", "", "" };
	string x[10] = { "2", "7", "4", "8", "#", "0", "#", "#", "9", "6" };
	string y[10] = { "8", "10", "0", "9", "4", "5", "#", "2", "12", "6" };
	string b[4] = { "10", "0", "4", "2" };
	string c[8] = { "1", "9", "7", "3", "9", "7", "5" };
	string d[12] = { "1", "3", "7", "1", "7", "5", "3", "1", "7", "9", "7", "5" };
	string f[16] = { "4", "7", "0", "f", "2", "4", "5", "e", "a", "1", "0", "6", "c", "e", "4", "8" };
	string g[16] = { "0", "0", "1", "2", "4", "4", "4", "5", "6", "7", "8", "a", "c", "e", "e", "f" };

	switch (n)
	{

		assert(includes(y, 10, b, 4));
			} break; case 32: {
		assert(includes(y + 1, 9, b, 4));
			} break; case 33: {
		assert(!includes(y + 2, 8, b, 4));
			} break; case 34: {
		assert(!includes(y + 1, 6, b, 4));
			} break; case 35: {
		assert(includes(y + 1, 7, b, 4));
			} break; case 36: {
		assert(includes(y, 10, b + 2, 1));
			} break; case 37: {
		assert(includes(y + 1, 9, b, 1));
			} break; case 38: {
		assert(!includes(y + 2, 8, b, 1));
			} break; case 39: {
		assert(includes(y, 10, b, 0));
			} break; case 40: {
		assert(includes(y, 0, b, 0));
			} break; case 41: {
		assert(includes(y + 1, 2, b, 2));
			} break; case 42: {
		assert(!includes(y + 2, 2, b + 1, 2));
			} break; case 43: {
		assert(!includes(y + 2, 2, b + 1, 3));
			} break; case 44: {
		assert(!includes(y + 1, 1, b, 2));
			} break; case 45: {
		assert(!includes(y + 1, 0, b, 1));
			} break; case 46: {
		assert(includes(c, 7, d + 3, 3));
			} break; case 47: {
		assert(!includes(c, 7, d + 6, 3));
			} break; case 48: {
		assert(includes(c, 7, d + 9, 3));
			} break; case 49: {
		assert(countIncludes(c, 0, d, 0) == 1);
			} break; case 50: {
		assert(countIncludes(c, 7, d, 0) == 1);
			} break; case 51: {
		assert(countIncludes(c, 2, d + 2, 1) == 0);
			} break; case 52: {
		assert(countIncludes(c, 7, d, 3) == 1);
			} break; case 53: {
		assert(countIncludes(c, 7, d + 3, 3) == 2);
			} break; case 54: {
		assert(countIncludes(c, 7, d + 6, 3) == 0);
			} break; case 55: {
		assert(countIncludes(c, 7, d + 9, 3) == 3);
			} break; case 56: {
		assert(countIncludes(c, 7, d + 2, 1) == 2);
			} break; case 57: {
		auto i = f[0];
		order(f, 1);
		assert(f[0] == i);
			} break; case 58: {
		auto i = f[0];
		order(f, 0);
		assert(f[0] == i);
			} break; case 59: {
		order(f, 16);
		assert(equal(f, f + 16, g));
			} break; case 60: {
		assert(pathExists(maze1, 8, 6, 1, 1));
			} break; case 61: {
		assert(!pathExists(maze2, 8, 6, 1, 1));
			} break; case 62: {
		assert(pathExists(maze3, 4, 3, 7, 1));
			} break; case 63: {
		assert(!pathExists(maze4, 4, 3, 7, 1));
			}
	}
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	xxxtestone(n);
	cout << "Passed" << endl;
}