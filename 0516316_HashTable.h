#ifndef HASHTABLE
#define HASHTABLE

#include <bits/stdc++.h>
using namespace std;


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
        vector<int> Height, Weight;
        vector<string> Gender;
        unordered_map<string,int> key;
        int size;
        int search;
};

#endif // HASHTABLE

