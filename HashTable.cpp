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
        // for (size_t i = 1; i < capcity; ++i) {
        //     offsets.push_back((i * 7) % capcity);
        // }
        while (offsets.size() < capcity - 1 ) {
            bool duplicate = false;
            int random = rand() % capcity;
            if (random > 0) {
                for (int i = 0; i < offsets.size(); i++) {
                    if (random == offsets.at(i)) {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate) {
                    offsets.push_back(random);
                }
            }
        }
    }
    HashTable::~HashTable() {

    }

bool HashTable::insert(string key, int val) {
        if (contains(key)) {
            return false;
        }
      size_t home = hashfunction(key);
        size_t insertPlace = home % capcity;
        int i = 0;
        size_t emptySpot;
        bool empty = false;
        if (buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::ESS ||
        buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::EAR) {
            buckets.at(insertPlace).load(key, val);
            Size++;
            resize();
            return true;
        }
        else {
                while (i < offsets.size()) {
                    insertPlace = (offsets.at(i) + home) % capcity;
                    if (buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::NORMAL &&
                buckets.at(insertPlace).key == key) {
                        return false;
                    }
                    if ((buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::ESS ||
        buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::EAR) && (empty == false)) {
                        emptySpot = insertPlace;
                        empty = true;
                    }
                    i++;
                }
        }
        if (empty) {
            buckets.at(emptySpot).load(key, val);
            Size++;
            resize();
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
            Size--;
            return true;
        }
        while (i < offsets.size()) {
            checkingPlace = (offsets.at(i) + home) % capcity;
            if (buckets.at(checkingPlace).key == key && buckets.at(checkingPlace).bucketType == HashTableBucket::BucketType::NORMAL) {
                buckets.at(checkingPlace).key = "";
                buckets.at(checkingPlace).bucketType = HashTableBucket::BucketType::EAR;
                Size--;
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
optional<int> HashTable::get( const string& key) const {
        size_t home = hashfunction(key);
        size_t checkingPlace = home % capcity;
        int i = 0;
        if (buckets.at(checkingPlace).key == key && buckets.at(checkingPlace).bucketType == HashTableBucket::BucketType::NORMAL) {
            return buckets.at(checkingPlace).value;
        }
        while (i < offsets.size()) {
            checkingPlace = (offsets.at(i) + home) % capcity;
            if (buckets.at(checkingPlace).key == key && buckets.at(checkingPlace).bucketType == HashTableBucket::BucketType::NORMAL) {
                return buckets.at(checkingPlace).value;
            }
            i++;
        }
        return nullopt;

    }
int& HashTable::operator[](const string& key) {
    size_t home = hashfunction(key);
    size_t checkingPlace = home % capcity;
    int i = 0;
    if (buckets.at(checkingPlace).key == key && buckets.at(checkingPlace).bucketType == HashTableBucket::BucketType::NORMAL) {
        return buckets.at(checkingPlace).value;
    }
    while (i < offsets.size()) {
        checkingPlace = (offsets.at(i) + home) % capcity;
        if (buckets.at(checkingPlace).key == key && buckets.at(checkingPlace).bucketType == HashTableBucket::BucketType::NORMAL) {
            return buckets.at(checkingPlace).value;
        }
        i++;
    }
    throw std::runtime_error("Key not found");
}
vector<string> HashTable::keys() const{
        vector<string> keys;
        size_t size = this->capacity();
        for (int i = 0; i < size; i++) {
            if (buckets.at(i).bucketType == HashTableBucket::BucketType::NORMAL) {
                keys.push_back(buckets.at(i).key);
            }
        }
        return keys;
}
double HashTable::alpha() const {
        double alpha = static_cast<double> (Size)/static_cast<double>(capcity);
        return alpha;
}
size_t HashTable::capacity() const {
        return capcity;
}

size_t HashTable::size() const {
        return Size;
    }
// used to convert string to int value for probing
size_t HashTable::hashfunction(const string& key) const{
        size_t result = 0;
        for (int i = 0;i < key.length(); i++) {
            char c = key[i];
            result += static_cast<size_t>(c);
        }
        return result;
    }

ostream& operator<<(ostream& os, const HashTable& hashTable) {
        for (size_t i = 0; i < hashTable.buckets.size(); ++i) {
            if (hashTable.buckets[i].bucketType == HashTableBucket::BucketType::NORMAL) {
                os << "Bucket " << i << ": " << hashTable.buckets[i] << std::endl;
            }
        }
        return os;
    }

void HashTable::resize() {
        double alpha = static_cast<double> (Size)/static_cast<double>(capcity);
        // cout<< alpha << endl;

        if (alpha > 0.5) {
            offsets.clear();
            this->capcity = capcity * 2;
            Size = 0;
            // for (size_t i = 1; i < capcity; ++i) {
            //     offsets.push_back((i * 7) % capcity);
            // }
            while (offsets.size() < capcity - 1 ) {
                bool duplicate = false;
                int random = rand() % capcity;
                if (random > 0) {
                    for (int i = 0; i < offsets.size(); i++) {
                        if (random == offsets.at(i)) {
                            duplicate = true;
                            break;
                        }
                    }
                    if (!duplicate) {
                        offsets.push_back(random);
                    }
                }
            }
            vector<HashTableBucket> oldbucket = buckets;
            buckets.clear();
            buckets.resize(capcity);
            for (int i = 0; i < oldbucket.size(); i++) {
                int j =0;
                size_t home;
                size_t insertPlace;
                if (oldbucket.at(i).key != "") {
                    home = hashfunction(oldbucket.at(i).key);
                    insertPlace = home % capcity;
                    if (buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::ESS) {
                        buckets.at(insertPlace).load(oldbucket.at(i).key, oldbucket.at(i).value);
                        Size++;
                    }
                    else {
                        while (j < offsets.size()) {
                            insertPlace = (offsets.at(j) + home) % capcity;
                            if (buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::ESS) {
                                buckets.at(insertPlace).load(oldbucket.at(i).key, oldbucket.at(i).value);
                                 Size++;
                                 break;
                }
                            j++;
                        }
                    }
                }
            }
        }

    }