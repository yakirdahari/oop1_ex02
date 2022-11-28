#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
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
	char getLocation(const int col, const int row) const;
	int getCookieCount();
	void resetLevel();
	char objectLocation();
	~Board();

private:
	int m_cookieCount;  // how many cookies in the map
	vector<string> m_map;  // current map
	vector<vector<string>> m_maps;  // map list
	// vector<enemy> enemies;
	std::ifstream m_file;
};

