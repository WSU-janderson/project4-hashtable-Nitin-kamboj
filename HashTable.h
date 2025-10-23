/**
 * HashTable.h
 */
#include <iostream>
#include <vector>
using namespace std;

struct HashTableBucket {
enum class BucketType {NORMAL, ESS, EAR};
public:

    string key;
    size_t value;
    BucketType bucketType;
    HashTableBucket();
    HashTableBucket(string key, size_t value);
    void load(string key, size_t value);
    bool isEmpty() const;
    friend ostream& operator<<(ostream& os, const HashTableBucket& bucket);
};
class HashTable {
public:
    size_t capcity;
    size_t numOfElements;
    vector<size_t> offsets;
    vector<HashTableBucket> buckets;

    size_t hashfunction(string& key);

    HashTable();
    HashTable(size_t initCapacity = 8);
    ~HashTable();
    bool insert(string key, size_t value);
    bool remove(string key);
    bool contains(string key);
    int get(string key);
    int& operator[](string key);
    vector<string> keys();
    double alpha();
    size_t capacity();
    size_t size();
    friend ostream& operator<<(ostream& os, const HashTable& HashTable);
};
