#include "Sequence.h"
#include <string>
#include <cassert>
#include<iostream>
using namespace std;


int main()
{
	//Sequence ss;  // ItemType is std::string
	//ss.insert(0, "aaa");
	//ss.insert(1, "bbb");
	//ss.insert(2, "ccc");

	//ItemType x = "xxx";
	//assert(!ss.get(3, x) && x == "xxx");  // x is unchanged
	//assert(ss.get(1, x) && x == "bbb");
	//assert(ss.get(2, x) && x == "ccc");
	//assert(ss.erase(1) == true);
	//assert(ss.get(1, x) && x == "ccc");
	//assert(ss.find("aaa") == 0);
	//ss.insert("aaa");

	//assert(ss.get(0, x) && x == "aaa");
	//assert(ss.get(1, x) && x == "aaa");
	//assert(ss.remove("aaa") == 2);

	//assert(ss.get(0, x) && x ==  "ccc");

	//Sequence aa;
	//aa.insert("a");
	//aa.insert("b");
	//aa.insert("c");
	//
	//ss.swap(aa);

	//assert(aa.get(0, x) && x == "ccc");

	//assert(ss.get(0, x) && x == "a");
	//
	//assert(ss.get(1, x) && x == "b");
	//assert(ss.get(2, x) && x == "c");
	//x = "d";
	//assert(ss.set(2, x) == true && ss.get(2,x) && x =="d");
	//assert(ss.set(3, x) == false);
	Sequence a;
	a.insert(0, 30);
	a.insert(1, 21);
	a.insert(2, 63);
	a.insert(3, 42);
	a.insert(4, 17);
	a.insert(5, 63);
	a.insert(6, 17);
	a.insert(7, 29);
	a.insert(8, 8);
	a.insert(9, 32);

	Sequence b;
	b.insert(0, 63);
	b.insert(1, 17);
	b.insert(2, 29);
	assert(subsequence(a, b) == 5);	//checking if subsequence returns correct value

	Sequence c;
	c.insert(0, 17);
	c.insert(1, 63);
	c.insert(2, 29);


	assert(subsequence(a, c) == -1);	//checking if subsequence returns correct value

	Sequence d;
	interleave(a, b, d);
	ItemType x;
	d.get(1, x);
	cout << x;
	assert(d.get(1, x) == true && x == 63);	//check if value is interleaved at the correct place
	assert(d.get(6, x) == true && x == 42);	//when seq2 ends, check that rest of seq1 is inserted properly
	assert(d.get(7, x) == true && x == 17);
	assert(d.get(8, x) == true && x == 63);

	interleave(a, b, a);
	assert(a.get(1, x) == true && x == 63);	//same behavior even with input sequence as output
	assert(a.get(6, x) == true && x == 42);
	assert(a.get(7, x) == true && x == 17);
	assert(a.get(8, x) == true && x == 63);
	
	Sequence e(c);							//test copy constructor with existing sequnce c (consisting of 17, 63 29)
	assert(e.get(0, x) == true && x == 17);
	assert(e.get(1, x) == true && x == 63);
	assert(e.get(2, x) == true && x == 29);
	assert(e.get(3, x) == false);
	assert(e.size() == 3);	//test that size is the same

}
