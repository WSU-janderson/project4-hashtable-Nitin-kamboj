//
// Created by nitin on 10/23/2025.
//

#include "HashTableBucket.h"

HashTableBucket::HashTableBucket() {
    this->key;
    this->value;
    bucketType = BucketType::ESS;
}
HashTableBucket::HashTableBucket(string key, size_t value) {
    this->key = key;
    this->value = value;
    bucketType = BucketType::NORMAL;
}
void HashTableBucket::load(string key, size_t value) {
    this->key = key;
    this->value = value;
    bucketType = BucketType::NORMAL;
}
bool HashTableBucket::isEmpty() const {
    if (bucketType == BucketType::NORMAL) {
        return false;
    }
    return true;
}


