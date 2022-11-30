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
	size_t getPoints()const;
	void givePoints(size_t x);
	Location getSpawn()const;
	Location getLocation()const;
	void superPacman();
	bool isSuperPacman();
	void died();
	void clear();
	~Player();

private:
	Location m_location;
	Location m_spawn;
	std::vector<Location> m_spawnList;
	int m_level;
	int m_lives;
	size_t m_points;
	int m_movesLeft;  // how many moves left till super pacman is over
};
