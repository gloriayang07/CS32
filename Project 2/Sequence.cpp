#include "Sequence.h"
using namespace std;

Sequence::Node::Node() //constructor for Node
{
	next = nullptr;
	prev = nullptr;
}

Sequence::Sequence()	
	: m_size(0)
{
	this->m_h = new Node();
	m_h->next = m_h;
	m_h->prev = m_h;
}

Sequence::~Sequence()
{
	while (m_h != m_h->next)
	{
		Node *n = m_h->next;
		m_h->next = n->next;	//head now points to next element
		delete n;	//deletes previous element
	}
	delete m_h;	//delete head
}
Sequence::Sequence(const Sequence& other)	//copy constructor
{
	m_h = new Node;
	m_h->next = m_h;	
	m_h->prev = m_h;
	int size = other.size();
	for (int i = 0; i < size; i++)
	{
		ItemType temp;
		other.get(i, temp);
		insert(i,temp);
	}
	m_size = other.size();
}

Sequence& Sequence::operator=(const Sequence& value)	//assignment operator
{
	if (this != &value)
	{
		Sequence temp(value);
		swap(temp);
	}
	return *this;
}

int Sequence::size() const
{
	return m_size;
}

bool Sequence::empty() const
{
	return (m_size == 0);
}

int Sequence::insert(int pos, const ItemType& value)
{
	if (pos < 0 || pos > size() )	
		return -1;

	Node *temp = new Node();	//create new node to insert
	temp->m_data = value;

	int count = 0;
	Node *current = m_h->next;
	for (int i = 0; i < pos; i++)	//iterate list to correct position
	{
		current = current->next;
		count++;
	}
	temp->next = current;	//adjust pointers
	temp->prev = current->prev;
	temp->prev->next = temp;
	current->prev = temp;
	m_size++;

	if (pos == size()) // if end of list, adjust pointers so that end of list points to head
	{
		current->next = m_h;
		m_h->prev = current;
	}
	return pos;
}

int Sequence::insert(const ItemType& value)
{
	Node *current = m_h->next;
	int pos = 0;
	while (value > current->m_data && current != m_h)	
	{
		current = current->next;
		pos++;
	}
	insert(pos, value);
	return pos;
}

bool Sequence::erase(int pos)
{
	if (pos < 0 || pos >= size())
		return false;
	Node* current = m_h->next;
	for (int i = 0; i < pos; i++)
	{
		current = current->next;
	}
	if (current != m_h)
	{
		Node* temp = current->prev;
		current->next->prev = temp;	//adjust pointers
		current->prev->next = temp->next->next;
		delete current;
		m_size--;
		return true;
	}

	return false;
}

int Sequence::remove(const ItemType& value)
{
	int keepPos = find(value);
	if (keepPos == -1)
		return 0;
	int count = 0;
	while (keepPos != -1)	//while value still exists in sequence
	{
		erase(keepPos);
		count++;
		keepPos = find(value);
	}
	return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (pos < 0 || pos >= size())
		return false;
	Node* current = m_h->next;
	for (int i = 0; i < pos; i++)
		current = current->next;
	value = current->m_data;
	return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (pos < 0 || pos >= size())
		return false;
	Node* current = m_h->next;
	for (int i = 0; i < pos; i++)
		current = current->next;
	current->m_data = value;
	return true;
}

int Sequence::find(const ItemType& value) const
{
	Node * current = m_h->next;
	for (int i = 0; i <= size(); i++)
		if (current->m_data == value)
			return i;
	return -1;
}

void Sequence::swap(Sequence& other)
{
	// Swap elements.  Since the only elements that matter are those up to
	// m_size and other.m_size, only they have to be moved.
	Node * temp = m_h;	//switch head pointers
	m_h = other.m_h;
	other.m_h = temp;

	int tempSize = m_size;	//switch sizes
	m_size = other.m_size;
	other.m_size = tempSize;

}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	ItemType val1, val2;
	int count = 0;
	for (int i = 0; i < seq1.size(); i++)	//for each element of seq1, look for subsequence
	{
		seq1.get(i, val1);
		seq2.get(0, val2);
		while (val2 == val1)	//compare proceeding values
		{
			
			count++;
			seq1.get(i + count, val1);
			seq2.get(count, val2);
			if (count == seq2.size())
			{
				return i;	//return position that subsequence exists
			}

		}
		count = 0;	//if one of them does not match, reset and move to next value to seq1
			
		

	}
	return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	ItemType val1, val2;
	Sequence t;

	int p = 0;
	int rPos = 0;
	int tSize = seq1.size() + seq2.size();
	while (rPos < tSize)
	{
		if (seq1.get(p, val1))	//insert if not end of list
		{
			t.insert(rPos, val1);
			rPos++;
		}


		if (seq2.get(p, val2))	//insert if not end of list
		{

			t.insert(rPos, val2);
			rPos++;
		}
		p++;
	}
	result = t;
}
