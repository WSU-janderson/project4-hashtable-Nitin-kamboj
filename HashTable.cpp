/**
 * HashTable.cpp
 */
#include "HashTable.h"
#include "HashTableBucket.h"
# include <iostream>
using namespace std;
    HashTable::HashTable(size_t capcity) {
        this->capcity = capcity;
        for (int i = 0; i < capcity; i++) {
            buckets.push_back(HashTableBucket());
        }

    }
bool HashTable::insert(string key, size_t val) {
      size_t home = hashfunction(key);
        size_t insertPlace = home % capcity;
        int i = 0;
        size_t emptySpot;
        bool empty = false;
        if (buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::ESS ||
        buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::EAR) {
            buckets.at(insertPlace).value = val;
        }
        else {
                while (i < offsets.size()) {
                    insertPlace = (offsets.at(i) + home) % capcity;
                    if (buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::NORMAL &&
                buckets.at(insertPlace).key == key) {
                        return false;
                    }
                    if (buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::ESS ||
        buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::EAR) {
                        emptySpot = insertPlace;
                        empty = true;
                    }
                    i++;
                }
        }
        if (empty) {
            buckets.at(emptySpot).value = val;
        }
    return false;
    }
bool HashTable::remove(string key) {

}
bool HashTable::contains(string key) {

    }
int HashTable::get(string key) {

    }
int& HashTable::operator[](string key) {

}
vector<string> HashTable::keys() {

}
double HashTable::alpha() {

}
size_t HashTable::capacity() {

}

size_t HashTable::size() {

    }
size_t HashTable::hashfunction(string& key) {
        size_t result = 0;
        for (int i = 0;i < key.length(); i++) {
            char c = key[i];
            result += static_cast<size_t>(c);
        }
        return result;
    }

