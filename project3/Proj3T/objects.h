#ifndef OBJECTS_H
#define OBJECTS_H


#include <string> 
class Objects
{
public:
	Objects(int r, int c, std::string name);
	void setRows(int r); 
	void setCols(int c); 
	int rows() const; 
	int cols() const; 
	std::string getName() const; 
	virtual ~Objects(); 
private:
	int m_rows; 
	int m_cols; 
	std::string m_name;
	
};
Objects::Objects(int r, int c, std::string name): m_rows(r), m_cols(c), m_name(name)
{

}
Objects::~Objects()
{}
int Objects::rows() const
{
	return(m_rows); 
}
int Objects::cols() const
{
	return(m_cols);
}
void Objects::setRows(int r)
{
	m_rows = r; 
}
void Objects::setCols(int c)
{
	m_cols = c;
}
std::string Objects::getName() const
{
	return m_name; 
}
class Weapon : public Objects
{
public:
	Weapon(int r, int c, std::string name, int dex, int dam);
	int getDex() const;
	int getDam() const; 
	~Weapon(); 
private:
	int m_dexBonus;
	int m_damage;
};
Weapon::Weapon( int r, int c, std::string name, int dex, int dam):Objects(r,c,name), m_dexBonus(dex), m_damage(dam)
{

}
Weapon::~Weapon()
{

}
int Weapon::getDex() const
{
	return(m_dexBonus); 
}
int Weapon::getDam() const
{
	return(m_damage); 
}
class Scroll : public Objects
{
public:
	Scroll(int r, int c, std::string name);
	~Scroll(); 
};
Scroll::Scroll(int r, int c, std::string name) :Objects( r, c, name)
{

}
Scroll::~Scroll()
{}
#endif 