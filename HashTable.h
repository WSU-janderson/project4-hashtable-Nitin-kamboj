/**
 * HashTable.h
 */
#include <iostream>
#include <optional>
#include <vector>
using namespace std;
#include "HashTableBucket.h"
class HashTable {
public:
    size_t capcity;
    size_t Size = 0;
    size_t numOfElements;
    vector<size_t> offsets;
    vector<HashTableBucket> buckets;
    static constexpr size_t DEFAULT_INITIAL_CAPACITY = 8;
    size_t hashfunction(const string& key) const;

    HashTable(size_t initCapacity = DEFAULT_INITIAL_CAPACITY);
    ~HashTable();
    bool insert(string key, int value);
    bool remove(string key);
    bool contains(string key);
    optional<int> get(const string& key) const;
    int& operator[](const string& key);
    vector<string> keys() const;
    double alpha() const;
    size_t capacity() const;
    size_t size() const;
    friend ostream& operator<<(ostream& os, const HashTable& HashTable);
    void resize();
};
