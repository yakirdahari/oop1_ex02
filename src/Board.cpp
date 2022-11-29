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
bool Board::isValid(vector<string> map, Player& player)
{
	int pacmanCount = 0,
		cookieCount = 0,
		doorCount = 0,
		keyCount = 0;

	Location door(0, 0);
	vector<Location> doors;
	vector<Ghost> ghosts;
	Ghost ghost;

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
				        ghost.setLocation(x, i);
				        ghosts.push_back(ghost);
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

// Updating board
void Board::updateMap(Player& player)
{
	system("cls");
	
	//int level = player.getLevel() + 1;

	for (int i = 0 ; i < m_map.size(); i++)
	{
		cout << m_map[i] << endl;
	}
	std::cout << "Level: " << player.getLevel() +1 <<
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

void Board::moveGhosts(const Player& player)
{
	int level = player.getLevel(),
		whichWay;

	Location playerLoc = player.getLocation();

	for (int i = 0; i < m_ghosts[level].size() ; i++)
	{
		if (m_ghosts[level][i].isAlive())
		{
			Location ghostLoc = m_ghosts[level][i].getLocation();
			whichWay = findWay();  // finds which side to go

			switch (whichWay)
			{
			case TOP_LEFT:
				int top = countSpaces(level, ghostLoc, "top"),
					left = countSpaces(level, ghostLoc, "left");
				break;
			case TOP_RIGHT:
				break;
			case BOTTOM_RIGHT:
				break;
			case BOTTOM_LEFT:
				break;
			}

			//Location new_loc = find_way()
			//canGhostMove(player_loc, ghost_loc);
		}
	}
}

void Board::loadLevel(Player& player)
{
	m_map.clear();
	int level = player.getLevel();
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
	return m_ghosts[level].size();
}

string Board::findWay(Location playerLoc, Location ghostLoc)
{
	if (ghostLoc.col < playerLoc.col &&
		ghostLoc.col < playerLoc.col)
	{
		return "TOP_LEFT";
	}
}

bool Board::GhostCanMove(int level, Location loc)
{
	if (m_map[loc.row][loc.col] == WALL ||
		m_map[loc.row][loc.col] == DOOR)
	{
		return false;
	}
	return true;
}

// Closing file
Board::~Board()
{
	
}