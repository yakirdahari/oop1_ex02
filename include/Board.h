#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "Location.h"
//#include "Enemy.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Controller;
class Player;
//class Enemy;
class Board
{
public:
	Board();
	void readFile();
	bool isValid(vector<string> map);
	void Build(Player& player);
	void Update(int lvl);
	char getLocation(const int col, const int row) const;
	void resetLevel();
	char objectLocation();
	~Board();

private:
	int m_mapCount;  // how many maps
	vector<vector<string>> m_map;  // current map
	vector<vector<string>> m_maps;  // map list
	std::ifstream m_file;
};

