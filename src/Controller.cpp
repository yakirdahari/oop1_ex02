#include "Controller.h"

Controller::Controller()
{

}

void Controller::run()
{
	m_board.Build(m_player);
	m_board.loadLevel(m_player);
    m_board.updateMap(m_player);
    m_player.setSpawn();

    while (!GameOver())
    {
        auto c = _getch();
        switch (c)
        {
        case 0:
        case SpecialKey:
            handleSpecialKey();
            break;
        default:
            handleRegularKey(c);
            break;
        }
    }
}

bool Controller::GameOver()
{
    if (m_player.getLives() == 0)
    {
        return true; // RIP
    }
    return false;  // game not over
}

void Controller::handleSpecialKey()
{
    auto c = _getch();
    switch (c)
    {
    case KB_Up:
        m_board.move(m_player, KB_Up);
        break;
    case KB_Down:
        m_board.move(m_player, KB_Down);
        break;
    case KB_Left:
        m_board.move(m_player, KB_Left);
        break;
    case KB_Right:
        m_board.move(m_player, KB_Right);
        break;
    }
}
void Controller::handleRegularKey(int c)
{
    switch (c)
    {
    case KB_Escape:
        
        exit(EXIT_SUCCESS);
    default:
        break;
    }
}
Controller::~Controller()
{
}
