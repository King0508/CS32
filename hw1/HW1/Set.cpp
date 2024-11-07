#include "Set.h"
Set::Set() : m_size(0)
{

}

bool::Set::empty() const
{
	if (m_size == 0)
	{
		return true; 
	}
	return(false); 
}

int::Set::size() const
{
	return(m_size);
}

bool::Set::insert(const ItemType& value)
{
	if (m_size == DEFAULT_MAX_ITEMS)
		return false; 
	for (int i = 0; i < m_size; i++)
	{
		if (m_set[i] == value)
			return false; 	
	}
	m_set[m_size] = value; 
	m_size++; 
	return true; 
}
bool ::Set::erase(const ItemType& value)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_set[i] == value)
		{
			for (int k = i; k < m_size-1; k++)
			{
				m_set[k] = m_set[k + 1];
			}
			m_size--;
			return true;
		}
	}
	return false; 
}

bool::Set::contains(const ItemType& value) const
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_set[i] == value)
			return true; 
	}
	return false; 
}

bool::Set::get(int i, ItemType& value) const
{
	if (i >= 0 && i < m_size)
	{
		for (int k = 0; k < m_size; k++)
		{
			int counter = 0;
			for (int j = 0; j < m_size; j++)
			{
				if (m_set[k] < m_set[j])
				{
					counter++; 
				}
			}
			if (counter == i)
			{
				value = m_set[k]; 
				return true; 
			}
		}
	}
	return false; 
}

void ::Set::swap(Set& other)
{
	ItemType tempType; 
	int tempSize = 0; 
	int loop = 0; 
	if (m_size >= other.size())
	{
		 loop = m_size; 
	}
	else
	{
		loop = other.size(); 
	}
	for (int i = 0; i < loop; i++)
	{
		tempType = m_set[i]; 
		m_set[i] = other.m_set[i];
		other.m_set[i] = tempType; 
	}
	tempSize = other.size(); 
	other.m_size = m_size; 
	m_size = tempSize; 
}