#include "Board.h"

// Opening file
Board::Board() :m_file("Board.txt"), m_mapCount (0)
{
	if (!m_file.is_open()) {
		cout << "Error in opening file" << endl;
		exit(EXIT_FAILURE);
	}
}

bool Board::isValid(vector<string> map)
{
	int pacmanCount = 0,
		doorCount = 0,
		keyCount = 0;
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
				break;
			case COOKIE: moreThanOneCookie = true;
				break;
			case DOOR: doorCount++;
				break;
			case KEY: keyCount++;
				break;
			}
		}
	}
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
		if (isValid(map))
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
void Board::Update(int lvl)
{
	system("cls");
	
	/*std::cout << "Level : " << m_player.getPoints() <<
		         " Lives : " << m_player.getLife() << 
		         " Points : " << m_player.getLevel() << endl;*/
	for (int i = 0 ; i < m_maps[lvl].size(); i++)
	{
		cout << m_maps[lvl][i] << endl;
	}
}

// Closing file
Board::~Board()
{
	
}