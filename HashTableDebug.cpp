/**
 * HashTableDebug.cpp
 *
 * Write your tests in this file
 */
#include <iostream>

#include "HashTable.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    HashTable hashTable;
    hashTable.insert("Nitin", 123);
    cout<<hashTable.contains("Nitin") << endl;
    cout<<hashTable.contains("n") << endl;
    cout<<hashTable.size() << endl;
    cout<<hashTable.buckets.size() << endl;
    cout  << hashTable;
    cout << hashTable.buckets.at(2) << endl;
    return 0;
}
