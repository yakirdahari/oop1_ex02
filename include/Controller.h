#pragma once

#include <iostream>
#include "Player.h"
#include "Board.h"
#include <conio.h>

enum Keys
{
	KB_Escape = 27,
	KB_Space = 32,
	SpecialKey = 224,
};

enum SpecialKeys
{
	KB_Up = 72,
	KB_Down = 80,
	KB_Left = 75,
	KB_Right = 77,
};

class Controller
{
public:
	Controller();
	void run();
	bool GameOver();
	bool handleSpecialKey();
	bool handleRegularKey(int c);
	~Controller();

private:
	Board m_board;
	Player m_player;
};
