#include <iostream>
#include <fstream>
#include "Hash.h"
#include <cassert>
using namespace std;

const unsigned int SEQSIZE = 10;
const unsigned int MINSEQSIZE = 1;

void createDiff(istream& fold, istream& fnew, ostream& fdiff) {

	HashTable hashtable;
	string newstr;
	string oldSequence, newSequence, diff;
	char temp = 0;
	int offset = 0;

	if (fold.get(temp)) {
		oldSequence += temp;
		for (int count = 1; count < SEQSIZE && fold.get(temp); count++) {
			oldSequence += temp;
		}
		hashtable.add(oldSequence, offset);
		offset++;
		while (fold.get(temp)) {
			oldSequence = oldSequence.substr(1);
			oldSequence += temp;
			hashtable.add(oldSequence, offset);
			offset++;
		}
		while (oldSequence.length() >= MINSEQSIZE) {
			oldSequence = oldSequence.substr(1);
			hashtable.add(oldSequence, offset);
			offset++;
		}
	}

	pair<int, int> copyRange;
	copyRange.first = -1;
	copyRange.second = -1;
	string addstr = "";

	while (fnew.get(temp)) {
		newstr += temp;
	}
	cout << newstr << endl;
	int j;
	for (j = 0; j < newstr.length() - SEQSIZE + 1; j++) {
		newSequence = newstr.substr(j, SEQSIZE);
		int foundOffset = hashtable.find(newSequence);

		if (foundOffset == -1) {

			addstr += newSequence[0];
		}
		else {
			if (addstr.length() > 0) {
				diff += 'A';
				diff += to_string(addstr.length());
				diff += ':';
				diff += addstr;
				addstr = "";
			}

			copyRange.first = foundOffset;
			copyRange.second = foundOffset + SEQSIZE;
			for (int i = j; i + SEQSIZE < newstr.length() && hashtable.find(newstr.substr(i, SEQSIZE)) != -1; j++)
				copyRange.second++;
			j += (copyRange.second - copyRange.first - 1);


		}
	}


	if (copyRange.second != -1) {
		diff += 'C';
		diff += to_string(copyRange.second - copyRange.first);
		diff += ',';
		diff += to_string(copyRange.first);
		addstr = "";
	}
	else {
		newSequence = newSequence.substr(1);
	}
	diff += 'A';
	diff += to_string(addstr.length() + newSequence.length());
	diff += ':';
	diff += addstr;
	diff += newSequence;


	fdiff << diff;
	cout << diff << endl;

}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew) {
	string old, newstr;
	char temp;
	while (fold.get(temp)) {
		old += temp;
	}
	cout << "OLD: " << old << endl;

	string diff;
	while (fdiff.get(temp)) {
		diff += temp;
	}
	cout << "DIFF: " << diff << endl;

	for (int i = 0; i < diff.length();) {
		if (diff[i] == 'A') {
			i++;
			int numVals = 0;
			// malformed diff file: not long enough, no specified number of chars, no ':'
			while (i < diff.length() && diff[i] != ':') {
				// invalid number of chars
				if (diff[i] < '0' || diff[i] > '9')
					return false;
				numVals = numVals * 10 + (diff[i] - '0');
				i++;
			}

			// never found the ':'
			if (i + 1 >= diff.length())
				return false;
			else {
				i++;
				for (int j = 0; j < numVals; j++, i++)
					newstr += diff[i];
			}
		}
		else if (diff[i] == 'C') {
			i++;
			int numCopied = 0;
			// malformed diff file: not long enough, no specified number of chars, no ','
			while (i < diff.length() && diff[i] != ',') {
				// invalid number of chars
				if (diff[i] < '0' || diff[i] > '9')
					return false;
				numCopied = numCopied * 10 + (diff[i] - '0');
				i++;
			}

			// never found the ','
			if (i + 1 >= diff.length())
				return false;
			else {
				i++;
				// invalid char after comma
				if (diff[i] < '0' || diff[i] > '9')
					return false;
				// find offset
				int offset = 0;
				while (i < diff.length() && (diff[i] >= '0' && diff[i] <= '9')) {
					offset = offset * 10 + (diff[i] - '0');
					i++;
				}
				if (offset > old.length() - 1 || offset + numCopied > old.length()) {
					cerr << "INVALID OFFSET: " << offset << " " << numCopied << " " << old.length() << endl;
					return false;
				}
				newstr += old.substr(offset, numCopied);   // append the copied part
			}

		}
		else if (diff[i] == '\n' || diff[i] == '\r')   // newline or carriage return do nothing
			i++;
		else return false;    // not an add or a copy command, invalid
	}
	cout << "Final: " << newstr << endl;
	fnew << newstr;
	return true;
}

#include <iostream>
#include <sstream>  // for istringstream and ostringstream
#include <string>
#include <cassert>
using namespace std;

void runtest(string oldtext, string newtext)
{
	istringstream oldFile(oldtext);
	istringstream newFile(newtext);
	ostringstream diffFile;
	createDiff(oldFile, newFile, diffFile);
	string result = diffFile.str();
	cout << "The diff file length is " << result.size()
		<< " and its text is " << endl;
	cout << result << endl;

	oldFile.clear();   // clear the end of file condition
	oldFile.seekg(0);  // reset back to beginning of the stream
	istringstream diffFile2(result);
	ostringstream newFile2;
	assert(applyDiff(oldFile, diffFile2, newFile2));
	assert(newtext == newFile2.str());
}

int main()
{
	runtest("There's a bathroom on the right.",
		"There's a bad moon on the rise.");
	runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
		"XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");
	cout << "All tests passed" << endl;
}