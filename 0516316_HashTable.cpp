#include "0516316_HashTable.h"
HashTable::HashTable()
{
    Height.clear();
    Weight.clear();
    Gender.clear();
    key.clear();
    size=0;
};
void HashTable::addItem(string key, string Gender, int Height, int Weight)
{
    this->key.insert(make_pair(key,size));
    this->Height.push_back(Height);
    this->Weight.push_back(Weight);
    this->Gender.push_back(Gender);
    size++;
};
HashTable &HashTable::operator[](string s)
{
    search=key[s];
    return *this;
};
string HashTable::getGender()
{
    return Gender[search];
};
int HashTable::getHeight()
{
    return Height[search];
};
int HashTable::getWeight()
{
    return Weight[search];
};
