#include "Ghost.h"
//#include "Board.h"

Ghost::Ghost() : m_location(0, 0), alive(true), m_temp(' ')
{
}

void Ghost::setLocation(int col, int row)
{
	m_location.col = col;
	m_location.row = row;
}

Location Ghost::getLocation()
{
	return m_location;
}

// if ghost still alive
bool Ghost::isAlive()
{
	return alive ? true : false;
}

char Ghost::getTemp() const
{
	return m_temp;
}

// saves what ghost erases to bring it back later
void Ghost::setTemp(char c)
{
	// making sure ghost won't eat 'a'
	if (c == 'a')  
	{
		m_temp = 'a';
		return;
	}
	m_temp = c;
}
