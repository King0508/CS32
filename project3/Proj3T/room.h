#ifndef ROOM_H
#define ROOM_H
class Temple; 
class Room
{
public:
	Room(Temple* temple, int ux, int uy, int lx, int ly);
	bool isInRoom(int ux, int uy, int lx, int ly) const;
	int getUX() const; 
	int getUY() const; 
	int getLX() const;
	int getLY() const; 
private:
	Temple* m_temple; 
	int m_ux;
	int m_uy;
	int m_lx;
	int m_ly;
};
#endif // !ROOM_H



