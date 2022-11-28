#pragma once

#include <iostream>
#include "Player.h"
#include "Board.h"

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
	Player m_player;
	//Enemy* m_enemies;
};
