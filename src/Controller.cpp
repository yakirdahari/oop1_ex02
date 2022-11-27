#include "Controller.h"

Controller::Controller() : m_lvl(0)
{
	
}

void Controller::run()
{
	m_board.Build();
	m_board.Update(m_lvl);
	
}

Controller::~Controller()
{
}
