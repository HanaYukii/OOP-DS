#ifndef HASHTABLE
#define HASHTABLE

#include <bits/stdc++.h>
using namespace std;
typedef struct ht
{
    string Gender;
    int Height;
    int Weight;
}ht;

class HashTable
{
    public:
        HashTable();

        void addItem(string key, string Gender, int Height, int Weight);

        HashTable &operator[](string s);

        string getGender();

        int getHeight();

        int getWeight();


    private:
        unordered_map<string,ht> key;
        int size;
        string search;
};

#endif // HASHTABLE

