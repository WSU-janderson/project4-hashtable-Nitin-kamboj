/**
 * HashTable.cpp
 */
// File: HashTable.cpp
// Author: Nitin Kamboj
// Project: Hash Table Implementation (CS 3100 – Data Structures)
// Description:
//    This file implements the HashTable class, which provides a hash
//    table data structure using open addressing and custom probing.
//    Functions include insertion, removal, key lookup, resizing, and
//    operator overloading for easy access and printing.
#include "HashTable.h"
#include "HashTableBucket.h"
# include <iostream>
#include <bits/locale_facets_nonio.h>
using namespace std;
// default constructor which sets up the capacity of hashtable and offsets
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
/**
* Insert a new key-value pair into the table. Duplicate keys are NOT allowed. The
* method should return true if the insertion was successful. If the insertion was
* unsucessful, such as when a duplicate is attempted to be inserted, the method
* should return false
*/
bool HashTable::insert(string key, int val) {
        if (contains(key)) {
            return false;
        }
      size_t home = hashfunction(key);
        size_t insertPlace = home % capcity;
        int i = 0;
        size_t emptySpot;
        bool empty = false;
        // check if the first place is ESS
        if (buckets.at(insertPlace).bucketType == HashTableBucket::BucketType::ESS) {
            buckets.at(insertPlace).load(key, val);
            Size++;
            resize();
            return true;
        }
        else {
            // Do probing and check ESS place and if the place is EAR then set to true but check further till we gwt ESS to check duplication of key
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
        // if empty is true then there must be EAR so place that ket to that bucket
        if (empty) {
            buckets.at(emptySpot).load(key, val);
            Size++;
            resize();
            return true;
        }
    return false;
    }
/**
* If the key is in the table, remove will “erase” the key-value pair from the
* table. This might just be marking a bucket as empty-after-remove
*/
bool HashTable::remove(string key) {
        size_t home = hashfunction(key);
        size_t checkingPlace = home % capcity;
        int i = 0;
        // if key found at the first place
        if (buckets.at(checkingPlace).key == key && buckets.at(checkingPlace).bucketType == HashTableBucket::BucketType::NORMAL) {
            buckets.at(checkingPlace).key = "";
            buckets.at(checkingPlace).bucketType = HashTableBucket::BucketType::EAR;
            Size--;
            return true;
        }
        // probing to checking if there is key somewhere else in the hashtable
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
/**
* contains returns true if the key is in the table and false if the key is not in
* the table.
*/
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
/**
* If the key is found in the table, find will return the value associated with
* that key. If the key is not in the table, find will return something called
* nullopt, which is a special value in C++. The find method returns an
* optional<int>, which is a way to denote a method might not have a valid value
* to return. This approach is nicer than designating a special value, like -1, to
* signify the return value is invalid. It's also much better than throwing an
* exception if the key is not found.
*/
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
/**
* The bracket operator lets us access values in the map using a familiar syntax,
* similar to C++ std::map or Python dictionaries. It behaves like get, returnin
* the value associated with a given key:
 int idNum = hashTable[“James”];
* Unlike get, however, the bracker operator returns a reference to the value,
* which allows assignment:
 hashTable[“James”] = 1234;
 If the key is not
* in the table, returning a valid reference is impossible. You may choose to
* throw an exception in this case, but for our implementation, the situation
* results in undefined behavior. Simply put, you do not need to address attempts
* to access keys not in the table inside the bracket operator method.
*/

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
/**
* keys returns a std::vector (C++ version of ArrayList, or simply list/array)
* with all of the keys currently in the table. The length of the vector should be
* the same as the size of the hash table.
*/
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
/**
* alpha returns the current load factor of the table, or size/capacity. Since
* alpha returns a double,make sure to properly cast the size and capacity, which
* are size_t, to avoid integer division. You can cast a size_t num to a double in
* C++ like:
 static_cast<double>(num)
 The time complexity for
* this method must be O(1).
*/

double HashTable::alpha() const {
        double alpha = static_cast<double> (Size)/static_cast<double>(capcity);
        return alpha;
}
/**
* capacity returns how many buckets in total are in the hash table. The time
* complexity for this algorithm must be O(1).
*/

size_t HashTable::capacity() const {
        return capcity;
}
// returns the size of hashtable and using O(1) time complexity
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
/**
* operator<< is another example of operator overloading in C++, similar to
* operator[]. The friend keyword only needs to appear in the class declaration,
* but not the definition. In addition, operator<< is not a method of HashTable,
* so do not put HashTable:: before it when defining it. operator<< will allow us
* to print the contents of our hash table using the normal syntax:
 cout <<
* myHashTable << endl;
 You should only print the buckets which are occupied,
* and along with each item you will print which bucket (the index of the bucket)
* the item is in. To make it easy, I suggest creating a helper method called
* something like printMe() that returns a string of everything in the table. An
* example which uses open addressing for collision resolution could print
* something like:
 Bucket 5: <James, 4815>
 Bucket 2: <Juliet, 1623>
 Bucket
* 11: <Hugo, 42108>
*/

ostream& operator<<(ostream& os, const HashTable& hashTable) {
        for (size_t i = 0; i < hashTable.buckets.size(); ++i) {
            if (hashTable.buckets[i].bucketType == HashTableBucket::BucketType::NORMAL) {
                os << "Bucket " << i << ": " << hashTable.buckets[i] << std::endl;
            }
        }
        return os;
    }
// resize the hashtable and offset when aplha is greater than or equal to 0.5
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