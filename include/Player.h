#pragma once

#include "Location.h"
#include <vector>
#include <Windows.h>

class Controller; // Forward declaration
class Board;

class Player
{
public:
	Player();
	void setLocation(Location loc);
	void addSpawn(int col, int row);
	void setSpawn();
	void levelUp();
	int getLevel()const;
	int getLives()const;
	int getPoints()const;
	void givePoints(int x);
	Location getSpawn()const;
	Location getLocation()const;
	~Player();

private:
	Location m_location;
	Location m_spawn;
	std::vector<Location> m_spawnList;
	int m_level;
	int m_lives;
	int m_points;
};
