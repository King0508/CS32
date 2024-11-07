#include "temple.h"
#include "utilities.h"
#include "room.h"
#include "actor.h"
#include "objects.h"
#include "Game.h"
#include <vector>
#include <iostream>
#include <algorithm>
Temple::Temple(Game* game) :m_game(game), n_objects(1), n_monsters(0), m_levels(-1) //level is intially -1 because when generated gets called, level becomes zero 
{
	for (int i = 0; i < 70; i++)//fills the grid with '#' 
	{
		for (int j = 0; j < 18; j++)
			temple[i][j] = '#';
	}
	Weapon* sw = new Weapon(0, 0, "short sword", 0, 2);//contruct new player with a short sword as weaon 
	m_player = new Player(this, sw, 0, 0, 20, 2, 2, 2);
}
Temple::~Temple() //free up the dynamically allocated memory for the next level to be generated 
{	
	for (int i = 0; i < n_monsters; i++)
		delete m_monster[i]; 
	for (int i = 0; i < n_objects; i++)
		delete m_objects[i]; 
	for (int i = 0; i < m_rooms.size(); i++)
		delete m_rooms[i]; 
	m_rooms.clear(); 
	delete m_player; 
}
void Temple::cheat() //sets max hp to 50, hp to 50, and strength to 9 
{
	m_player->setMaxHp(50); 
	m_player->setHp(50); 
	m_player->setStrength(9); 
}
void Temple::pickUp() //uses dynamic cast to determine weather a scroll or a weapon is picked up. 
{	
	for (int i = 0; i < n_objects; i++)
	{
		if (m_objects[i]->rows() == m_player->rows() && m_objects[i]->cols() == m_player->cols() && m_objects[i]->getName() != "stair" && m_objects[i]->getName() != "idol") {
			Scroll* scroll = dynamic_cast<Scroll*>(m_objects[i]); 
			if (scroll != nullptr) {
				if (m_player->getItems() == MAXITEMS) { //stops the player from picking up more items after the inventory is full 
					action.push("Your inventory is full. You cannot pick up a scroll called scroll of " + m_objects[i]->getName() + ".");
					break; 
				}
				Scroll* newScroll = new Scroll(m_player->rows(), m_player->cols(), m_objects[i]->getName());
				m_player->setInventory(newScroll);
				action.push("You pick up a scroll called scroll of " + m_objects[i]->getName());
				delete m_objects[i]; //after a scroll is picked up, it is deleted from the m_objects array, so it won't be displayed 
				for (int j = i; j < n_objects; j++) {
					if (j == n_objects - 1) 
						break; 
					m_objects[j] = m_objects[j + 1]; 
				}
				n_objects--; 
			}
			else {
				if (m_player->getItems() == MAXITEMS && m_objects[i]->getName() == "magic fangs") {
					action.push("Your inventory is full. You cannot pick up magic fangs of sleep.");
					break;
				}
				else if (m_player->getItems() == MAXITEMS) {
					action.push("Your inventory is full. You cannot pick up " + m_objects[i]->getName() + ".");
					break; 
				}
				int dex, dam;
				if (m_objects[i]->getName() == "mace" || m_objects[i]->getName() == "short sword"){
					dex = 0;
					dam = 2;
				}
				else if (m_objects[i]->getName() == "long sword"){
					dex = 2;
					dam = 4;
				}
				else if (m_objects[i]->getName() == "magic axe"){
					dex = 5;
					dam = 5;
				}
				else{
					dex = 3;
					dam = 2;
				}
				Weapon* newWeapon = new Weapon(m_player->rows(), m_player->cols(), m_objects[i]->getName(), dex, dam);
				m_player->setInventory(newWeapon);
				if (m_objects[i]->getName() == "magic fangs")
					action.push("You pick up magic fangs of sleep");
				else
					action.push("You pick up " + m_objects[i]->getName());
				delete m_objects[i]; //deleted the weapon so its no longer displayed on the map 
				for (int j = i; j < n_objects; j++) {
					if (j == n_objects - 1) 
						break;
					m_objects[j] = m_objects[j + 1];
				}
				n_objects--;	
			}
		}		
	}
}
void Temple::newTemple() //deletes the dynamically allocated memory when a brand new Temple is generated. 
{
	for (int i = 0; i < n_monsters; i++)
		delete m_monster[i]; //monsters deleted 
	n_monsters = 0; 
	for (int i = 0; i < n_objects; i++)
		delete m_objects[i]; //all game objects deleted 
	n_objects = 1; 
	m_rooms.clear(); //deletes the vector, set size = 0 
	//std::cout << m_rooms.size() << std::endl; 
}
void Temple::read(char c) //the user passes in a char that determines which scroll will be read
{
	int index = c - 97;  
	if (index + 1 <= m_player->getItems())
	{
		Objects* curItem = m_player->getInventory(index);
		Scroll* scroll = dynamic_cast<Scroll*>(curItem);//using dynamic cast to determine if a scroll was read 
		if (scroll != nullptr)
		{
			action.push("You read the scroll called scroll of " + curItem->getName());//messages are saved on to a queue and will be displayed later 
			if (curItem->getName() == "teleportation")
			{
				action.push("You feel your body wrenched in space and time.");
				temple[m_player->cols()][m_player->rows()] = ' ';
				int r, c;
				emptyCoord(r, c);
				m_player->setCols(c);//generates a new coord on the map for the player and completes the teleportation 
				m_player->setRows(r);
				temple[c][r] = '@';
			}
			else if (curItem->getName() == "enhance armor") //message and effeccts for enhance armor 
			{
				action.push("Your armor glows sliver");
				m_player->setArmor(m_player->getArmor() + randInt(1, 3));
			}
			else if (curItem->getName() == "enhance health") //message and effects for enhance health 
			{
				action.push("You feel your heart beating stronger.");
				m_player->setMaxHp(m_player->getMaxHp() + randInt(3, 8));
			}
			else if (curItem->getName() == "enhance dexterity") // message and effects for enhance dexterity 
			{
				action.push("You feel like less of a klutz.");
				m_player->setDexterity(m_player->dexterity() + 1);
			}
			else //message and effects for strength 
			{
				action.push("Your muscles bulge.");
				m_player->setStrength(m_player->getStrenth() + randInt(1, 3));
			}
			m_player->deleteInventory(index); 
			//m_player->useScroll(index); //saves the index of the scroll be read, useful later when displaying the inventory 
		}
		else //message for weapon that cannot be read 
		{
			if (curItem->getName() == "magic fangs")
				action.push("You can't read a magic fangs of sleep");
			else
				action.push("You can't read a " + curItem->getName());
		}
	}	
}
void Temple::wield(char c) //function that display the wielding strings and the effect of wielding different weapons 
{
	int index = c - 97; 
	if (index + 1 <= m_player->getItems())
	{
		Objects* curItem = m_player->getInventory(index);
		Weapon* weapon = dynamic_cast<Weapon*>(curItem);
		if (weapon != nullptr)
		{
			action.push("You are wielding " + curItem->getName());
			m_player->deleteWeapon(); //to adjust a player's weapon, the current weapon is deleted 
			int dex, dam;
			if (curItem->getName() == "mace" || curItem->getName() == "short sword")
			{
				dex = 0;
				dam = 2;
			}
			else if (curItem->getName() == "long sword")
			{
				dex = 2;
				dam = 4;
			}
			else if (curItem->getName() == "magic axe")
			{
				dex = 5;
				dam = 5;
			}
			else
			{
				dex = 3;
				dam = 2;
			}
			Weapon* newWeapon = new Weapon(curItem->rows(), curItem->cols(), curItem->getName(), dex, dam);
			m_player->setWeapon(newWeapon); //a new weapon is created and set to the player's weapon pointer, this object is not part of temple's objects array 
		}
		else
			action.push("You can't wield scroll of " + curItem->getName()); //message for wielding a scroll 
	}	
}
char Temple::currentChar(int r, int c) const // returns the char at some location in the temple, useful in the actor and objects.h class to access part of the temple grid 
{	
	if (r >= 0 && r < 70 && c >= 0 && c < 18) {
		return temple[r][c];
	}
	else {
		return '#';
	}
	/*if (c < 18 && r < 70)
		return(temple[r][c]);
	else
		return '#'; */
}
Player* Temple::getPlayer() const //returns the player pointer in the temple class, useful for actors and objects 
{
	return(m_player);
}
void Temple::playerRegen() //for a 10 percent chance, the player regains 1 hp before each user command. 
{
	if (trueWithProbability(0.1))
		m_player->setHp(m_player->getHp() + 1); 
}
bool Temple::playerSleep() const // a boolean that helps determine is a player is asleep, checks for the sleep time of the player, and decrement it if is above zero 
{
	if (m_player->getSleep() > 0)
	{
		m_player->setSleep(m_player->getSleep() - 1); 
		return true; 
	}
	return false; 
}
Monster* Temple::MonsterAtLocation(int r, int c) const //returns a pointer to the alive monster at some location on the grid, useful for the attack function of different actors 
{
	for (int i = 0; i < n_monsters; i++)
	{
		if (m_monster[i]->rows() == r && m_monster[i]->cols() == c && m_monster[i]->getHp() > 0)
			return m_monster[i];
	}
	return nullptr;
}
Objects* Temple::ObjectAtLocation(int r, int c) const //returns a pointer to the game object at some location on the grid, stairs and idols do not count, only weapons are scrolls 
{
	for (int i = 0; i < n_objects; i++)//useful in displaying the correct message when game objects are picked up 
	{
		if (m_objects[i]->rows() == r && m_objects[i]->cols() == c && m_objects[i]->getName() != "stair" && m_objects[i]->getName() != "idol")
			return m_objects[i]; 
	}
	return nullptr; 
}
bool Temple::isObjectHere(int c, int r) const {
	for (int i = 0; i < n_objects; i++) {
		if (m_objects[i]->cols() == c && m_objects[i]->rows() == r)
			return true; 
	}
	return false; 
}
void Temple::displayActionString() //displays the queue which has saved all the string which include wield, read, pick, and attack messages 
{
	while (!action.empty())
	{
		std::string s = action.front(); //saves the front of the queue, pop it, and display the string by cout 
		action.pop(); 
		std::cout << s << std::endl;
	}
}
void Temple::display()//function that displays the updated temple grid each cycle
{
	for (int i = 0; i < MAXROWS; i++) //prints out the grid 
	{
		for (int j = 0; j < MAXCOLS; j++)
			std::cout << temple[j][i];
		std::cout << std::endl;
	}
	std::cout << "Level: " << m_levels << ", Hit points: " << m_player->hp() << ", Armor: " << m_player->armor() << ", Strength: " << m_player->strength() << ", Dexterity: " << m_player->dexterity() << std::endl;
	std::cout << std::endl; //prints out the attributes of player 
	displayActionString(); //displays the strings 
	if (m_player->getHp() <= 0) //if the player has died, the game will be forced to end 
	{
		std::cout << "Press q to exit game." << std::endl;
		char q;
		while ((q = getCharacter()) != 'q')
		{}
		exit(0);
	}
}
bool Temple::reachIdol() const //used in the play function in the Game class to determine if the player is currently on top of the golden idol 
{
	int r, c; 
	for (int i = 0; i < n_objects; i++)
	{
		if (m_objects[i]->getName() == "idol")
		{
			r = m_objects[i]->rows(); 
			c = m_objects[i]->cols(); 
			if (m_player->rows() == r && m_player->cols() == c)
				return true; 
		}
	}
	return false; 
}
bool Temple::reachStair() const //used in the play function in the Game class to determine if the player is currently on top of the staircase leading to the next level  
{
	int r, c;
	for (int i = 0; i < n_objects; i++)
	{
		if (m_objects[i]->getName() == "stair")
		{
			r = m_objects[i]->rows();
			c = m_objects[i]->cols();
			if (m_player->rows() == r && m_player->cols() == c)
				return true;
		}
	}
	return false; 
}
void Temple::displayInventory() const //displays the player's inventory, if a scroll has been used, it will be skipped when displaying the inventory
{
	char a = 'a';
	std::cout << "Inventory:" << std::endl; 
	for (int i = 0; i < m_player->getItems(); i++,a++)
	{
		Objects* inv = m_player->getInventory(i); 
		Scroll* scroll = dynamic_cast<Scroll*>(inv);//dynamic cast to determine scroll or weapon 
		std::cout << " ";
		std::cout << a;
		if (scroll != nullptr)
			std::cout << ". A scroll called scroll of " + inv->getName() << std::endl;
		else
		{
			if (inv->getName() == "magic fangs")
				std::cout << ". " + inv->getName() + " of sleep" << std::endl;
			else
				std::cout << ". " + inv->getName() << std::endl;
		}
	}
}
void Temple::displayObjects() //function used to accurately display the gameObjects on the grid 
{
	for (int i = 0; i < n_objects; i++){ 
		if (!isActorHere(m_objects[i]->cols(), m_objects[i]->rows())) { //no actor should be on top of an object when it is displayed, this would erase the actor 
			if (m_objects[i]->getName() == "stair")
				temple[m_objects[i]->cols()][m_objects[i]->rows()] = '>';
			else if (m_objects[i]->getName() == "idol")
				temple[m_objects[i]->cols()][m_objects[i]->rows()] = '&';
			else if (m_objects[i]->getName() == "mace" || m_objects[i]->getName() == "short sword" || m_objects[i]->getName() == "long sword" || m_objects[i]->getName() == "magic axe" || m_objects[i]->getName() == "magic fangs")
				temple[m_objects[i]->cols()][m_objects[i]->rows()] = ')';
			else if (m_objects[i]->getName() == "teleportation" || m_objects[i]->getName() == "enhance armor" || m_objects[i]->getName() == "strength" || m_objects[i]->getName() == "enhance health" || m_objects[i]->getName() == "enhance dexterity")
				temple[m_objects[i]->cols()][m_objects[i]->rows()] = '?';
		}
	}
}
bool Temple::isActorHere(int c, int r) const //boolean function that returns true with an actor is at some location on the temple grid, useful for displaying gameObjects
{
	if (temple[c][r] == '@' || temple[c][r] == 'S' || temple[c][r] == 'B' || temple[c][r] == 'D' || temple[c][r] == 'G')
		return true; 
	return false; 
}
bool Temple::canWalk(int c, int r) const//boolean function that returns true if actors can walk over this location on the grid 
{
	if (temple[c][r] == ' ' || temple[c][r] == '>' || temple[c][r] == '&' || temple[c][r] == ')' || temple[c][r] == '?')
		return true; 
	return false; 
}
std::string Temple::actionString(std::string attacker, std::string defender, std::string weapon, bool hit, bool sleep, int hp)//function that determines actino string base on weapons and actors 
{	
	std::string as; 
	if (weapon == "short sword")
		as = " slashes ";
	else if (weapon == "mace" || weapon == "long sword")
		as = " swings ";
	else if (weapon == "magic fangs")
		as = " strikes ";
	else
		as = " chops "; 
	if (sleep)
		return(attacker + as + weapon + " at " + defender + " and hits, putting " + defender + " to sleep.");
	else if (hit && hp > 0)
		return(attacker + as + weapon + " at " + defender + " and hits.");
	else if (hit && hp <= 0)
		return(attacker + as + weapon + " at " + defender + " dealing a final blow.");
	else
		return(attacker + as + weapon + " at " + defender + " and misses.");
}
void Temple::attack(int ar, int ac, int dr, int dc)//attack function that determines if an attack was successful and how much damage is done 
{
	int ap, dp; 
	bool hit = false; 
	bool sleep = false; 
	if (MonsterAtLocation(ar, ac))//the case where the monster is the attack, and player is the defender 
	{
		Monster* attacker = MonsterAtLocation(ar, ac); 
		ap = attacker->dexterity() + attacker->getWeapon()->getDex(); 
		dp = m_player->dexterity() + m_player->armor(); 
		if (randInt(1, ap) >= randInt(1, dp))
			hit = true; 
		if (hit)
		{
			m_player->setHp(m_player->hp() - randInt(0, attacker->strength() + attacker->getWeapon()->getDam() - 1));
			if (attacker->getWeapon()->getName() == "magic fangs" && trueWithProbability(0.2) && m_player->getHp() > 0)//20percent chance magic fangs put enemies to sleep 
			{	
				sleep = true; 
				int s = randInt(2, 6);  
				if (s > m_player->getSleep()) //if the current sleep time is lower than the new one, the new sleep time because the current sleep time 
					m_player->setSleep(s); 
			}		 
		}	
		std::string actionS = actionString(attacker->description(), m_player->description(), attacker->getWeapon()->getName(), hit, sleep, m_player->getHp()); 
		action.push(actionS); 
	}
	else// the case when the player is the attacker and the monster is the defender 
	{
		Monster* defender = MonsterAtLocation(dr, dc); 
		ap = m_player->dexterity() + m_player->getWeapon()->getDex(); 
		dp = defender->dexterity() + defender->armor(); 
		if (randInt(1, ap) >= randInt(1, dp))
			hit = true;
		if (hit && defender->getHp() > 0)
		{
			defender->setHp(defender->hp() - randInt(0, m_player->strength() + m_player->getWeapon()->getDam() - 1));
			if (defender->getHp() <= 0)
				temple[dc][dr] = ' ';	//if the monster dies, it should be removed from the map 
			else if (m_player->getWeapon()->getName() == "magic fangs" && trueWithProbability(0.2))
			{
				sleep = true; 
				int s = randInt(2, 6);
				if (s > defender->getSleep())
					defender ->setSleep(s);
			}
		}
		std::string actionS = actionString(m_player->description(), defender->description(), m_player->getWeapon()->getName(), hit, sleep, defender->getHp());
		action.push(actionS); //action string is saved to the back of the queue 
	}
}
void Temple::monstersMove()//calls the move function for all the alive monsters on the temple grid, if they had just been recently killed, call their drop function as well 
{	
	for (int i = 0; i < n_monsters; i++)
	{	
		if (m_monster[i]->getHp() <= 0 && m_monster[i]->isMonsterAlive())
			m_monster[i]->drop();
		m_monster[i]->move();
	}					
}
void Temple::insertObject(Objects* obj)//inserts a new object into the temple's objects array, useful when the monster's drop gameObjects 
{
	m_objects[n_objects] = obj; 
	n_objects++; 
}
bool Temple::isMonsterHere(int c, int r)const //returns true if a monster is currently at some location on the map 
{
	if (temple[c][r] == 'B' || temple[c][r] == 'G' || temple[c][r] == 'S' || temple[c][r] == 'D')
		return true; 
	return false; 
}
void Temple::playerMove(char d)//move function for the player that takes in a char that determines the direction of movement 
{
	int r = m_player->rows(); 
	int c = m_player->cols(); 
	switch (d)
	{
	case'h'://move left 
		if (canWalk(c - 1, r))
		{
			temple[c][r] = ' ';
			temple[c - 1][r] = '@';
			m_player->setCols(c - 1);
			return;
		}
		else if (isMonsterHere(c - 1, r))//attack monster to the left 
			attack(r, c, r, c - 1);
		break;
	case'l'://move right 
		if (canWalk(c + 1, r))
		{
			temple[c][r] = ' ';
			temple[c + 1][r] = '@';
			m_player->setCols(c + 1); 
			return;
		}
		else if (isMonsterHere(c + 1, r)) //attack monster to the right 
			attack(r, c, r, c + 1);
		break;
	case'k'://move up 
		if (canWalk(c , r - 1))
		{
			temple[c][r] = ' ';
			temple[c][r-1] = '@';
			m_player->setRows(r - 1); 
			return;
		}
		else if (isMonsterHere(c, r-1)) //attack monster above player 
			attack(r, c, r-1, c);
		break;
	case'j'://move down 
		if (canWalk(c, r + 1))
		{
			temple[c][r] = ' ';
			temple[c][r+1] = '@';
			m_player->setRows(r + 1);
			return;
		}
		else if (isMonsterHere(c, r+1)) //attack monster below player 
			attack(r, c, r+1, c);
		break;
	default:
		break; 
	}
}
void Temple::createCooridor()//funtion that generates the coordiors that connects each room
{	
	// Sort rooms by the x-coordinate of their center
	std::sort(m_rooms.begin(), m_rooms.end(), [](Room* a, Room* b) {
		return (a->getUX() + a->getLX()) / 2 < (b->getUX() + b->getLX()) / 2;
		});
	for (size_t i = 0; i < m_rooms.size() - 1; ++i) {
		Room* room1 = m_rooms[i];
		Room* room2 = m_rooms[i + 1];
		int x1 = (room1->getUX() + room1->getLX()) / 2;
		int y1 = (room1->getUY() + room1->getLY()) / 2;
		int x2 = (room2->getUX() + room2->getLX()) / 2;
		int y2 = (room2->getUY() + room2->getLY()) / 2;
		drawCooridor(x1, y1, x2, y2);
	}
}
void Temple::drawCooridor( int x1, int y1, int x2, int y2)
{	
	//Draw horizontal cooridor 
	for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
		temple[x][y1] = ' ';
	}
	// Draw vertical corridor
	for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y) {
		temple[x2][y] = ' ';
	}
}
bool Temple::createRoom(Room* x)//boolean function that returns true if a particular rooms can be created, that is, it does not overlap with rooms created before. 
{	
	if (x == nullptr) {
		//std::cerr << "Error: Null pointer passed to createRoom\n";
		return false;
	}
	for (int i = 0; i < m_rooms.size(); i++) {
		if (m_rooms[i] == nullptr) {
			//std::cerr << "Error: Null pointer found in m_rooms\n";
			return false;
		}
		if (m_rooms[i]->isInRoom(x->getUX(), x->getUY(), x->getLX(), x->getLY())) {
			return false;
		}
	}
	m_rooms.push_back(x);
	for (int i = x->getLX(); i < x->getUX(); i++)
	{
		for (int j = x->getUY(); j < x->getLY(); j++)
			temple[i][j] = ' '; //prints out the room 
	}
	return true;	
}
void Temple::generate()//main function in temple that handles room coordinate generation, monster and gameObjects generation, and cooridors
{	
	m_levels++;
	if (m_levels != 0)
	{
		for (int i = 0; i < 70; i++)
		{
			for (int j = 0; j < 18; j++)
				temple[i][j] = '#'; //first initialized the map with all ### 
		}
	} 
	int rooms = 0; 
	if (trueWithProbability(0.1)) //10 percent chance with 3 rooms 
		rooms = 3;
	else
		rooms = randInt(4, 6); //90 percent choose randomly between 4 to 6  
	for (int i = 0; i < rooms; i++)
	{
		int Xsize = 0;
		int Ysize = 0; 
		if (rooms == 6)//room size randomization if 6 rooms will be created 
		{
			if (trueWithProbability(0.2))
				Xsize = randInt(9, 15);
			else
				Xsize = randInt(10, 15);
			if (trueWithProbability(0.2))
				Ysize = randInt(3, 8);
			else
				Ysize = randInt(3, 7); 
		}
		else if (rooms == 5)//room size randomization if 5 rooms will be created 
		{
			if (trueWithProbability(0.1))
				Xsize = randInt(8, 15);
			else
				Xsize = randInt(10, 14);
			if (trueWithProbability(0.1))
				Ysize = randInt(3, 10);
			else
				Ysize = randInt(5, 9);	
		}
		else //room size randomization if 4 or 3 rooms will be created 
		{	
			if (trueWithProbability(0.1))
				Xsize = randInt(8, 15);
			else
				Xsize = randInt(12, 14);
			Ysize = randInt(3, 9);
		}
		int ux = randInt(1, 69);
		int uy = randInt(1, 17);
		int lx = randInt(1, 69);
		int ly = randInt(1, 17);
		while (ux <= lx || uy >= ly || ux - lx != Xsize || ly - uy != Ysize) //generate room coordinates that are valid 
		{
			ux = randInt(1, 69);
			uy = randInt(1, 17);
			lx = randInt(1, 69);
			ly = randInt(1, 17);
		}
		Room* x = new Room(this, ux, uy, lx, ly);
		if (!createRoom(x))//if the rooms overlaps with old rooms, delete the room created and decrement the loop index so a new room can be created 
		{
			i--;
			delete x; 
		}	
	}
	createCooridor();//calls functions that makes cooridors, actors, and objects 
	actorsAndObjects(); 
}
void Temple::emptyCoord(int &r, int &c) const //r and c are passed into the function by reference, r and c are empty spaces on the temple grid 
{
	r = randInt(1, 17); 
	c = randInt(1, 69); 
	while (temple[c][r] != ' ')
	{
		r = randInt(1, 17);
		c = randInt(1, 69);
	}
}
void Temple::setCurrentChar(int r, int c, char d) //setter for the temple grid for classes outside the Temple class, give they provide a char d 
{
	temple[r][c] = d;  
}
void Temple::actorsAndObjects()//function that create and intialize the actors and objects on the temple gird 
{
	int r, c; 
	emptyCoord(r, c); //generate a randomly coordinate for the player 
	m_player->setCols(c);
	m_player->setRows(r); 
	temple[c][r] = '@';//place the player on that random coordinate 
	n_monsters = randInt(2, 5 * (m_levels + 1) + 1); //random number of monsters 
	n_objects += randInt(2, 3); //random number of objects 
	for (int i = 0; i < n_monsters; i++)
	{	
		//appropriate monsters are generated on each level using trueWithProbability 
		//weapons are created using dynamically allocated memory and will be deleted in the actors' destructor 
		if (m_levels == 2)//valid monsters for level 2 of the game 
		{
			if (trueWithProbability(1.0/3.0))//Boogeymen 
			{
				emptyCoord(r, c);
				Weapon* sw = new Weapon(r, c ,"short sword", 0 , 2);
				m_monster[i] = new Bogeymen(this, sw, r, c, randInt(5, 10), 2, randInt(2, 3), randInt(2, 3)); 
				temple[c][r] = 'B'; 
				
			}
			else if (trueWithProbability(1.0 / 2.0))//Snakewomen 
			{
				emptyCoord(r, c); 
				Weapon* fang = new Weapon(r, c, "magic fangs", 3, 2);
				m_monster[i] = new Snakewomen(this, fang, r, c, randInt(3, 6), 3, 2, 3); 
				temple[c][r] = 'S'; 
			}
			else //Goblin
			{
				emptyCoord(r, c); 
				Weapon* sw = new Weapon(r, c, "short sword", 0, 2);
				m_monster[i] = new Goblins(this, sw, r, c, randInt(15, 20), 1, 3, 1, m_game->getDistance());
				temple[c][r] = 'G'; 
			}
		}
		else if (m_levels > 2) //valid monsters for levels 3 and 4 
		{
			if (trueWithProbability(1.0 / 4.0))//Boogeymen 
			{
				emptyCoord(r, c);
				Weapon* sw = new Weapon(r, c, "short sword", 0, 2);
				m_monster[i] = new Bogeymen(this, sw, r, c, randInt(5, 10), 2, randInt(2, 3), randInt(2, 3));
				temple[c][r] = 'B';
			}
			else if (trueWithProbability(1.0 / 3.0))//Snakewomen 
			{
				emptyCoord(r, c);
				Weapon* fang = new Weapon(r, c, "magic fangs", 3, 2);
				m_monster[i] = new Snakewomen(this, fang, r, c, randInt(3, 6), 3, 2, 3);
				temple[c][r] = 'S';
			}
			else if (trueWithProbability(1.0 / 2.0))//Goblin
			{
				emptyCoord(r, c);
				Weapon* sw = new Weapon(r, c, "short sword", 0, 2);
				m_monster[i] = new Goblins(this, sw, r, c, randInt(15, 20), 1, 3, 1, m_game->getDistance());//goblins gets passed in the smell distance forom the game class 
				temple[c][r] = 'G';
			}
			else
			{
				emptyCoord(r, c);
				Weapon* ls = new Weapon(r, c, "long sword", 2, 4);
				m_monster[i] = new Dragon(this, ls, r, c, randInt(20, 25), 4, 4, 4);
				temple[c][r] = 'D';
			}
		}
		else //valid monsters for level 0 and 1 
		{
			if (trueWithProbability(1.0 / 2.0))//Snakewomen 
			{
				emptyCoord(r, c);
				Weapon* fang = new Weapon(r, c, "magic fangs", 3, 2);
				m_monster[i] = new Snakewomen(this, fang, r, c, randInt(3, 6), 3, 2, 3);
				temple[c][r] = 'S';
			}
			else//Goblin
			{
				emptyCoord(r, c);
				Weapon* sw = new Weapon(r, c, "short sword", 0, 2);
				m_monster[i] = new Goblins(this, sw, r, c, randInt(15, 20), 1, 3, 1, m_game->getDistance());
				temple[c][r] = 'G';
			}
		}	
	}
	for(int i = 0; i < n_objects; i++)//generate the gameObjects 
	{	
		emptyCoord(r, c);//random coordinate 
		if (i == n_objects-1 && m_levels < 4)//generate a staircase object 
		{
			Objects* stair = new Objects(r, c, "stair"); 
			m_objects[i] = stair; 
			temple[c][r] = '>'; 
		}
		else if (i == n_objects - 1 && m_levels == 4)//generate a golden idol if the game is at level 4 
		{
			Objects* idol = new Objects(r, c, "idol"); 
			m_objects[i] = idol; 
			temple[c][r] = '&'; 
		}
		if (i == n_objects - 1)
			break; 
		int randObj = randInt(1, 7); //magic fangs of sleep, magic axes, and teleportation scrolls are never placed on the level
		if (randObj == 1)//mace 
		{
			Objects* Maces = new Weapon(r, c, "mace", 0, 2); 
			m_objects[i] = Maces; 
			temple[c][r] = ')'; 
		}
		else if (randObj == 2)//short sword 
		{
			Objects* sw = new Weapon(r, c, "short sword", 0, 2);
			m_objects[i] = sw;
			temple[c][r] = ')';
		}
		else if (randObj == 3)//long sword 
		{
			Objects* ls = new Weapon(r, c, "long sword", 2, 4);
			m_objects[i] = ls;
			temple[c][r] = ')';
		}
		else if (randObj == 4)//enhance armor scroll 
		{
			Objects* ia = new Scroll(r, c, "enhance armor");
			m_objects[i] = ia;
			temple[c][r] = '?';
		}
		else if (randObj == 5)//strength scroll 
		{
			Objects* rs = new Scroll(r, c, "strength");
			m_objects[i] = rs;
			temple[c][r] = '?';
		}
		else if (randObj == 6) //enhance health scroll 
		{
			Objects* eh = new Scroll(r, c, "enhance health");
			m_objects[i] = eh;
			temple[c][r] = '?';
		}
		else //enhance dexterity scroll 
		{
			Objects* ed = new Scroll(r, c, "enhance dexterity");
			m_objects[i] = ed;
			temple[c][r] = '?';
		}	
	}	
}
