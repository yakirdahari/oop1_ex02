#include "Ghost.h"
//#include "Board.h"

Ghost::Ghost(int col, int row) : m_location(col, row), alive(true), m_temp(' ')
{
}

void Ghost::setLocation(int col, int row)
{
	this->m_location.col = col;
	this->m_location.row = row;
}

Location Ghost::getLocation()
{
	return this->m_location;
}

// if ghost still alive
bool Ghost::isAlive()
{
	return this->alive ? true : false;
}

char Ghost::getTemp() const
{
	return this->m_temp;
}

// saves what ghost erases to bring it back later
void Ghost::setTemp(char c)
{
	// making sure ghost won't eat 'a'
	if (c == 'a')  
	{
		this->m_temp = 'a';
		return;
	}
	this->m_temp = c;
}
