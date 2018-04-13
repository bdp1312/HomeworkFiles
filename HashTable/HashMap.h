#ifndef HashMap_H
#define HashMap_H

#include<vector>
using std::vector;
//using std::cout;
//using std::endl;
using std::pair;

template<typename K,typename V,typename Hash>
class HashMap {
    Hash hashFunction;
    // Data to store the hash table and the number of elements.
    int tableSize; //total number of slots in hash table
    int dataload;//number of taken positions in hash table
    double loadFactor(int tableSize, int dataload)//calculates load Factor of hashtable
    {
      double lf = dataload/tableSize;
      //cout<<"loadFactor = "<<lf<<endl;
      return lf;
    }
    vector<vector<pair<K,V>>> table;

    // Suggestion for the hash table: either
    //vector<vector<pair<K,V>>> table;
    // or
    // vector<list<pair<K,V>>> table;
    // would work well for the chaining approach.

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // NOTE: These might be different depending on how you store your table.
        typename std::remove_reference<decltype(table.begin())>::type mainIter;
        typename std::remove_reference<decltype(table.begin())>::type mainEnd;
        typename std::remove_reference<decltype(table[0].begin())>::type subIter;
    public:
        friend class const_iterator;
        friend class HashMap;

        // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,const decltype(mainEnd) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,
                const decltype(mainEnd) me,
                const decltype(subIter) si):
                mainIter(mi),mainEnd(me),subIter(si) {}

        bool operator==(const iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return *subIter; }
        iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    class const_iterator {
      friend class HashMap;
        // NOTE: These might be different depending on how you store your table.
        typename std::remove_reference<decltype(table.cbegin())>::type mainIter;
        typename std::remove_reference<decltype(table.cbegin())>::type mainEnd;
        typename std::remove_reference<decltype(table[0].cbegin())>::type subIter;
    public:
        // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.cbegin()) mi,const decltype(table.cbegin()) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.cbegin()) mi,
            const decltype(table.cbegin()) me,
            const decltype(table[0].cbegin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}
        const_iterator(const decltype(table.begin()) mi,
            const decltype(table.begin()) me,
            const decltype(table[0].begin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}

        // NOTE: These might be different depending on how you store your table.
        const_iterator(const iterator &i):mainIter(i.mainIter),mainEnd(i.mainEnd),subIter(i.subIter){}

        bool operator==(const const_iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> &operator*() const { return *subIter; }
        const_iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    HashMap(const Hash &hf) :hashFunction{ hf }
    {
      table.resize(1000000);

      dataload = 0;
    }
    // HashMap(const HashMap<K,V,Hash> &that); // Only if needed.

    // HashMap &operator=(const HashMap<K,V,Hash> &that); // Only if needed.

    bool empty() const{return dataload==0;}

    unsigned int size() const
    {
      unsigned int theSize = dataload;
      return theSize;
    }

    iterator find(const key_type& k)
    {
      int index = hashFunction(k)%table.size();

      for(auto itr = table[index].begin(); itr!=table[index].end(); ++itr){
        if (k == itr->first){
          return iterator(table.begin()+index, table.end(), itr);
        }
      }
      return end();
    }

    const_iterator find(const key_type& k) const  {
        int index = hashFunction(k)%table.size();
        for(auto itr = table[index].cbegin(); itr!=table[index].cend(); ++itr){
          if (k == itr->first){
            return const_iterator(table.cbegin()+index, table.cend(), itr);
          }
        }
      }
      return cend();
    }

    int count(const key_type& k) const{
      auto val = find(k);
      if(val != end()){
        return 1;
      }else{
        return 0;
      }
    }

    std::pair<iterator,bool> insert(const value_type& val){//insert one element
      iterator iter = find(val.first);
      if(iter == end()){
        int index = hashFunction(val.first)%table.size();
        table[index].push_back(val);
        iterator newiter(table.begin()+index, table.end(), --table[index].end());
        ++dataload;
        return make_pair(newiter, true);
      }else{
        return make_pair(iter, false);
      }
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last)//insert a range of data
    {
      for(auto i = first; i !=last; ++i){
        insert(*i);
      }
    //   auto key =find(*(first));
    //   if( key== table.end()){
    //     K bin = hashFunction(*first)%table.size();
    //     (table[key]).push_back(*last)
    //
    //     ++tableSize;
    // } else{
    //   return()
    }

    iterator erase(const_iterator position)//return iterator after the deleted one
    {
      auto index = position.mainIter-table.begin();
      auto pos = table[index].erase(position.subIter);

      --dataload;//fix variable name
      return iterator(table.begin()+index, table.end(), pos);
    }

    int erase(const key_type& k)
    {
      const_iterator iter = find(k);
      if(iter = cend()){return 0;}
      erase(iter);
      return 1;
    }

    void clear()
    {
      for(auto i = table.begin(); i != table.end(); ++i){
        i->clear();
        dataload = 0;
      }
    }

    mapped_type &operator[](const K &key)
    {
      return (*insert(make_pair(key, V())).first).second;
    }

    bool operator==(const HashMap<K,V,Hash>& rhs) const{
      for(auto asdf = begin(); asdf != end(); ++asdf){
        if(rhs.find((*asdf).first) == rhs.end()){
          return false;
        }
      }
      if (size()==rhs.size()){return true;}
      else{return false;}
    }

    bool operator!=(const HashMap<K,V,Hash>& rhs) const {return !(*this==rhs);}

    // NOTE: These might be different depending on how you store your table
    iterator begin() {
        return iterator(table.begin(),table.end());
    }

    const_iterator begin() const{
        return const_iterator(table.begin(),table.end());
    }

    iterator end(){
        return iterator(table.end(),table.end());
    }

    const_iterator end() const{
        return const_iterator(table.end(),table.end());
    }

    const_iterator cbegin() const{
        return const_iterator(table.begin(),table.end());
    }

    const_iterator cend() const{
        return const_iterator(table.end(),table.end());
    }

private:
    void growTableAndRehash();
};
#endif
