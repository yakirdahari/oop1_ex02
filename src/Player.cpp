#include "Player.h"

class Controller;

Player::Player()
	:m_location(0, 0), m_spawn(0, 0),
	 m_level(1), m_lives(3), m_points(0),
	 m_movesLeft(0)
{
}

void Player::setLocation(Location loc)
{
	m_location.col = loc.col;
	m_location.row = loc.row;
}

void Player::addSpawn(int col, int row)
{
	m_spawn.col = col;
	m_spawn.row = row;
	m_spawnList.push_back(m_spawn);
}

void Player::setSpawn()
{
	Location spawn = m_spawnList[getLevel()];
	setLocation(spawn);
}

void Player::levelUp()
{
	m_level++;
}

int Player::getLevel() const
{
	return m_level -1;
}

int Player::getLives() const
{
	return m_lives;
}

int Player::getPoints() const
{
	return m_points;
}

void Player::givePoints(int x)
{
	m_points += x;
}

Location Player::getSpawn() const
{
	return m_spawnList[getLevel()];
}

Location Player::getLocation() const
{
	return m_location;
}

void Player::superPacman()
{
	m_movesLeft = 20;
}

bool Player::isSuperPacman()
{
	if (m_movesLeft == 0)
	{
		return false;
	}
	m_movesLeft--;
	return true;  // still super pacman
}

Player::~Player()
{
}