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
        if (m_board.getCookieCount(m_player) == 0 &&
            m_player.getLevel() +1 != 3)
        {
            m_player.levelUp();
            m_board.loadLevel(m_player);
            m_board.updateMap(m_player);
            m_player.setSpawn();
        }
    }
}

bool Controller::GameOver()
{
    int lives = m_player.getLives();
    int level = m_player.getLevel() +1;
    int cookieCount = m_board.getCookieCount(m_player);

    if (lives == 0 || level == 3 && cookieCount == 0)
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
