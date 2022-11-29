#include "Location.h"

class Ghost
{
public:
	Ghost();
	void setLocation(int col, int row);
	Location getLocation();
	bool isAlive();
	
private:
	Location m_location;
	bool alive;
};