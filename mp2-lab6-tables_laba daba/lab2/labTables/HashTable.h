#pragma once
#include <exception>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>

template<class Key>
int ownhashfunction(Key key, int size)
{
    // type your function here
    return 0;
}

int HashFunc(int key, int size)
{
    return key % size;
}

int HashFunc(std::string key, int size)
{
    int res = 0;
    for (int i = 0; i < key.size(); i++)
        res += key[i];
    return res % size;
}


template<class Key, class Data>
class HashTable
{
protected:
    std::vector<std::list<Rec<Key, Data> > > dataVector;
    int size;
    int (*hashFunc)(Key, int);


public:
    HashTable(int Size = 10, bool _ownhashfunction = 0) : size(Size)
    {
        dataVector.resize(size);

        if (_ownhashfunction)
            hashFunc = ownhashfunction;
        else hashFunc = HashFunc;
    }

    void Add(Key key, Data data)
    {
        int index = hashFunc(key, size);

        dataVector[index].push_back(Rec<Key, Data>(key, data));
    }

    Data Find(Key key)
    {
        int index = hashFunc(key, size);
        typename std::list<Rec<Key, Data> >::iterator it = dataVector[index].begin();
        while (it->key != key)
            it++;
        return it->data;
    }
    int getSize() const { return size; }
};