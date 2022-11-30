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
            // update map and move ghosts if moved or pressed space
            if (handleSpecialKey())
            {
                m_board.moveAllGhosts(m_player);
                m_board.updateMap(m_player);
            }
            break;
        default:
            if (handleRegularKey(c))
            {
                m_board.moveAllGhosts(m_player);
                m_board.updateMap(m_player);
            }
            break;
        }
        // checking if reached next map + load
        if (m_board.getCookieCount(m_player) == 0 &&
            m_player.getLevel() +1 != 3)
        {
            int level = m_player.getLevel();
            int ghostsLeft = m_board.getGhostCount(level);
            m_player.levelUp();
            m_player.givePoints( 50 + (ghostsLeft * 2) );
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
// key handler for player
bool Controller::handleSpecialKey()
{
    auto c = _getch();
    switch (c)
    {
    case KB_Up:
        if (m_board.movePlayer(m_player, KB_Up))
        {
            return true;
        }    
        break;
    case KB_Down:
        if (m_board.movePlayer(m_player, KB_Down))
        {
            return true;
        }
        break;
    case KB_Left:
        if (m_board.movePlayer(m_player, KB_Left))
        {
            return true;
        }
        break;
    case KB_Right:
        if (m_board.movePlayer(m_player, KB_Right))
        {
            return true;
        }
        break;
    }
    return false;  // no move was made
}
bool Controller::handleRegularKey(int c)
{
    switch (c)
    {
    case KB_Escape: exit(EXIT_SUCCESS);
        break;
    case KB_Space: return true;
        break;
    default:
        return false;
        break;
    }
}
Controller::~Controller()
{
}
