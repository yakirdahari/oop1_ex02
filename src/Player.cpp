#include "Player.h"

class Controller;

Player::Player() 
	:m_location(0, 0), m_spawn(0, 0), 
	 m_level(1), m_lives(3), m_points(0)
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
	int a = m_level - 1;
	Location spawn = m_spawnList[a];
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
	int a = m_level - 1;
	return m_spawnList[a];
}

Location Player::getLocation() const
{
	return m_location;
}

Player::~Player()
{
}