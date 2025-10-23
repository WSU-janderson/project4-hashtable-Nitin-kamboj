/**
 * HashTable.cpp
 */
#include "HashTable.h"
# include <iostream>
using namespace std;
    HashTable::HashTable(size_t capcity) {
        this->capcity = capcity;
        for (int i = 0; i < capcity; i++) {
            buckets.push_back(HashTableBucket());
        }

    }
bool HashTable::insert(string key, size_t value) {
      size_t s = hashfunction(key);
        size_t insertPlace = s % capcity;
        if (buckets[insertPlace] == -1) {

        }

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

