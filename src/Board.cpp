#include "Board.h"
#include "Controller.h"

// Opening file
Board::Board() :m_file("Board.txt"), m_cookieCount (0)
{
	if (!m_file.is_open()) {
		cout << "Error in opening file" << endl;
		exit(EXIT_FAILURE);
	}
}

// checking if given map is valid
// also sets spawn location of player and enemies
bool Board::isValid(const vector<string> &map, Player& player)
{
	int pacmanCount = 0,
		cookieCount = 0,
		ghostCount = 0,
		doorCount = 0,
		keyCount = 0;

	Location door(0, 0);
	vector<Location> doors;
	vector<Ghost> ghosts;
	
	bool moreThanOneCookie = false;
	char c;

	for (int i = 0; i < map.size(); i++)
	{
		for (int x = 0; x < map[i].size(); x++)
		{ 
			c = map[i][x];
			switch (c)
			{
			case PACMAN: pacmanCount++;
						 player.addSpawn(x, i);
				break;
			case GHOST: 
			{
				Ghost ghost(x, i);
				ghosts.push_back(ghost);
				ghostCount++;
			}
				break;
			case COOKIE: moreThanOneCookie = true;
				         cookieCount++;
				break;
			case DOOR: doorCount++;
				door.col = x;
				door.row = i;
				doors.push_back(door);
				break;
			case KEY: keyCount++;
				break;
			}
		}
	}
	// store vectors in 2d vectors
	// each map has its own vector
	m_cookieCount.push_back(cookieCount);
	m_doors.push_back(doors);
	m_ghosts.push_back(ghosts);
	m_ghostCount.push_back(ghostCount);

	return (doorCount == keyCount) && 
		   (pacmanCount == 1)      && 
		    moreThanOneCookie ? true : false;
}

// Building board
void Board::Build(Player& player)
{
	while (!m_file.eof())
	{
		vector<string> map;
		string line;
		std::getline(m_file, line);
		int row = stoi(line);
		for (int i = 0; i < row; i++)
		{
			std::getline(m_file, line);
			map.push_back(line);
		}
		if (isValid(map, player))
		{
			m_maps.push_back(map);
		}
		else
		{
			cout << "Wrong Board.txt format!\n";
			exit(EXIT_FAILURE);
		}
		std::getline(m_file, line);
	}
}

void Board::rebuild(Player& player)
{
	int level = player.getLevel();
	Location playerSpawn = player.getSpawn();
	Location playerLoc = player.getLocation();
	
	m_map[playerLoc.row][playerLoc.col] = ' ';
	player.setLocation(playerSpawn);
	playerLoc = player.getLocation(); // update location
	m_map[playerLoc.row][playerLoc.col] = 'a';

	for (int i = 0; i < m_ghosts[level].size(); i++)
	{
		Ghost& ghost = m_ghosts[level][i];
		Location ghostSpawn = ghost.getSpawn();
		Location ghostLoc = ghost.getLocation();
		m_map[ghostLoc.row][ghostLoc.col] = ' ';
		ghost.setLocation(ghostSpawn.col, ghostSpawn.row);
		ghostLoc = ghost.getLocation();
		m_map[ghostLoc.row][ghostLoc.col] = '&';
	}

	
}

// Updating board
void Board::updateMap(Player& player)
{
	system("cls");

	for (int i = 0 ; i < m_map.size(); i++)
	{
		cout << m_map[i] << endl;
	}
	std::cout << "Level: " << player.getLevel() + 1 <<
		" Lives: " << player.getLives() <<
		" Points: " << player.getPoints() << endl;
}

bool Board::PlayerCanMove(Player& player, const Location new_loc)
{
	Location loc = player.getLocation();
	int level = player.getLevel();
	char c = m_map[new_loc.row][new_loc.col];
	
	switch (c)
	{
	case WALL: return false;
		break;
	case COOKIE:
		player.givePoints(2);
		m_cookieCount[level]--;
		break;
	case DOOR:
		if (!player.isSuperPacman())
		{
			return false;  // not super pacman
		}
	case KEY:
		player.givePoints(7);
		openRandomDoor(level);
		break;
	case GIFT:
		player.givePoints(5);
		player.superPacman();
		break;
	}
	// player movement
	if (player.isSuperPacman())
	{
		m_map[loc.row][loc.col] = ' ';
		m_map[new_loc.row][new_loc.col] = SUPERPACMAN;
		player.setLocation(new_loc);
	}
	else
	{
		m_map[loc.row][loc.col] = ' ';
		m_map[new_loc.row][new_loc.col] = PACMAN;
		player.setLocation(new_loc);
	}
	return true;
}

bool Board::movePlayer(Player& player, int key)
{
	Location new_loc = player.getLocation();

	switch (key)
	{
	case KB_Up:
		new_loc.row--;
		if (PlayerCanMove(player, new_loc))
		{
			return true;
		}
		break;
	case KB_Down:
		new_loc.row++;
		if (PlayerCanMove(player, new_loc))
		{
			return true;
		}
		break;
	case KB_Left:
		new_loc.col--;
		new_loc.col--;
		if (PlayerCanMove(player, new_loc))
		{
			return true;
		}
		break;
	case KB_Right:
		new_loc.col++;
		new_loc.col++;
		if (PlayerCanMove(player, new_loc))
		{
			return true;
		}
		break;
	}
	return false;  // no move made
}

void Board::moveAllGhosts(Player& player)
{
	int level = player.getLevel();
	Location playerLoc = player.getLocation();
	int whichWay,
		top, right, bottom, left;

	// go through each ghost in the map that is alive
	for (int i = 0; i < getGhostCount(level) ; i++)
	{
		if (m_ghosts[level][i].isAlive())
		{
			Ghost& ghost = m_ghosts[level][i];
			Location ghostLoc = m_ghosts[level][i].getLocation();

			whichWay = findWay(playerLoc, ghostLoc);  // finds which side to go

			// check if was eaten before moving
			if (playerLoc == ghostLoc)
			{
				if (player.isSuperPacman())
				{
					// delete ghost
					m_map[ghostLoc.row][ghostLoc.col] = '@';
					m_ghostCount[level]--;
					ghost.died();
					continue;
				}
				playerDied(player);  // not super pacman
			}

			switch (whichWay)
			{
			case TOP_LEFT:
				top = countSpaces(ghostLoc, "top");
				left = countSpaces(ghostLoc, "left");
				if (top < left && top == 0) { moveGhost(ghost, "left"); continue; }
				if (top > left && left == 0) { moveGhost(ghost, "top"); continue; }
				break; // top == left
			case TOP_RIGHT:
				top = countSpaces(ghostLoc, "top");
				right = countSpaces(ghostLoc, "right");
				if (top < right && top == 0) { moveGhost(ghost, "right"); continue; }
				if (top > right && right == 0) { moveGhost(ghost, "top"); continue; }
				break; // top == right
			case BOTTOM_RIGHT:
				bottom = countSpaces(ghostLoc, "bottom");
				right = countSpaces(ghostLoc, "right");
				if (bottom < right && bottom == 0) { moveGhost(ghost, "right"); continue; }
				if (bottom > right && right == 0) { moveGhost(ghost, "bottom"); continue; }
				break; // bottom == right
			case BOTTOM_LEFT:
				bottom = countSpaces(ghostLoc, "bottom");
				left = countSpaces(ghostLoc, "left");
				if (bottom < left && bottom == 0) { moveGhost(ghost, "left"); continue; }
				if (bottom > left && left == 0) { moveGhost(ghost, "bottom"); continue; }
				break; // bottom == left
			}
			// go towards player if none above applies
			if (playerLoc.col > ghostLoc.col &&
				playerLoc.row == ghostLoc.row)
			{ 
				moveGhost(ghost, "right");
			}
			else if (playerLoc.col < ghostLoc.col &&
				     playerLoc.row == ghostLoc.row)
			{ 
				moveGhost(ghost, "left");
			}
			else if (playerLoc.row < ghostLoc.row &&
				     playerLoc.col == ghostLoc.col)
			{ 
				moveGhost(ghost, "top");
			}
			else if (playerLoc.row > ghostLoc.row &&
			         playerLoc.col == ghostLoc.col)
			{ 
				moveGhost(ghost, "bottom");
			}

			// if none above applies, ghost picks the longest path available
			else
			{
				top = countSpaces(ghostLoc, "top");
				right = countSpaces(ghostLoc, "right");
				bottom = countSpaces(ghostLoc, "bottom");
				left = countSpaces(ghostLoc, "left");
				if (top > right && top > bottom && top > left) { moveGhost(ghost, "top"); }
				if (right > top && right > bottom && right > left) { moveGhost(ghost, "right"); }
				if (bottom > top && bottom > right && bottom > left) { moveGhost(ghost, "bottom"); }
				if (left > top && left > right && left > bottom) { moveGhost(ghost, "left"); }
				continue;
			}
			// update ghost location and check if player died
			ghostLoc = m_ghosts[level][i].getLocation();  
			
			if (playerLoc == ghostLoc && !player.isSuperPacman())
			{
				playerDied(player);
			}
		}
	}
}

void Board::loadLevel(Player& player)
{
	int level = player.getLevel();
	m_map.clear();
	
	for (int i = 0 ; i < m_maps[level].size() ; i++)
	{
		string line = m_maps[level][i];
		m_map.push_back(line);
	}
}

void Board::openRandomDoor(const int level)
{
	srand(time(NULL));
	int x = rand() % m_doors.size();
	Location door = m_doors[level][x];
	vector<Location> temp1;
	vector<vector<Location>> temp2;

	m_map[door.row][door.col] = ' ';  // poof random door is gone!

	// my algorithm to remove random door x from the 2d vector of doors
	// (1) we copy all doors of current level except x to temp1
	// (2) we copy all door vectors of all levels except current level
	// (3) for current level we copy temp1 which doesn't have x in it
	// (4) temp2 is now m_doors without x in it so we copy temp2 to m_doors
	for (int i = 0; i < m_doors[level].size(); i++)
	{
		if (i == x)
		{
			continue;
		}
		temp1.push_back(m_doors[level][i]);
	}
	for (int i = 0; i < m_doors.size(); i++)
	{
		if (i == level)
		{
			temp2.push_back(temp1);
			continue;
		}
		temp2.push_back(m_doors[i]);
	}
	m_doors[level].clear();
	m_doors = temp2;
}

int Board::getCookieCount(Player& player)
{
	return m_cookieCount[player.getLevel()];
}

int Board::getGhostCount(int level)
{
	return m_ghostCount[level];
}

int Board::findWay(Location playerLoc, Location ghostLoc)
{
	if (ghostLoc.col > playerLoc.col &&
		ghostLoc.row > playerLoc.row)
	{
		return TOP_LEFT;
	}
	if (ghostLoc.col < playerLoc.col &&
		ghostLoc.row > playerLoc.row)
	{
		return TOP_RIGHT;
	}
	if (ghostLoc.col < playerLoc.col &&
		ghostLoc.row < playerLoc.row)
	{
		return BOTTOM_RIGHT;
	}
	if (ghostLoc.col > playerLoc.col &&
		ghostLoc.row < playerLoc.row)
	{
		return BOTTOM_LEFT;
	}
	return 0;  // none of the above = 0
}

int Board::countSpaces(Location ghostLoc, string way)
{
	int row = ghostLoc.row,
		col = ghostLoc.col,
		spaces = 0;  // how many spaces we counted

	if (way == "top")
	{
		for (int i = row -1 ; m_map[i][col] != WALL && 
			                  m_map[i][col] != DOOR ; i--)
		{
			spaces++;
		}
	}
	if (way == "right")
	{
		for (int i = col +2 ; m_map[row][i] != WALL &&
			                  m_map[row][i] != DOOR; i+=2)
		{
			spaces++;
		}
	}
	if (way == "bottom")
	{
		for (int i = row +1 ; m_map[i][col] != WALL &&
			                  m_map[i][col] != DOOR; i++)
		{
			spaces++;
		}
	}
	if (way == "left")
	{
		for (int i = col -2 ; m_map[row][i] != WALL &&
			                  m_map[row][i] != DOOR; i-=2)
		{
			spaces++;
		}
	}
	return spaces;
}

bool Board::GhostCanMove(int col, int row)
{
	if (m_map[row][col] == WALL ||
		m_map[row][col] == DOOR)
	{
		return false;
	}
	return true;
}

void Board::moveGhost(Ghost& ghost, string way)
{
	Location ghostLoc = ghost.getLocation();
	char m_temp = ghost.getTemp();
	int col = ghostLoc.col;
	int row = ghostLoc.row;

	if (way == "top")
	{
		
		if (GhostCanMove(col, row -1))
		{
			m_map[row][col] = ghost.getTemp();
			row--;
			ghost.setTemp(m_map[row][col]);  // store what ghost erased
			m_map[row][col] = '&';
			ghost.setLocation(col, row);
		}
	}
	if (way == "right")
	{
		if (GhostCanMove(col +2, row))
		{
			m_map[row][col] = ghost.getTemp();
			col++;
			col++;
			ghost.setTemp(m_map[row][col]);  // store what ghost erased
			m_map[row][col] = '&';
			ghost.setLocation(col, row);
		}
	}
	if (way == "bottom")
	{
		if (GhostCanMove(col, row +1))
		{
			m_map[row][col] = ghost.getTemp();
			row++;
			ghost.setTemp(m_map[row][col]);  // store what ghost erased
			m_map[row][col] = '&';
			ghost.setLocation(col, row);
		}
		
	}
	if (way == "left")
	{
		if (GhostCanMove(col -2, row))
		{
			m_map[row][col] = ghost.getTemp();
			col--;
			col--;
			ghost.setTemp(m_map[row][col]);  // store what ghost erased
			m_map[row][col] = '&';
			ghost.setLocation(col, row);
		}
	}
}

// checks if player died
void Board::playerDied(Player& player)
{
	Location loc = player.getLocation();
	int row = loc.row;
	int col = loc.col;

	if (player.isSuperPacman())
	{
		m_map[row][col] = SUPERPACMAN;
		return; // didn't die
	}
	player.died();
	rebuild(player);
}

Board::~Board()
{
	
}