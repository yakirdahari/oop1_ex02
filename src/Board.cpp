#include "Board.h"

using std::cout;
using std::endl;

// Opening file
Board::Board() :m_file("Board.txt"), m_mapCount (0)
{
	if (!m_file.is_open()) {
		cout << "Error in opening file" << endl;
		exit(EXIT_FAILURE);
	}
}

// Building board
void Board::Build()
{
	while (!m_file.eof())
	{
		auto row = 0;
		std::vector<std::string> col;
		std::string line;
		std::getline(m_file, line);
		auto iss = std::istringstream(line);
		iss >> row;
		line.clear();
		for (int i = 0; i < row; i++)
		{
			std::getline(m_file, line);
			col.push_back(line);
		}
		m_maps.push_back(col);

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