/**
 * HashTable.cpp
 */
#include "HashTable.h"
#include "HashTableBucket.h"
# include <iostream>
#include <bits/locale_facets_nonio.h>
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
            buckets.at(insertPlace).load(key, val);
            return true;
        }
        else {
                while (i < offsets.size()) {
                    insertPlace = (offsets.at(i) + home) % capcity;
                    if (buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::NORMAL &&
                buckets.at(insertPlace).key == key) {
                        return false;
                    }
                    if (buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::ESS ||
        buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::EAR && (empty == false)) {
                        emptySpot = insertPlace;
                        empty = true;
                    }
                    i++;
                }
        }
        if (empty) {
            buckets.at(emptySpot).load(key, val);
            return true;
        }
    return false;
    }
bool HashTable::remove(string key) {
        size_t home = hashfunction(key);
        size_t checkingPlace = home % capcity;
        int i = 0;
        if (buckets.at(checkingPlace).key == key && buckets.at(checkingPlace).bucketType == HashTableBucket::BucketType::NORMAL) {
            buckets.at(checkingPlace).key = "";
            buckets.at(checkingPlace).bucketType = HashTableBucket::BucketType::EAR;
            return true;
        }
        while (i < offsets.size()) {
            checkingPlace = (offsets.at(i) + home) % capcity;
            if (buckets.at(checkingPlace).key == key && buckets.at(checkingPlace).bucketType == HashTableBucket::BucketType::NORMAL) {
                buckets.at(checkingPlace).key = "";
                buckets.at(checkingPlace).bucketType = HashTableBucket::BucketType::EAR;
                return true;
            }
            i++;
        }
        return false;
}
bool HashTable::contains(string key) {
        size_t home = hashfunction(key);
        size_t checkingPlace = home % capcity;
        int i = 0;
        if (buckets.at(checkingPlace).key == key && buckets.at(checkingPlace).bucketType == HashTableBucket::BucketType::NORMAL) {
            return true;
        }
        while (i < offsets.size()) {
            checkingPlace = (offsets.at(i) + home) % capcity;
            if (buckets.at(checkingPlace).key == key && buckets.at(checkingPlace).bucketType == HashTableBucket::BucketType::NORMAL) {
                return true;
            }
            i++;
        }
        return false;

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

