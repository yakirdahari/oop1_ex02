#pragma once

#include "Location.h"

class Controller; // Forward declaration
class Board;

class Player
{
public:
	Player();
	bool move(Controller& c);
	void setLocation(int col, int row);
	void handleSpecialKey(Player pacman, Board& board);
	int getPoints()const;
	~Player();

private:
	Location m_location;
	Location m_spawn;
	int m_level;
	int m_lives;
	int m_points;
};
