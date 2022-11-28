#include "Player.h"

Player::Player() :m_location(0, 0), m_spawn(0, 0)
{
}

bool Player::move(Controller& c)
{
	// Decide where to move
	// Check with Controller if it's legal
	// Change things (from the Controller) if there is a collision
	return true;
}

Player::~Player()
{
}