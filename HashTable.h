/**
 * HashTable.h
 */
#include <iostream>
#include <vector>
using namespace std;

struct HashTableBucket {
enum class BucketType {Normal, ESS, EAR};
public:
    string key;
    int value;
    BucketType bucketType;
    HashTableBucket();
    HashTableBucket(string key, int value);
    void load(string key, int value);
    bool isEmpty();
    friend ostream& operator<<(ostream& os, const HashTableBucket& bucket);
};
class HashTable {
    public:
    size_t capcity;
    HashTable();
    HashTable(size_t initCapacity = 8);
    ~HashTable();
    bool insert(string key, int value);
    bool remove(string key);
    bool contains(string key);
    int get(string key);
    int operator[](string key);
    vector<string> keys();
    double alpha();
    size_t capacity();
    size_t size();
    friend ostream& operator<<(ostream& os, const HashTable& HashTable);
};
