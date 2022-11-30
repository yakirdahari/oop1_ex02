#include "Location.h"

class Ghost
{
public:
	Ghost(int col, int row);
	void setLocation(int col, int row);
	Location getLocation();
	bool isAlive();
	char getTemp() const;
	void setTemp(char c);
	
private:
	Location m_location;
	bool alive;
	char m_temp; // saves what ghost erases to bring it back later
};