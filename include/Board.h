#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Location.h"
#include "Ghost.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Player;
class Board
{
public:
	Board();
	bool isValid(vector<string> map, Player& player);
	void Build(Player& player);
	void updateMap(Player& player);
	bool PlayerCanMove(Player& player, const Location loc);
	bool movePlayer(Player& player, int key);
	void moveGhosts(const Player& player);
	void loadLevel(Player& player);
	void openRandomDoor(const int level);
	int getCookieCount(Player& player);
	int getGhostCount(int level);
	string findWay(Location playerLoc, Location ghostLoc);
	int countSpaces(int level, Location ghostLoc, string way);
	bool GhostCanMove(int level, Location loc);
	~Board();

private:
	vector<int> m_cookieCount;  // amount of cookies per map
	vector<string> m_map;  // current map
	vector<vector<string>> m_maps;  // map list
	vector<vector<Location>> m_doors;  // stores all door locations
	vector<vector<Ghost>> m_ghosts;  // list of ghosts for each map
	std::ifstream m_file;
};

