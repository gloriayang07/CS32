#include <iostream>
#include <fstream>
#include "Hash.h"
#include <cassert>

using namespace std;

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
	HashTable hashTable;
	string oldSequence;
	int offset = 0;
	char t;

	string newSeqeuence{ istreambuf_iterator<char>(fnew), istreambuf_iterator<char>() }; //read all contents of fnew to newSequence

	
	string oldS{ istreambuf_iterator<char>(fold), istreambuf_iterator<char>() };	//copy entire contents of fold into string oldS
	//read file again to hash
	fold.clear();
	fold.seekg(0, ios::beg);

	int longestMatch = 0;
	for (int i = 0; i < newSeqeuence.size(); i++)
	{
		int match = 0;
		for (int j = 0; j < oldS.size(); j++)
		{
			if (newSeqeuence[i] == oldS[j])
			{
				if (i >= newSeqeuence.size())
				{
					break;
				}
				i++;
				match++;
			}
			else
			{
				match = 0;
			}

			if (match > longestMatch)
				longestMatch = match;
		}
	}

	//determine best sequence size (to minimize file size)
	int seqSize;
	if (longestMatch > 1000)
		seqSize = 32;
	else if (longestMatch <= 1000 && longestMatch > 200)
		seqSize = 22;
	else if (longestMatch <= 200 && longestMatch > 50)
		seqSize = 16;
	else
		seqSize = 8;


	string addstr = "";
	string newString;
	string diff;

	if (fold.get(t)) {
		oldSequence += t;	//read first character of fold
		for (int count = 1; count < seqSize && fold.get(t); count++) {	//copy first 8 characters into oldSequence
			oldSequence += t;
		}
		hashTable.add(oldSequence, offset);	//add to hashtable
		offset++;
		while (fold.get(t)) {
			oldSequence = oldSequence.substr(1);	//add one char to oldSequence, take off first char
			oldSequence += t;
			hashTable.add(oldSequence, offset);	//hash sequence
			offset++;
		}
		while (oldSequence.length() >= 1) {	//add remaining sequence into hashtable (even if less than 8 chars)
			oldSequence = oldSequence.substr(1);
			hashTable.add(oldSequence, offset);
			offset++;
		}
	}
	


	int j = 0;
	string addS = "";
	for (; j < newSeqeuence.length() - seqSize; j++)
	{
		newString = newSeqeuence.substr(j, seqSize);
		int foundOffset = hashTable.find(newString);


		if (foundOffset != -1) {
			if (addS != "")	//if there is string to add
			{
				//insert A command
				if (addS[0] == '\n')
				{
					addS = addS.substr(1); //'\n' at beginning does not count 

				}
				diff += '\n';
				diff += 'A';
				int size = addS.size();
				diff += to_string(size);
				diff += ':';
				diff += addS;

				addS = "";
			}
			int length = 0;;
			//j += seqSize;

			for (int i = foundOffset; i < oldS.size(); i++)	//compare chars to find number of consequetive matching chars
			{
				if (oldS[i] == newSeqeuence[j])
				{
					length++;
					j++;

				}
				else
					break;
			}
			j--;
			diff += 'C';	//insert C command
			diff += to_string(length);
			diff += ',';
			diff += to_string(foundOffset);
			addstr = "";


		}

		if (foundOffset == -1)
		{
			addS += newSeqeuence[j];	//add chars to add string
		}

	}

	//check for remianing characters
	for (; j < newSeqeuence.length(); j++)
	{
		addS += newSeqeuence[j];
	}
	if (addS != "")	//if there are charcters to add,
	{
		//add characters to diff file
		diff += 'A';
		diff += to_string(addS.length());
		diff += ':';
		diff += addS;

	}


	fdiff << diff;

}





bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
	string newString = "";
	string oldString{ istreambuf_iterator<char>(fold), istreambuf_iterator<char>() };
	string diff{ istreambuf_iterator<char>(fdiff), istreambuf_iterator<char>() };
	int num = 0;

	for (int i = 0; i < diff.length();)
	{
		switch (diff[i])
		{

		case '\n': case '\r':	//do nothing
		{
			i++;
			break;
		}
			

		case 'A':
		{
			i++;
			num = 0;

			if (diff[i] == ':')	//check that there is a digit between colon and A command
				return false;

			while (diff[i] != ':' && i < diff.length())
			{
				if (!isdigit(diff[i]))	//check that char immediately after A is digit
					return false;
				num = (diff[i] - '0') + (num * 10);	//convert from char to digit
				i++;
			}
			if (diff[i] != ':')	//if no colon is after digit, format is invalid
				return false;
			else
			{
				i++;
				for (int k = 0; k < num; k++, i++)
					newString += diff[i];	//add chars after digit 
			}
			break;
		}
		case 'C':
		{
			num = 0;

			i++;
			if (diff[i] == ',')	//check that there is a digit between comma and C command
				return false;

			num = 0;
			while (diff[i] != ',' && i < diff.length())//check that char immediately after C is digit
			{
				if (!isdigit(diff[i]))
					return false;
				num = (diff[i] - '0') + (num * 10); //convert from char to int
				i++;
			}

			if (diff[i] != ',') //check that format is valid, must find comma after digits
				return false;
			else
			{
				i++;
				if (!isdigit(diff[i]))
					return false;

				int offset = 0;
				while (i < diff.length() && isdigit(diff[i])) {
					offset = (diff[i] - '0') + (offset * 10);	//convert offset from char to int
					i++;
				}
				if (offset >= oldString.length() || offset + num > oldString.length()) {
					return false;
				}
				newString += oldString.substr(offset, num);	//copy num number of chars from fold to newString
			}
			break;
		}
		default:
			return false;	//invalid chaarcter, break
		}
	}
	cerr << "FINAL: " << newString << endl;
	fnew << newString;
	return true;
}

void testCreate()
{
	ifstream smallmart1("/Users/yglor/source/repos/CS32 H4/CS32 H4/smallmart1.txt");
	ifstream smallmart2("/Users/yglor/source/repos/CS32 H4/CS32 H4/smallmart2.txt");
	ofstream smallmartdiff("/Users/yglor/source/repos/CS32 H4/CS32 H4/diff.txt");

	createDiff(smallmart1, smallmart2, smallmartdiff);
	smallmartdiff.close();
}

void testApply()
{
	ifstream smallmartin("/Users/yglor/source/repos/CS32 H4/CS32 H4/smallmart1.txt");
	ifstream smallmartdiff("/Users/yglor/source/repos/CS32 H4/CS32 H4/diff.txt");
	ofstream smallmartout("/Users/yglor/source/repos/CS32 H4/CS32 H4/warandpeace3.txt");

	applyDiff(smallmartin, smallmartdiff, smallmartout);
}

int main()
{
	testCreate();
	testApply();


	/*ifstream greeneggs1("/Users/yglor/source/repos/CS32 H4/CS32 H4/greeneggs1.txt");
	ifstream greeneggs2("/Users/yglor/source/repos/CS32 H4/CS32 H4/greeneggs2.txt");
	ofstream greeneggsdiff("/Users/yglor/source/repos/CS32 H4/CS32 H4/greeneggsdiff.txt");
	createDiff(greeneggs1, greeneggs2, greeneggsdiff);
	greeneggsdiff.close();
	ifstream greeneggsin("/Users/yglor/source/repos/CS32 H4/CS32 H4/greeneggs1.txt");
	ifstream greeneggsdifff("/Users/yglor/source/repos/CS32 H4/CS32 H4/greeneggsdiff.txt");
	ofstream greeneggsout("/Users/yglor/source/repos/CS32 H4/CS32 H4/greeneggs3.txt");

	applyDiff(greeneggsin, greeneggsdifff, greeneggsout);
	cerr << "greeneggs passed" << endl;

	ifstream warandpeace1("/Users/yglor/source/repos/CS32 H4/CS32 H4/warandpeace1.txt");
	ifstream warandpeace2("/Users/yglor/source/repos/CS32 H4/CS32 H4/warandpeace2.txt");
	ofstream warandpeacediff("/Users/yglor/source/repos/CS32 H4/CS32 H4/warandpeacesub.txt");
	createDiff(warandpeace1, warandpeace2, warandpeacediff);
	warandpeacediff.close();
	ifstream warandpeacein("/Users/yglor/source/repos/CS32 H4/CS32 H4/warandpeace1.txt");
	ifstream warandpeacedifff("/Users/yglor/source/repos/CS32 H4/CS32 H4/warandpeacesub.txt");
	ofstream warandpeaceout("/Users/yglor/source/repos/CS32 H4/CS32 H4/warandpeace3.txt");

	applyDiff(warandpeacein, warandpeacedifff, warandpeaceout);
	cerr << "warandpeace passed" << endl;

	ifstream strange1("/Users/yglor/source/repos/CS32 H4/CS32 H4/strange1.txt");
	ifstream strange2("/Users/yglor/source/repos/CS32 H4/CS32 H4/strange2.txt");
	ofstream strangediff("/Users/yglor/source/repos/CS32 H4/CS32 H4/strangesub.txt");
	createDiff(strange1, strange2, strangediff);
	strangediff.close();
	ifstream strangein("/Users/yglor/source/repos/CS32 H4/CS32 H4/strange1.txt");
	ifstream strangedifff("/Users/yglor/source/repos/CS32 H4/CS32 H4/strangesub.txt");
	ofstream strangeout("/Users/yglor/source/repos/CS32 H4/CS32 H4/strange3.txt");

	applyDiff(strangein, strangedifff, strangeout);
	cerr << "strange passed" << endl;*/
}


//int main()
//{
//	ifstream smallmart1("smallmart1.txt");
//	ifstream smallmart2("smallmart2.txt");
//	ofstream smallmartdiff("sub.txt");
//
//	createDiff(smallmart1, smallmart2, smallmartdiff);
//	smallmartdiff.close();
//	ifstream smallmartin("smallmart1.txt");
//	ifstream smallmartdifff("smallmartdiff");
//	ofstream smallmartout("smallmart3.txt");
//
//	applyDiff(smallmartin, smallmartdifff, smallmartout);
//	cerr << "smallmart passed" << endl;
//
//	ifstream greeneggs1("greeneggs1.txt");
//	ifstream greeneggs2("greeneggs2.txt");
//	ofstream greeneggsdiff("sub.txt");
//	createDiff(greeneggs1, greeneggs2, greeneggsdiff);
//	greeneggsdiff.close();
//	ifstream greeneggsin("greeneggs1.txt");
//	ifstream greeneggsdifff("sub.txt");
//	ofstream greeneggsout("greeneggs3.txt");
//
//	applyDiff(greeneggsin, greeneggsdifff, greeneggsout);
//	cerr << "greeneggs passed" << endl;
//
//	ifstream warandpeace1("warandpeace1.txt");
//	ifstream warandpeace2("warandpeace2.txt");
//	ofstream warandpeacediff("sub.txt");
//	createDiff(warandpeace1, warandpeace2, warandpeacediff);
//	warandpeacediff.close();
//	ifstream warandpeacein("warandpeace1.txt");
//	ifstream warandpeacedifff("sub.txt");
//	ofstream warandpeaceout("warandpeace3.txt");
//
//	applyDiff(warandpeacein, warandpeacedifff, warandpeaceout);
//	cerr << "warandpeace passed" << endl;
//
//	ifstream strange1("strange1.txt");
//	ifstream strange2("strange2.txt");
//	ofstream strangediff("sub.txt");
//	createDiff(strange1, strange2, strangediff);
//	strangediff.close();
//	ifstream strangein("strange1.txt");
//	ifstream strangedifff("sub.txt");
//	ofstream strangeout("smallmart3.txt");
//
//	applyDiff(strangein, strangedifff, strangeout);
//	cerr << "strange passed" << endl;
//}

//#include <iostream>
//#include <sstream>  // for istringstream and ostringstream
//#include <string>
//#include <cassert>
//using namespace std;
//
//void runtest(string oldtext, string newtext)
//{
//	istringstream oldFile(oldtext);
//	istringstream newFile(newtext);
//	ostringstream diffFile;
//	createDiff(oldFile, newFile, diffFile);
//	string result = diffFile.str();
//	cout << "The diff file length is " << result.size()
//		<< " and its text is " << endl;
//	cout << result << endl;
//
//}
//
//int main()
//{
//	runtest("There's a bathroom on the right.",
//		"There's a bad moon on the rise.");
//	runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
//		"XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");
//	cout << "All tests passed" << endl;
//}