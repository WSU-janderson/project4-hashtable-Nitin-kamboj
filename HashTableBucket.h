//
// Created by nitin on 10/23/2025.
//

#ifndef HASHTABLE_HASHTABLEBUCKET_H
#define HASHTABLE_HASHTABLEBUCKET_H
#include <iostream>
using namespace std;

class HashTableBucket {

public:
    enum class BucketType {NORMAL, ESS, EAR};
    string key;
    int value;
    BucketType bucketType;
    HashTableBucket();
    HashTableBucket(string key, int value);
    void load(string key, int value);
    bool isEmpty() const;
    friend ostream& operator<<(ostream& os, const HashTableBucket& bucket);
};


#endif //HASHTABLE_HASHTABLEBUCKET_H