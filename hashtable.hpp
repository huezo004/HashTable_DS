template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size):Htable(prime_below(size)){
  currentSize=0;
  Pm=prime_below(size);
}

template <typename K, typename V>
size_t HashTable<K,V>::primeSize(){
   return Pm; 
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K& k){

  std::hash<K>hashIndex;

  return hashIndex(k) % Htable.size();
}

template <typename K, typename V>
HashTable<K,V>::~HashTable(){
   Htable.clear(); 
}

template <typename K, typename V>
size_t HashTable<K,V>::Hsize(){ // for passserver use 
  return currentSize; 
}

template <typename K, typename V>
bool HashTable<K,V>::insert(const std::pair<K,V>&kv){  

  //If pair is already inside
  if(match(kv))
   return false;

  //If pair is not in Htable
  if(!(match(kv))){
 
  Htable[myhash(kv.first)].push_back(kv);

  if(++currentSize > Htable.size())
         rehash(); 
  return true; 
  }

  //Replacement

  if(contains(kv.first)){
 
  auto & whichList = Htable[ myhash( kv.first ) ];  
  
   for(auto  itr = whichList.begin(); itr != whichList.end(); itr++){
       if((itr->first == kv.first) && (itr->second != kv.second)){
              itr->second=kv.second;
       }
   } 
	return true;
    
  }
     
  
}
template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K,V>&&kv){  //endl

  //If in table 
  if(match(kv))
    return false;
  
  //If not in table
   if(!(contains(kv.first))){
   
     Htable[myhash(kv.first)].push_back(std::move(kv));
                                                                                                                        
     if(++currentSize > Htable.size())   
         rehash();                                                                                                                                               
      return true;
   }


  //Replacement

   if(contains(kv.first)){
     auto & whichList = Htable[ myhash( kv.first ) ];

     for(auto  itr = whichList.begin(); itr != whichList.end(); itr++){
       if((itr->first == kv.first) && (itr->second != kv.second)){
	 itr->second= std::move(kv.second);  // update value      
       }
     }                                                                          
    return true;
   }
}

template <typename K, typename V>
bool HashTable<K,V>::match(const std::pair<K,V>&kv)const{
  
  
  for(auto whichList : Htable){
    for(auto itr = whichList.begin(); itr != whichList.end(); ++itr){
      if(*itr==kv)
	return true;
    }
  }
  return false;
}

template <typename K, typename V>
void HashTable<K,V>::rehash(){

  vector<list<pair<K,V>>>oldLists=Htable;

  Htable.resize(prime_below(2*Htable.size()));
	   for(auto & thisList: Htable)
	   thisList.clear();

  currentSize=0;
	    for(auto & thisList: oldLists)
	    for(auto & x : thisList)
	    insert(std::move(x));		
}


template<typename K, typename V>
void HashTable<K,V>::dump(){
  
  for(auto  wl : Htable){
     for(auto itr = wl.begin(); itr != wl.end(); ++itr) {
       cout<<itr->first << " "<< itr->second<<endl;  
         if(wl.size() > 1)
	     cout<< itr->first << " "<< itr->second <<":"<<endl;
    }
  } 
}

template <typename K, typename V>
bool HashTable<K,V>::contains(const K& k){
  auto & wl= Htable[myhash(k)];
  
  if (wl.empty())
    return false;
  for( auto itr=wl.begin(); itr!= wl.end(); ++itr)
             if(itr->first== k) 
	       return true; 
  return false; 
}

template <typename K, typename V>
void HashTable<K,V>::makeEmpty(){
  for(auto & wl: Htable)
         wl.clear();
}

template <typename K, typename V>
void HashTable<K,V>::clear(){
   makeEmpty(); 
}

template <typename K, typename V>
bool HashTable<K,V>::remove(const K& k){

  if (!contains(k))
    return false;
  auto itr = Htable[myhash(k)].end();

  for(auto itrr = Htable[myhash(k)].begin(); itrr!= Htable[myhash(k)].end(); ++itrr) {
    if(itrr->first==k)
      itr= itrr;      
}
  
  if(itr == Htable[myhash(k)].end())
    return false;
  Htable[myhash(k)].erase(itr);
   --currentSize;
  return true;
}


template<typename K, typename V>
bool HashTable<K,V>::write_to_file(const char *filename){
 
 ofstream files;
  files.open(filename);

  if(!files)
    return false;
  for(auto i: Htable){
    for(auto itr = i.begin(); itr!=i.end(); ++itr)
     files <<itr->first<<" "<<itr->second<<endl;
  }
  return true;
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

