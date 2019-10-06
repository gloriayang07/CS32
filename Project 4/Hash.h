#ifndef HASH
#define HASH

#include <iostream>
#include <string>
#include <functional>
using namespace std;

const int num_buckets = 150001;

struct Node
{
	Node(string data, int offset);
	string data;
	int offset;
	Node* next;
};

class HashTable
{
public:
	HashTable();
	~HashTable();
	void add(string add, int offset);

	int find(string f);

private:
	int hashFunc(const string& hashMe)
	{
		hash<string> stringHash;
		unsigned int hashValue = stringHash(hashMe);
		unsigned int bucketNum = hashValue % num_buckets;
		return bucketNum;
	}
	
	Node* m_buckets[num_buckets];
};

#endif // !HASH
