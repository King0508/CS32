#include "History.h"
#include <iostream>
using namespace std; 
History::History(int nRows, int nCols) :m_nRows(nRows), m_nCols(nCols), m_record(0)//the member initialization list initializes the private row and column data and sets intial tooters preached to zero 
{
	
}

bool History::record(int r, int c)
{

	if (r > m_nRows|| c > m_nCols)
	{
		return(false); //if the location is invalid, that is outside the history map dimensions in m_nRow and m_nCols, the function returns false 
		
	}
	m_r[m_record] = r - 1;//the -1 adjusts the coordinate system of the game map to the coordinate system of the history  map 
	m_c[m_record] = c -1;
	m_record++;//each time the .record function is called, an additional tooters should have been preached 
	return(true);//if r and c are valid locations, the function should return true 
	
}

void History::display() const
{
	clearScreen();
	char grid[MAXROWS][MAXCOLS];//make a 2-dimensional array of character to form a history map 
	int r, c;
	// Fill the grid with dots, and update the 2d array as Tooters are preached
	for (r = 0; r < m_nRows; r++)
	{	//loops through the rows of the history map 
		for (c = 0; c < m_nCols; c++)
		{	//loops through the columns of the history map 
				grid[r][c] = '.';//fill each spot in the 2-d array with '.'
				for (int k = 0; k < m_record; k++)
				{
					if (grid[m_r[k]][m_c[k]] == '.')
					{	//if a tooter is preached for the first time in some location, the character at that locatoin is set to 'A' 
						grid[m_r[k]][m_c[k]] = 'A'; 
					}
					else if (grid[m_r[k]][m_c[k]] < 'Z')
					{	//if a tooter is preached not for the first time in some location, the integral value of the character at that location is added by 1. The value of the Char does not exceed 'Z' 
						grid[m_r[k]][m_c[k]]++; 
					}
				}
				cout << grid[r][c]; //print out the history map that contains the information about where and how many tooters have been preached on the map 
		}	
		cout << endl; //prints an empty line so the history map looks like the game map 
	}
	cout << endl; //adds an empty line after the history's display function as the spec indicates 
}

