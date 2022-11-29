#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Location.h"
#include "Player.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Board
{
public:
	Board();
	bool isValid(vector<string> map, Player& player);
	void Build(Player& player);
	void updateMap(Player& player);
	bool canMove(Player& player, const Location loc);
	void move(Player& player, int key);
	void loadLevel(Player& player);
	void openRandomDoor(const int level);
	int getCookieCount(Player& player);
	~Board();

private:
	vector<int> m_cookieCount;  // amount of cookies per map
	vector<string> m_map;  // current map
	vector<vector<string>> m_maps;  // map list
	vector<vector<Location>> m_doors;  // stores all door locations
	// vector<enemy> enemies;
	std::ifstream m_file;
};

