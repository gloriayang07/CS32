#include "newSequence.h"
#include <iostream>


Sequence::Sequence()
	:m_numOfItems(0), m_maxNum(DEFAULT_MAX_ITEMS)
{
	m_sequenceItems = new ItemType[m_maxNum];
}

Sequence::Sequence(int num)
	: m_numOfItems(0)
{
	if (num < 0)
	{
		std::cout << "Error: negative max value. ";
		exit(-1);
	}
	else {
		m_maxNum = num;
		m_sequenceItems = new ItemType[m_maxNum];

	}

}
Sequence::~Sequence()
{
	delete[] m_sequenceItems;
}

Sequence::Sequence(const Sequence& other)
{
	m_maxNum = other.m_maxNum;
	m_numOfItems = other.m_numOfItems;
	m_sequenceItems = new ItemType[other.m_maxNum];
	for (int i = 0; i < m_numOfItems; i++)
	{
		m_sequenceItems[i] = other.m_sequenceItems[i];
	}
}

Sequence& Sequence::operator=(const Sequence& value)
{
	if (this != &value)
	{
		Sequence temp(value);
		swap(temp);
	}
	return *this;
}

bool Sequence::empty() const
{
	int s = size();
	if (s == 0)
		return true;
	return false;
}

int Sequence::size() const
{
	return m_numOfItems;
}
int Sequence::insert(int pos, const ItemType& value)
{
	if (pos < 0 || pos > size() || size() == m_maxNum)
		return -1;
	for (int i = size(); i > pos; i--)
	{
		m_sequenceItems[i] = m_sequenceItems[i - 1];
	}
	m_numOfItems++;
	m_sequenceItems[pos] = value;
	return pos;
}
int Sequence::insert(const ItemType& value)
{

	if (size() == m_maxNum)
		return -1;
	if (size() == 0)
	{
		insert(0, value);
		return 0;
	}
	int pos;
	for (int p = 0; p <= size(); p++)
	{
		if (value <= m_sequenceItems[p])
		{
			pos = p;
			break;
		}
		else
		{
			pos = size();
		}
	}
	insert(pos, value);
	return pos;
}
bool Sequence::erase(int pos)
{
	if (pos >= 0 && pos < size())
	{
		for (int i = pos; i < size(); i++)
		{
			m_sequenceItems[i] = m_sequenceItems[i + 1];
		}
		m_numOfItems--;
		return true;

	}
	return false;

}

int Sequence::remove(const ItemType& value)
{
	int itemsRemoved = 0;
	for (int i = size() - 1; i >= 0; i--)
	{
		if (m_sequenceItems[i] == value)
		{
			for (int j = i; j < size(); j++) {
				m_sequenceItems[j] = m_sequenceItems[j + 1];
			}
			m_numOfItems--;
			itemsRemoved++;
		}
	}
	return itemsRemoved;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (pos >= 0 && pos < size()) {
		value = m_sequenceItems[pos];
		return true;
	}
	return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (pos >= 0 && pos < size())
	{
		m_sequenceItems[pos] = value;
		return true;

	}
	return false;
}
int Sequence::find(const ItemType& value) const
{
	int s = size();
	for (int p = 0; p < s; p++)
	{
		if (value == m_sequenceItems[p])
		{
			return p;
		}
	}
	return -1;
}
void Sequence::swap(Sequence& other)
{
	ItemType* temp;
	temp = other.m_sequenceItems;
	other.m_sequenceItems = m_sequenceItems;
	m_sequenceItems = temp;

	int tempSize;
	tempSize = other.size();
	other.m_numOfItems = m_numOfItems;
	m_numOfItems = tempSize;

	int tempMax;
	tempMax = other.m_maxNum;
	other.m_maxNum = m_maxNum;
	m_maxNum = tempMax;
}
void Sequence::dump() const
{
	for (int i = 0; i < size(); i++)
	{
		std::cerr << m_sequenceItems[i] << ", ";
	}
	std::cerr << std::endl;
}