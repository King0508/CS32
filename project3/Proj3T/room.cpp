#include "room.h"
#include "temple.h"
#include "globals.h"
Room::Room(Temple* temple, int ux, int uy, int lx, int ly) :m_temple(temple), m_ux(ux), m_uy(uy), m_lx(lx), m_ly(ly)
{}
bool Room::isInRoom(int ux, int uy, int lx, int ly) const //returns true if the new room coordinates overlaps with the this room 
{	
	for (int i = lx - 1; i <= ux + 1; i++) {
		for (int j = uy - 1; j <= ly + 1; j++) {
			if (i < 0 || i >= 70 || j < 0 || j >= 18) {
				continue; // Skip out-of-bounds
			}
			if (m_temple->currentChar(i, j) != '#') {
				return true;
			}
		}
	}
	return false;
	/*for (int i = lx-1; i <= ux+1; i++)
	{
		for (int j = uy-1; j <= ly+1; j++)
		{
			if (m_temple->currentChar(i, j) != '#')
				return true;
		}
	}
	return false;*/
}
int Room::getLX() const
{
	return m_lx;
}
int Room::getUX() const
{
	return m_ux;
}
int Room::getLY() const
{
	return m_ly;
}
int Room::getUY() const
{
	return m_uy;
}



