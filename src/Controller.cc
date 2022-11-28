#include "Controller.h"

Controller::Controller() : m_lvl(0)
{

}

void Controller::run()
{
	Player p;
	m_board.Update(m_lvl);
	m_board.Build(p);
}

Controller::~Controller()
{
}
