#ifndef HASH_H
#define HASH_H
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <functional>

class HashTable {
public:
	HashTable(unsigned int size);//constructor takes in unsigned int for the the number of buckets 
	void insert(const std::string& key, unsigned int offset);//insert string key into the hashtable 
	bool find(const std::string& key, unsigned int &offset);//find function that takes 2 parameters, returns true if sequence can be found, false otherwise, offset is set to offset of the N length string 
	bool find(const std::string& key, unsigned int& offset, const std::string& fold, const std::string& fnew, int j, int& length); //find function that takes 6 parameters, does everything the other function does, but returns the greatest match length
private:
	std::vector <std::list<std::pair<std::string, unsigned int>> > table;
	std::hash<std::string> hashFunction; //hash function for std::string using std::hash 
};
#endif // !HASH_H