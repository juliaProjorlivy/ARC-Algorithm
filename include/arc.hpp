#ifndef ARC_HPP
#define ARC_HPP

#include <list>
#include <unordered_map>

template<typename KeyT = int>
class history_t
{
private:
    std::list<KeyT> hist;

    using ListIt = typename std::list<KeyT>::iterator;
    std::unordered_map<KeyT, ListIt> hashTbl;

public:
    history_t(): hist(), hashTbl() {};
    ~history_t() {};

    //delete an element from the history
    void pop_back() {auto popped = hist.pop_back(); hashTbl.erase(popped);};

    //add new element to the history
    void push_front(KeyT key) {auto inserted = hist.push_front(key); hashTbl.insert({key, inserted});};

    //get number of elements in history
    std::size_t size() {return hist.size();};

    //check if an element was found in history
    bool hit(KeyT key) {return hashTbl.find(key) != hashTbl.end();};
};

template<typename PageT, typename KeyT = int>
class cache_t
{
private:
    std::size_t size;
    std::list<PageT> cache;

    using ListIt = typename std::list<PageT>::iterator;
    std::unordered_map<KeyT, ListIt> hashTbl;

    //last recently used pages history
    history_t<KeyT> lru_hist;
    //most frequently used pages history
    history_t<KeyT> mfu_hist;

    //size of lru part in cache
    int lru_size;
    //size of mfu part in cache
    int mfu_size;
    //pointer-divider
    int p;

    //points to the first element in T2
    ListIt divider;
public:
    cache_t(std::size_t _size) : size(_size), cache(), hashTbl(), divider(cache.begin()), lru_size(0), mfu_size(0), lru_hist(), mfu_hist() {};
    ~cache_t() {};

    //pop an element from lru cache and hashTbl; returns the key of popped elelment
    KeyT pop_back_lru() {ListIt popped = cache.pop_front(); lru_size--; return (hashTbl.erase(popped))->first;};

    //pop an element from mfu cache and hashTbl; returns the key of popped elelment
    KeyT pop_back_mfu() {ListIt popped = cache.pop_back(); mfu_size--; return (hashTbl.erase(popped))->first;};

    //just inserts page in lru cache and hashTbl
    void push_front_lru(PageT elem, KeyT key)
    {cache.insert(divider, elem);  hashTbl.insert({key, divider}); lru_size++;};

    //just inserts page in mfu cache and hashTbl
    void push_front_mfu(PageT elem, KeyT key)
    {divider = cache.insert(++divider, elem);  hashTbl.insert({key, divider}); mfu_size++;};

    //take an element from cache and put it into the beginning of mfu cache
    void move_to_mfu_from_lru(ListIt elem) {divider = cache.insert(++divider, cache.erase(elem)); lru_size--; mfu_size++;};

    //takes an element from cache and puts it into the history (pop from hashTbl and push into history hashTbl)
    void replace(KeyT key);

    //the main algorithm
    template<typename F>
    void lookup_update(KeyT key, F slow_get_page);
};

#endif

