#pragma once

#include <iostream>
#include <cstdlib> // for std::system()
#include "io.h"
#include <conio.h>
//#include "Player.h"
#include "Board.h"
#include <Windows.h>
//#include "Enemy.h"

class Controller
{
public:
	Controller();
	void run();
	bool GameOver();
	~Controller();

private:
	int m_lvl;  // current level
	Board m_board;
	//Player m_player;
	//Enemy* m_enemies;
};
