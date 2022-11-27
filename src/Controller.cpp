#include "Controller.h"

Controller::Controller() : m_lvl(0)
{
	
}

void Controller::run()
{
	m_board.Build();
	m_board.Update(1);
	
}

Controller::~Controller()
{
}
