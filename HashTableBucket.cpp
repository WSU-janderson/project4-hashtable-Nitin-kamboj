//
// Created by nitin on 10/23/2025.
//

#include "HashTableBucket.h"
using namespace std;
HashTableBucket::HashTableBucket() {
    key = "";
    value = 0;
    bucketType = BucketType::ESS;
}
HashTableBucket::HashTableBucket(string key, int value) {
    load(key, value);
}
void HashTableBucket::load(string key, int value) {
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
std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    if (bucket.bucketType == HashTableBucket::BucketType::NORMAL) {
        os << "<" << bucket.key << ", " << bucket.value << ">";
    }
    return os;
}


