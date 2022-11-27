#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "Location.h"
//#include "Player.h"
//#include "Enemy.h"

class Controller;
//class Player;
//class Enemy;
class Board
{
public:
	Board();
	void readFile();
	void Build();
	void Update(int lvl);
	char getLocation(const int col, const int row) const;
	void resetLevel();
	char objectLocation();
	~Board();

private:
	int m_mapCount;  // how many maps
	std::vector<std::vector<std::string>> m_map;  // current map
	std::vector<std::vector<std::string>> m_maps;  // map list
	std::ifstream m_file;
};

