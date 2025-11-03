//
// Created by nitin on 10/23/2025.
//

#include "HashTableBucket.h"
using namespace std;
// default constructor if key and value is not given
HashTableBucket::HashTableBucket() {
    key = "";
    value = 0;
    bucketType = BucketType::ESS;
}
// default constructor if key and value is given
HashTableBucket::HashTableBucket(string key, int value) {
    load(key, value);
}
// this function is used to load key and value into bucket and set bucketType to NORMAL
void HashTableBucket::load(string key, int value) {
    this->key = key;
    this->value = value;
    bucketType = BucketType::NORMAL;
}
// to check if the bucket is empty or not and returns true or false
bool HashTableBucket::isEmpty() const {
    if (bucketType == BucketType::NORMAL) {
        return false;
    }
    return true;
}
 /**
* The stream insertion operator could be overloaded to print the
* bucket's contents. Or if preferred, you could write a print method
* instead.
*/
std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    if (bucket.bucketType == HashTableBucket::BucketType::NORMAL) {
        os << "<" << bucket.key << ", " << bucket.value << ">";
    }
    return os;
}


