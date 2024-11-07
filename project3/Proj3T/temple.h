#ifndef TEMPLE_INCLUDED
#define TEMPLE_INCLUDED
#include <string>
#include <queue> 
#include <vector>
#include "globals.h"
class Monster;
class Room;
class Player;
class Game; 
class Objects; 
class Temple
{
public:
	Temple(Game* game);
	~Temple();
	void display();
	void generate();
	char currentChar(int r, int c) const;
	Monster* MonsterAtLocation(int r, int c) const;
	Objects* ObjectAtLocation(int r, int c) const;
	void attack(int ar, int ac, int dr, int dc); 
	Player* getPlayer() const; 
	void emptyCoord(int &r, int &c) const; 
	bool createRoom(Room* x);
	bool reachStair() const; 
	bool reachIdol() const; 
	bool canWalk(int c, int r) const;
	bool isMonsterHere(int c, int r) const;
	bool isActorHere(int c, int r) const; 
	bool isObjectHere(int c, int r) const; 
	bool playerSleep() const; 
	void cheat(); 
	void newTemple(); 
	void displayObjects(); 
	void setCurrentChar(int r, int c, char d); 
	void createCooridor();
	void drawCooridor(int x1, int y1, int x2, int y2);
	void actorsAndObjects(); 
	void monstersMove(); 
	void playerMove(char d); 
	void pickUp(); 
	void displayInventory() const; 
	void insertObject(Objects* obj); 
	void displayActionString();
	void playerRegen();  
	void read(char c); 
	void wield(char c); 
	std::string actionString(std::string attacker, std::string defender, std::string, bool hit, bool sleep, int hp);
private:
	Game* m_game; 
	char temple[MAXCOLS][MAXROWS];
	Objects* m_objects[MAXOBJECTS];
	int n_objects; 
	Monster* m_monster[MAXMONSTERS];
	int n_monsters;
	std::vector<Room*> m_rooms; 
	Player* m_player;
	int m_levels; 
	std::queue<std::string> action; 

};
#endif // !TEMPLE_INCLUDED



