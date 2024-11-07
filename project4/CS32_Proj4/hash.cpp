#include <vector>
#include <list>
#include <string>
#include <utility>
#include <functional>
#include "hash.h"

HashTable::HashTable(unsigned int size): table(size){}

void HashTable::insert(const std::string& key, unsigned int offset) {
	unsigned int hashValue = hashFunction(key) % table.size();//hashFunction converts string key into an unsigned int
	table[hashValue].push_back(std::make_pair(key, offset));//make_pair makes a pair, then the pair is inserted 
}
bool HashTable::find(const std::string& key, unsigned int &offset) {
	unsigned int hashValue = hashFunction(key) % table.size();
	for (std::list<std::pair<std::string, unsigned int>>::const_iterator it = table[hashValue].begin(); it != table[hashValue].end(); it++) {
		if (it->first == key) {
			offset = it->second;//once a match is found, offset is set and the function returns 
			return true;
		}
	}
	return false;
}
bool HashTable::find(const std::string& key, unsigned int& offset, const std::string& fold, const std::string& fnew, int j, int& length) {
	unsigned int hashValue = hashFunction(key) % table.size();
	bool found = false; 
	int maxLength = 0; 
	for (std::list<std::pair<std::string, unsigned int>>::const_iterator it = table[hashValue].begin(); it != table[hashValue].end(); it++) {
		if (it->first == key) {
			int tempLength = key.length();//tempLength starts off as the length of key 
			int tempOffset = it->second;//tempOffset does not get updated to the actual offset until greatest match length is found 
			while (j + tempLength < fnew.size() && tempOffset + tempLength < fold.size() && fnew[j + tempLength] == fold[tempOffset + tempLength])
				tempLength++; 
			if (tempLength > maxLength) {//a newer longer length is found 
				maxLength = tempLength; 
				offset = tempOffset; 
				found = true; 
			}
		}
	}
	length = maxLength; //updates length 
	return found; //return if a match has been found yet 
}

