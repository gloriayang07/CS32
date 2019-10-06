#include "ScoreList.h"
ScoreList::ScoreList()
	:m_scoreList(), m_size(0)
{

}// Create an empty score list.

bool ScoreList::add(unsigned long score)

{
	if (score <= 100 && size() < DEFAULT_MAX_ITEMS)
	{
		m_scoreList.insert(score);
		return true;
	}
	return false;
	
}
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.

bool ScoreList::remove(unsigned long score)
{
	int p = m_scoreList.find(score);
	return m_scoreList.erase(p);
}
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.

int ScoreList::size() const
{
	return m_scoreList.size();
}
// Return the number of scores in the list.

unsigned long ScoreList::minimum() const
{
	if (m_scoreList.size() == 0)
		return NO_SCORE;
	ItemType min;
	m_scoreList.get(0, min);
	return min;
}
// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.

unsigned long ScoreList::maximum() const
{
	
	if (m_scoreList.size() == 0)
		return NO_SCORE;
	ItemType max;
	m_scoreList.get(m_scoreList.size() - 1, max);
	return max;
}
// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.