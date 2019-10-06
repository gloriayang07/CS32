#include <iostream>
#include <string>
#include <functional>
#include "Hash.h"
using namespace std;

//class implemntations for Hash.h

Node::Node(string data, int offset)
	: data(data), offset(offset), next(nullptr)
{}
//constructor
HashTable::HashTable()
{
	for (int i = 0; i < num_buckets; i++)
	{
		m_buckets[i] = nullptr;
	}
}
//destructor
HashTable::~HashTable()
{
	for (int i = 0; i < num_buckets; i++)
	{
		if (m_buckets[i] != nullptr)
		{
			while (m_buckets[i]->next != nullptr)
			{
				Node* temp = m_buckets[i];
				m_buckets[i] = m_buckets[i]->next;
				delete temp;
			}
		}
		delete m_buckets[i];
	}
}



void HashTable::add(string add, int offset)
{
	unsigned int bucket = hashFunc(add);

	Node *& insert = m_buckets[bucket];
	if (insert == nullptr) //if no collisions
		insert = new Node(add, offset);
	else
	{
		//add to end of link list is there are collisions
		Node* temp = new Node(add, offset);	
		Node* last = insert;
		while (last->next)
		{
			last = last->next;
		}
		last->next = temp;
	}
}


int HashTable::find(string f)
{
	if (f.empty())
		return -1;
	int hash = hashFunc(f);
	Node* pointer = m_buckets[hash];
	if (pointer == nullptr)
		return -1;
	while (pointer->next != nullptr) //look through linked list at hased location to find matching string
	{
		if (pointer->data == f)
		{
			return pointer->offset;
		}
		pointer = pointer->next;
	}
	if (pointer->data == f) //check if pointer at end of linked list has matching data
	{
		return pointer->offset;
	}
	return -1;
}
