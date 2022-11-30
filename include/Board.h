#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Location.h"
#include "Ghost.h"
#include <ctime>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::time;

class Player;
class Board
{
public:
	Board();
	bool isValid(const vector<string> &map, Player& player);
	void Build(Player& player);
	void rebuild(Player& player);
	void updateMap(Player& player);
	bool PlayerCanMove(Player& player, const Location loc);
	bool movePlayer(Player& player, int key);
	void moveAllGhosts(Player& player);
	void loadLevel(Player& player);
	void openRandomDoor(const int level);
	int getCookieCount(Player& player);
	int getGhostCount(int level);
	int findWay(Location playerLoc, Location ghostLoc);
	int countSpaces(Location ghostLoc, string way);
	bool GhostCanMove(int col, int row);
	void moveGhost(Ghost& ghost, string way);
	void playerDied(Player& player);
	~Board();

private:
	vector<int> m_cookieCount;  // amount of cookies per map
	vector<int> m_ghostCount;    // amount of ghosts per map
	vector<string> m_map;  // current map
	vector<vector<string>> m_maps;  // map list
	vector<vector<Location>> m_doors;  // stores all door locations
	vector<vector<Ghost>> m_ghosts;  // list of ghosts for each map
	std::ifstream m_file;
};

