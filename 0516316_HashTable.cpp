#include<bits/stdc++.h>
#include "_HashTable.h"

HashTable::HashTable()
{

    size=0;
};
void HashTable::addItem(string key, string Gender, int Height, int Weight)
{
    ht add;
    add.Gender=Gender;
    add.Height=Height;
    add.Weight=Weight;
    this->key.insert(make_pair(key,add));
    size++;
};
HashTable &HashTable::operator[](string s)
{
    search=s;
    return *this;
};
string HashTable::getGender()
{
    ht ans=key[search];
    return ans.Gender;
};
int HashTable::getHeight()
{
    ht ans=key[search];
    return ans.Height;
};
int HashTable::getWeight()
{
    ht ans=key[search];
    return ans.Weight;
};
