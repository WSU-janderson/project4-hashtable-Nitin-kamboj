[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

---
Time Complexity Analysis

The insert method has an average time complexity of O(1) because it typically takes a constant number of probes to find an empty bucket after computing the hash value. However, in the worst case, if many collisions occur or the table is nearly full, the method may require checking every bucket, making it O(n) in the worst case.

The remove method runs in O(1) on average since locating and marking a bucket as deleted usually takes constant time with pseudo-random probing. In the worst case, it can become O(n) if a long sequence of probes is required to find the key.

The contains method also operates in O(1) average time because it only needs to compute the hash and probe a few locations to determine if the key exists. The worst case is O(n) when many collisions cause it to probe most of the table.

The get method has an average time complexity of O(1), as it performs the same hash and probing operations as contains to find a key. In the worst case, it may need to scan the entire table, giving it O(n) complexity.

The operator[] method has the same time complexity as get, which is O(1) on average and O(n) in the worst case, because it uses hashing and probing to find and return a reference to the associated value.

The keys method has a time complexity of O(n) because it must iterate through every bucket in the hash table to collect all stored keys.

The alpha method runs in O(1) time since it only computes the ratio of size to capacity, which are both stored values that can be accessed directly.

The capacity method has O(1) time complexity because it simply returns the current total number of buckets.

The size method also runs in O(1) time, as it directly returns the stored count of active key-value pairs.

Finally, the rehashBackwards method has a time complexity of O(n) because it must visit and reinsert all existing key-value pairs in reverse order when resizing the table.
