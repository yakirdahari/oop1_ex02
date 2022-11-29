#include "Ghost.h"
//#include "Board.h"

Ghost::Ghost() : m_location(0, 0), alive(true)
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

bool Ghost::isAlive()
{
	return alive ? true : false;
}
