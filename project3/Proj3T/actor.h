#ifndef ACTOR_H
#define ACTOR_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "utilities.h"
#include "temple.h"
#include "objects.h"
class Actor
{
public:
	Actor(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp);
	virtual std::string description() const = 0;
	int strength() const;
	int armor() const;
	int dexterity() const;
	void setDexterity(int d); 
	int hp() const;
	int rows() const;
	virtual void setRows(int r); 
	int cols() const;
	virtual void setCols(int c); 
	virtual void setHp(int hp);
	int getHp() const;
	int getStrenth() const;
	void setStrength(int s);
	int getSleep() const;
	void setSleep(int t);
	int getArmor() const; 
	void setArmor(int a); 
	virtual int distance(int pr, int pc, int mr, int mc) const;
	Weapon* getWeapon() const; 
	Temple* getTemple() const;
	void deleteWeapon();
	void setWeapon(Weapon* weapon); 
	virtual ~Actor(); 
private:
	Temple* m_temple;
	Weapon* m_weapon;
	int m_rows;
	int m_cols;
	int m_hp;
	int m_armor;
	int m_strength;
	int m_dexterity;
	int m_sleep;
}; 
Actor::Actor(Temple* temple, Weapon* weapon,int r, int c, int hp, int ap, int sp, int dp): m_temple(temple),m_weapon(weapon), m_rows(r), m_cols(c), m_hp(hp), m_armor(ap), m_strength(sp), m_dexterity(dp), m_sleep(0)
{	 
}
Actor::~Actor()
{
	delete m_weapon; 
}
void Actor::setDexterity(int d)
{	
	if (d <= 99)
		m_dexterity = d;
}
void Actor::setWeapon(Weapon* weapon)
{
	m_weapon = weapon; 
}
void Actor::deleteWeapon()
{
	delete m_weapon; 
}
int Actor::distance(int pr, int pc, int mr, int mc) const
{
	int x = abs(pr - mr);
	int y = abs(pc - mc);
	return(x + y);
}
Temple* Actor::getTemple() const
{
	return(m_temple);
}
int Actor::getStrenth() const
{
	return m_strength; 
}
int Actor::getArmor() const
{
	return m_armor; 
}
void Actor::setArmor(int a)
{	
	if (a <= 99)
		m_armor = a;
}
void Actor::setStrength(int s)
{	
	if (s <= 99)
		m_strength = s;
}
int Actor::getSleep() const
{
	return m_sleep; 
}
void Actor::setSleep(int t)
{	
	if (t <= 9)
		m_sleep = t;
}
Weapon* Actor:: getWeapon() const
{
	return(m_weapon); 
}
void Actor::setCols(int c)
{	
	m_cols = c; 
}
void Actor::setRows(int r)
{
	m_rows = r;
}
int Actor::hp() const
{
	return(m_hp);
}
void Actor::setHp(int hp)
{	
	if (hp <= 99)
		m_hp = hp;
}
int Actor::getHp() const
{
	return m_hp;
}
int Actor::strength() const
{
	return m_strength;
}
int Actor::armor() const
{
	return m_armor;
}
int Actor::rows() const
{
	return m_rows;
}
int Actor::cols() const
{
	return m_cols;
}
int Actor::dexterity() const
{
	return m_dexterity;
}
class Player :public Actor
{
public:
	Player(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp);
	std::string description() const;
	void setInventory(Objects* x);
	Objects* getInventory(int i) const; 
	int getItems() const; 
	bool isInInventory(int r, int c) const;
	void setHp(int hp); 
	int getMaxHp() const;
	void setMaxHp(int m); 
	void deleteInventory(int index); 
	virtual ~Player(); 
private:
	Objects* inventory[MAXITEMS];
	int usedScrolls[MAXOBJECTS];
	int m_usedSrolls; 
	int m_items; 
	int m_maxhp; 
};
void Player::setInventory(Objects* x)
{
	if (m_items < MAXITEMS)
	{
		inventory[m_items] = x;
		m_items++;
	}
}
Player::~Player()
{
	for (int i = 0; i < m_items; i++)
		delete inventory[i]; 
}
Player::Player(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp) : Actor(temple, weapon, r, c, hp, ap, sp, dp), m_usedSrolls(0), m_items(0), m_maxhp(hp)
{	
	Weapon* ss = new Weapon(rows(), cols(), "short sword", 0, 2); //a new short sword is created to put into the player's inventory
	setInventory(ss); 
}
void Player::deleteInventory(int index) { //this function deletes the object in inventory at some index, and swaps the pointers to ensure no memory leak 
	delete inventory[index]; 
	for (int i = index; i < m_items; i++) {
		if (i == m_items - 1) //do not go through last iteration to avoid out of bounds access 
			break; 
		inventory[i] = inventory[i + 1]; 
	}
	m_items--; 
}
int Player::getMaxHp() const
{
	return m_maxhp; 
}
void Player::setHp(int hp)
{
	if (hp <= m_maxhp)
		Actor::setHp(hp); 
}
Objects* Player::getInventory(int i) const
{
	if (i + 1 <= m_items)
		return inventory[i]; 
	return nullptr; 
}
void Player::setMaxHp(int m)
{	
	if (m <= 99)
		m_maxhp = m;
}
bool Player::isInInventory(int r, int c) const
{
	for (int i = 0; i < m_items; i++)
	{
		if (inventory[i]->rows() == r && inventory[i]->cols() == c)
			return true;
	}	
	return false; 	
}
int Player::getItems() const
{
	return(m_items); 
}
std::string Player::description() const
{
	return "Player";
}
class Monster : public Actor
{
public:
	Monster(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp);
	virtual void walk(int pr, int pc, int mr, int mc); 
	virtual void move() = 0;
	virtual void drop() = 0;
	void setRows(int r); 
	void setCols(int c); 
	bool isMonsterAlive() const; 
	void setAlive(bool a); 
	virtual ~Monster(); 
private:
	bool m_alive; 
};
Monster::Monster(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp) : Actor(temple, weapon, r, c, hp, ap, sp, dp), m_alive(true) 
{

}
Monster::~Monster()
{
	
}
void Monster::setAlive(bool a)
{
	m_alive = a; 
}
bool Monster::isMonsterAlive() const
{
	return m_alive; 
}
void Monster::setRows(int r)
{
	Actor::setRows(r);
	getWeapon()->setRows(r); 	
}
void Monster::setCols(int c)
{
	Actor::setCols(c); 
	getWeapon()->setCols(c); 
}
void Monster::walk(int pr, int pc, int mr, int mc) //function that has the Bogeymen and the snakewomen move closer to the player given they are in range 
{	
	int d = distance(pr, pc, mr, mc);//distance calculates the raw distance from from the player to the monster 
	int e = distance(pr, pc, mr, mc+1);//distance if the monster moves east, south , west, north, those distance must be smaller than d for the monster to move in that direction 
	int s = distance(pr, pc, mr+1, mc); 
	int w = distance(pr, pc, mr, mc-1); 
	int n = distance(pr, pc, mr-1, mc); 
	if (getTemple()->canWalk(mc + 1, mr) && e < d)//the monster will only go east if its new distance from the player will be less than the orignial distance 
	{
		char m = getTemple()->currentChar(mc, mr);
		getTemple()->setCurrentChar(mc, mr, ' ');
		getTemple()->setCurrentChar(mc + 1, mr, m);
		setCols(mc + 1);
	}
	else if (getTemple()->canWalk(mc, mr + 1) && s < d)//moves down 
	{
		char m = getTemple()->currentChar(mc, mr);
		getTemple()->setCurrentChar(mc, mr, ' ');
		getTemple()->setCurrentChar(mc, mr + 1, m);
		setRows(mr + 1);
	}
	else if (getTemple()->canWalk(mc - 1, mr) && w < d)//moves left 
	{
		char m = getTemple()->currentChar(mc, mr);
		getTemple()->setCurrentChar(mc, mr, ' ');
		getTemple()->setCurrentChar(mc - 1, mr, m);
		setCols(mc - 1);
	}
	else if (getTemple()->canWalk(mc, mr - 1) && n < d)//moves up 
	{
		char m = getTemple()->currentChar(mc, mr);
		getTemple()->setCurrentChar(mc, mr, ' ');
		getTemple()->setCurrentChar(mc, mr - 1, m);
		setRows(mr - 1);
	}
}
class Bogeymen : public Monster
{
public:
	Bogeymen(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp);
	std::string description() const;
	void move();
	void drop(); 
};
Bogeymen::Bogeymen(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp) : Monster(temple, weapon, r, c, hp, ap, sp, dp)
{
}
void Bogeymen::drop()
{
	if (trueWithProbability(1.0/10)) //10 percent chance the bogeymen will drop a magic axe 
	{
		if (!getTemple()->isObjectHere(cols(), rows()))
		{
			Weapon* newWeapon = new Weapon(rows(), cols(), "magic axe", 5, 5); //a new weapon is created and is added to the temple class 
			getTemple()->insertObject(newWeapon);//insertObject inserts the pointer to the next available index of the objects array in the temple class 
			getTemple()->setCurrentChar(cols(), rows(), ')');
		}
	}
	setAlive(false);
}
void Bogeymen::move()
{	
	if (getHp() <= 0)//if monster is died, it cannot move
		return;
	else if (getSleep() > 0)
	{
		setSleep(getSleep() - 1);
		return; 
	}
	if (distance(getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols(), rows(), cols()) == 1)
		getTemple()->attack(rows(), cols(), getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols());
	else if (distance(getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols(), rows(), cols()) <= 5)
		walk(getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols(), rows(), cols());
}
std::string Bogeymen::description() const
{
	return "the Bogeymen";
}

class Snakewomen : public Monster
{
public:
	Snakewomen(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp);
	std::string description() const;
	void move();
	void drop(); 
};
Snakewomen::Snakewomen(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp) : Monster(temple, weapon, r, c, hp, ap, sp, dp)
{
}
void Snakewomen::drop()
{
	if (trueWithProbability(1.0/3))//1/3 chance drops magic fangs of sleep 
	{
		if (!getTemple()->isObjectHere(cols(), rows()))
		{
			Weapon* newWeapon = new Weapon(rows(), cols(), getWeapon()->getName(), getWeapon()->getDex(), getWeapon()->getDam());
			getTemple()->insertObject(newWeapon); 
			getTemple()->setCurrentChar(cols(), rows(), ')');
		}	
	}
	setAlive(false); 
}
void Snakewomen::move()
{
	if (getHp() <= 0)//if monster is died, it cannot move
		return;
	else if (getSleep() > 0)
	{
		setSleep(getSleep() - 1);
		return;
	}
	if (distance(getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols(), rows(), cols()) == 1)
		getTemple()->attack(rows(), cols(), getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols());	
	else if (distance(getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols(), rows(), cols()) <= 3)//if distance between player and snakewomen is less than or equal to 3, the snakewomen moves closer to player if possible 
		walk(getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols(), rows(), cols());			
}
std::string Snakewomen::description() const
{
	return "the Snakewomen";
}

class Dragon : public Monster
{
public:
	Dragon(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp);
	std::string description() const;
	void move();
	void drop(); 
	void setHp(int hp); 
	int getMaxHp() const; 
private:
	int m_maxhp; 
};
Dragon::Dragon(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp) : Monster(temple, weapon, r, c, hp, ap, sp, dp), m_maxhp(hp) 
{
}
void Dragon::setHp(int hp)
{
	if (hp <= m_maxhp) //max hp is the intial hp when the dragon is contructed 
		Actor::setHp(hp); 
}
int Dragon::getMaxHp()const
{
	return m_maxhp; 
}
void Dragon::drop()
{
	if (!getTemple()->isObjectHere(cols(), rows()))//numItemAtLocation = 0 ensures that the monster can drop an item at the location  
	{
		std::string scrollName; 
		if (trueWithProbability(0.5))
			scrollName = "teleportation";
		else if (trueWithProbability(0.4))
			scrollName = "strength";
		else if (trueWithProbability(1.0 / 3))
			scrollName = "enhance armor";
		else if (trueWithProbability(0.5))
			scrollName = "enhance health";
		else
			scrollName = "enhance dexterity"; 
		Scroll* newScroll = new Scroll(rows(), cols(), scrollName);//name of scroll is determined through trueWithProbablity
		getTemple()->insertObject(newScroll);
		getTemple()->setCurrentChar(cols(), rows(), '?');
	}
	setAlive(false);//last thing before a monster dies, they drop, afterwards ,the boolean is set to false 
}
void Dragon::move()
{	
	if (getHp() <= 0)//if monster is died, it cannot move
		return;
	else if (getSleep() > 0)
	{
		setSleep(getSleep() - 1); 
		return;
	}
	if (trueWithProbability(0.1) && hp() < m_maxhp)//10 percent chance regens for dragons, before its attack move 
		setHp(hp() + 1);
	if (distance(getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols(), rows(), cols()) == 1)//if distance == 1, dragon attacks 
		getTemple()->attack(rows(), cols(), getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols());	 
}
std::string Dragon::description() const
{
	return "the Dragon";
}

class Goblins : public Monster
{
public:
	Goblins(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp, int distance);
	std::string description() const;
	void move();
	void drop(); 
	void findPath(int r, int c, int pr, int pc, std::vector<std::string>& ans, std::string& currentPath);
private:
	int m_distance; 
};

Goblins::Goblins(Temple* temple, Weapon* weapon, int r, int c, int hp, int ap, int sp, int dp, int distance) : Monster(temple, weapon, r, c, hp, ap, sp, dp), m_distance(distance) 
{	
}
void Goblins::findPath(int r, int c, int pr, int pc, std::vector<std::string>& ans, std::string& currentPath) //recursive function for goblin that guides its movement 
{	
	//this function takes in the coordinates of the goblin and the player. It also takes in a vector of strings and a string by reference. 
	//for each movement search in the recursive, a direction string D, L, R, or U are appended to the next of currentPath. When the 
	//goblins reaches the player, currentPath, the string that has saved the directions of movement is added to the vector. 
	//at the end, all possible path to the player is saved in the string vector and the shortest one can be obtained. 
	std::string direction = "DLRU";
	int dr[4] = { 1, 0, 0, -1 };
	int dc[4] = { 0, -1, 1, 0 };
	if (r == pr && c == pc)
		return; 
	if (currentPath.size() >= m_distance)
		return; 
	char a = getTemple()->currentChar(c, r);//marks visited spots for effciency 
	getTemple()->setCurrentChar(c, r, '#'); //saves the char at that location 
	for (int i = 0; i < 4; i++)
	{
		int nextrow = r + dr[i]; 
		int nextcol = c + dc[i];
		if (getTemple()->canWalk(nextcol,nextrow))
		{
			currentPath += direction[i]; 
			if (distance(nextrow, nextcol, pr, pc) == 1 && currentPath.size() < m_distance)	//appropriate condition for a valid path to the player 
				ans.push_back(currentPath); 
			else 
				findPath(nextrow, nextcol, pr, pc, ans, currentPath); //continue recursively 
			currentPath.pop_back(); //removes that most recent direction in currentPath 
		}
	}
	getTemple()->setCurrentChar(c, r, a); //replace the char
}
void Goblins::drop()
{	
	if (trueWithProbability(1.0 / 3))//one third chance the goblin drops either a magic fang or a magic axe 
	{
		if (!getTemple()->isObjectHere(cols(), rows()))//only drops if no other items 
		{	
			std::string name; 
			int dex, dam; 
			if (trueWithProbability(0.5)) //half of the time magic axe, the other half magic fangs of sleep 
			{
				name = "magic axe"; //name and attributes for magic axe 
				dex = 5; 
				dam = 5; 
			}
			else
			{
				name = "magic fangs"; //name and attributes for magic fangs 
				dex = 3;
				dam = 2; 
			}
			Weapon* newWeapon = new Weapon(rows(), cols(), name, dex, dam);
			getTemple()->insertObject(newWeapon);
			getTemple()->setCurrentChar(cols(), rows(), ')');
		}
	}
	setAlive(false);
}
void Goblins::move() 
{	
	if (getHp() <= 0)//if monster is died, it cannot move
		return;
	else if (getSleep() > 0) //decrement sleep time 
	{
		setSleep(getSleep() - 1);
		return;
	}
	else if (distance(getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols(), rows(), cols()) == 1) //if distance == 1, Goblin attack 
		getTemple()->attack(rows(), cols(), getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols()); //calls attack function 
	else if (distance(getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols(), rows(), cols()) <= m_distance) //the goblin has to be within 15 moves of the player 
	{
		std::vector<std::string> allPaths; 
		std::string path = "";
		findPath(rows(), cols(), getTemple()->getPlayer()->rows(), getTemple()->getPlayer()->cols(), allPaths, path); //allPaths saves all the possible path for the goblin to reach the player in less than 15 moves 
		if (!allPaths.empty())
		{
			std::string shortest = allPaths[0];
			for (int i = 1; i < allPaths.size(); i++)
			{
				if (allPaths[i].size() < shortest.size())
					shortest = allPaths[i];//the shortest string in the array is found 
			}
			switch (shortest.at(0))//the goblins moves the direction indicated by the zeroth index of the shortest string 
			{
			case 'D': //goblins moves down 
				getTemple()->setCurrentChar(cols(), rows(), ' ');
				getTemple()->setCurrentChar(cols(), rows() + 1, 'G');
				setRows(rows() + 1);
				break;
			case'L': //goblins move left 
				getTemple()->setCurrentChar(cols(), rows(), ' ');
				getTemple()->setCurrentChar(cols() - 1, rows(), 'G');
				setCols(cols() - 1); 
				break;
			case'R': //goblins move right 
				getTemple()->setCurrentChar(cols(), rows(), ' ');
				getTemple()->setCurrentChar(cols() + 1, rows(), 'G');
				setCols(cols() + 1); 
				break;
			case'U': //goblins move up 
				getTemple()->setCurrentChar(cols(), rows(), ' ');
				getTemple()->setCurrentChar(cols(), rows() - 1, 'G');
				setRows(rows() - 1); 
				break;
			}
		}	
	}
}
std::string Goblins::description() const
{
	return "the Goblin";
}
#endif  
