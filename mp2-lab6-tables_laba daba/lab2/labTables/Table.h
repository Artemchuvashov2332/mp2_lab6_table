#pragma once
#include <exception>
#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>

//----------Class Rec------

template<class Key, class Data>
class Rec {
public:
    Key key;
    Data data;

    bool operator ==(const Key&);
    bool operator !=(const Key&);
    friend std::ostream& operator<<(std::ostream& os, const Rec<Key, Data>& d);

    Rec(Key _key, Data _data) : key(_key), data(_data) {}
};

template<class Key, class Data>
inline bool Rec<Key, Data>::operator!=(const Key& _key)
{
    return key != _key;
}

template<class Key, class Data>
inline bool Rec<Key, Data>::operator==(const Key& _key)
{
    return key == _key;
}

template<class Key, class Data>
std::ostream& operator<<(std::ostream& os, const Rec<Key, Data>& d)
{
    os << "key: " << d.key << " data: " << d.data << std::endl;
    return os;
}

template<class Key, class Data>
class Table {
protected:
    int size;
    int count;
    Rec<Key, Data>* dataArray;

public:
    Table(int _size = 10) : size(_size), count(0)
    {
        dataArray = new Rec<Key, Data>[size];
    }

    void Add(Key key, Data data)
    {
        dataArray[count].key = key;
        dataArray[count].data = data;
        ++count;
    }

    Data Find(Key key) {
        for (int i = 0; i < count; ++i)
            if (dataArray[i].key == key)
                return dataArray[i].data;
        throw std::exception("Not found");
    }
    
    int getSize() const { return size; }
    int getCount() const { return count; }

    Rec<Key, Data> getRec(int i) const
    {
        return dataArray[i];
    }
};


template<class Key, class Data>
class SortTable : public Table<Key, Data >
{
public:
    SortTable(size_t _size);
    SortTable(const SortTable<Key, Data>& table);
    SortTable(const Table<Key, Data>& table); //done
    void Add(Key key, Data data);
    Data Find(Key key);
    void Delete(const Key& key);
    Data& operator[](const Key& key);
};

template<class Key, class Data>
SortTable<Key, Data>::SortTable(size_t _size) : Table<Key, Data>::Table(_size) { };



template<class Key, class Data>
SortTable<Key, Data>::SortTable(const SortTable<Key, Data>& table) {
    this->size = table.size;
    this->count = table.count;
    this->dataArray = new Rec<Key, Data>[this->size];
    for (int i = 0; i < this->count; ++i)
    {
        this->dataArray[i] = table.dataArray[i];
    }
}

template<class Key, class Data>
SortTable<Key, Data>::SortTable(const Table<Key, Data>& table)
{
    this->size = table.getSize();
    this->count = table.getCount();
    this->dataArray = new Rec<Key, Data>[this->size];
    for (int i = 0; i < this->count; i++)
        this->dataArray[i] = table.getRec(i);

    for (int i = 0; i < this->count; i++)
        for (int j = 0; j < this->count; j++)
            if (this->dataArray[i].data > this->dataArray[j].data)
                std::swap(this->dataArray[i], this->dataArray[j]);
}

template<class Key, class Data>
void SortTable<Key, Data>::Add(Key key, Data data) {
    int i = 0;
    while (i < this->count)
    {
        if (this->dataArray[i].key <= key) continue;
        break;
    }
    for (int j = this->count; j > i; j--)
    {
        this->dataArray[j].key = this->dataArray[j - 1].key;
        this->dataArray[j].data = this->dataArray[j - 1].data;
    }
    this->dataArray[i].key = key;
    this->dataArray[i].data = data;
    ++this->count;
}

template<class Key, class Data>
Data SortTable<Key, Data>::Find(Key key) {
    int l = 0, r = this->count - 1;
    while (l + 1 < r)
    {
        int mid = (l + r) / 2;
        if (this->dataArray[mid].key > key)
            r = mid;
        else l = mid;
    }
    if (this->dataArray[l].key == key) return this->dataArray[l].data;
    if (this->dataArray[r].key == key) return this->dataArray[r].data;
    throw std::runtime_error("Not Found");
}

template<class Key, class Data>
Data& SortTable<Key, Data>::operator[](const Key& key) {
    int l = 0, r = this->count - 1;
    while (l + 1 < r)
    {
        int mid = (l + r) / 2;
        if (this->dataArray[mid].key > key)
            r = mid;
        else l = mid;
    }
    if (this->dataArray[l].key == key) return this->dataArray[l].data;
    if (this->dataArray[r].key == key) return this->dataArray[r].data;
    throw std::runtime_error("Not Found");
}

template<class Key, class Data>
void SortTable<Key, Data>::Delete(const Key& key)
{
    int i = 0;
    while (i < this->count)
    {
        if (this->dataArray[i++].key < key) continue;
        break;
    }
    for (i; i < this->count; i++)
    {
        this->dataArray[i].key = this->dataArray[i + 1].key;
        this->dataArray[i].data = this->dataArray[i + 1].data;
    }
}

