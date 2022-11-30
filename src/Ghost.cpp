#include "Ghost.h"

Ghost::Ghost(int col, int row)
	: m_location(col, row), m_alive(true), 
	  m_temp(' '), m_spawn(col, row)
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
	return m_alive ? true : false;
}

char Ghost::getTemp() const
{
	return m_temp;
}

Location Ghost::getSpawn() const
{
	return m_spawn;
}

// saves what ghost erases to bring it back later
void Ghost::setTemp(char c)
{
	// so we don't replicate 
	switch (c)
	{
	case 'a':
		m_temp = ' ';
		break;
	case '&':
		m_temp = ' ';
		break;
	case '@':
		m_temp = ' ';
		break;
	case '*':
		m_temp = '*';
		break;
	case '%':
		m_temp = '%';
		break;
	case '$':
		m_temp = '$';
		break;
	case ' ':
		m_temp = ' ';
	}
}

void Ghost::died()
{
	m_alive = false;
}

void Ghost::revive()
{
	m_alive = true;
}
