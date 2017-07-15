#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<list>
#include<vector> 
#include<iostream>
#include<string>
#include<utility>
#include<algorithm>
#include <fstream>

using namespace std;

namespace cop4530{ 
template <typename K, typename V>
class HashTable{
  public:
  explicit HashTable(size_t size = 101); 
  ~HashTable(); 
  bool contains(const K & k); 
  bool match(const std::pair<K,V>&kv) const; 
  bool insert(const std::pair<K,V>&kv); 
  bool insert(std::pair<K,V>&& kv); 
  bool remove(const K & k); 
  void clear(); 
  bool load(const char *filename); 
  void dump(); 
  bool write_to_file(const char *filename);
  size_t Hsize();
  size_t primeSize(); 
  unsigned long prime_below (unsigned long); 
    void setPrimes(vector<unsigned long>&); 
 private:
  vector<list<pair<K,V>>> Htable;
  size_t Pm;
  size_t currentSize;
  void makeEmpty(); 
  void rehash(); 
  size_t myhash(const K &k); 

static const unsigned int max_prime = 1301081;
static const unsigned int default_capacity = 11;

};
#include "hashtable.hpp"
}
#endif


