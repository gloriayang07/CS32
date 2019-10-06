#include <string>
#include <iostream>
#include <cassert>
using namespace std;
// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then for this value of a2            the function must return
//    "stan" "kenny" "cartman"                      1
//    "stan" "cartman" "butters"                    2
//    "kenny" "stan" "cartman"                      0
//    "kyle" "cartman" "butters"                    3
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
	int count = 0;
	if (n2 < 1)
		return 1;
	if (n1 < 1)
		return count;
	if (a1[0] == a2[0])
		return count = countIncludes(a1 + 1, n1 - 1, a2, n2) + countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	else
		return count = count + countIncludes(a1 + 1, n1 - 1, a2, n2);
}

// Exchange two strings
void exchange(string& x, string& y)
{
	string t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator,
	int& firstNotLess, int& firstGreater)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
	//  Every element earlier than position firstNotLess is < separator
	//  Every element from position firstNotLess to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstGreater-1 is not known yet
	//  Every element at position firstGreater or later is > separator

	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > separator)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < separator)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
	if (n <= 1)
		return;
	int sep = n / 2;
	int low = -1;
	int high = n;

	separate(a, n, a[sep], low, high);
	order(a, low);
	order(a + high, n - high);
	return;  // This is always correct.
}

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

	case 49: {
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
	}break; case 60: {
		order(f, 15);
		assert(equal(f, f + 16, g));
	}
	}
	
}

int main()
{
	while (true) 
	{
		cout << "Enter test number: ";
		int n;
		cin >> n;
		xxxtestone(n);
		cout << "Passed" << endl;
	}
	
}