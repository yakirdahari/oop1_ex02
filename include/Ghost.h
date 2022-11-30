#include "Location.h"

class Ghost
{
public:
	Ghost(int col, int row);
	void setLocation(int col, int row);
	Location getLocation();
	bool isAlive();
	char getTemp() const;
	Location getSpawn() const;
	void setTemp(char c);
	void died();
	
private:
	Location m_location;
	bool m_alive;
	Location m_spawn;  // remember where ghost was first spawned
	char m_temp; // saves what ghost erases to bring it back later
};