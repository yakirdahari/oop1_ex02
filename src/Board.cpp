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
	if (!m_file.eof())
	{
		int height, width;
		std::vector<std::string> col;
		std::string line;

		m_file >> height;
		m_file >> width;

		std::getline(m_file, line);

		for (int i = 0; i < height; i++)
		{
			std::getline(m_file, line);
			col.push_back(line);
		}
		m_maps.push_back(col);
	}
}

// Updating board
void Board::Update(int lvl)
{
	system("cls");
	/*std::cout << "Level : " << m_player.getPoints() <<
		         " Lives : " << m_player.getLife() << 
		         " Points : " << m_player.getLevel() << endl;*/
	for (int i = 0 ; i < m_maps[lvl].size() ; i++)
	{
		cout << m_maps[lvl][i] << endl;
	}
}

// Closing file
Board::~Board()
{
	
}