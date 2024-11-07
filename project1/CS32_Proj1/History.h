#ifndef HISTORY_H
#define HISTORY_H
#include "globals.h"//include globals.h because we want to use a constant to indicate the size m_r and m_c 
class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
private: 
	int m_nRows; //the number of rows the history map has 
	int m_nCols; //the number of columns the history map has  
	int m_r[MAXTOOTERS]; //an array that contains the row location of all preached tooters 
	int m_c[MAXTOOTERS]; //an array that contains the column location of all preached tooters 
	int m_record;//an integer that counts the total number of tooters preached 
};
#endif

