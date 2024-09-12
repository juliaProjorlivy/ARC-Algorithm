#ifndef ARC_HPP
#define ARC_HPP

#include <cstddef>
#include <list>
#include <unordered_map>

template<typename DataT, typename KeyT = int>
class base_t
{
private:
    std::size_t size;
    std::list<DataT> data;

    using ListIt = typename std::list<DataT>::iterator;
    std::unordered_map<KeyT, ListIt> hashTbl;

    ListIt divider;
    ListIt ptr;
public:
    base_t(std::size_t _size) : size(_size), divider(0), ptr(0), data(), hashTbl() {};
    virtual ~base_t() {};

    virtual ListIt pop_back_lru() {ListIt popped = data.pop_front(); hashTbl.erase(popped); return popped;};
    virtual ListIt pop_back_mru() {ListIt popped = data.pop_back();  hashTbl.erase(popped); return popped;};
    virtual void push_front_lru(DataT elem, KeyT key)
    {data.insert(divider, elem);  hashTbl.insert({key, elem});};
    virtual void push_front_mru(DataT elem, KeyT key)
    {data.insert(divider + 1, elem);  hashTbl.insert({key, elem});};

};


template<typename KeyT = int>
class history_t
{
private:
    std::size_t size;
    std::list<KeyT> history;

    using ListIt = typename std::list<KeyT>::iterator;
    std::unordered_map<KeyT, ListIt> hashTbl;

public:
    history_t(std::size_t _size) : size(_size), history(), hashTbl() {};
    ~history_t();

    size_t length() {return history.length();};
    ListIt find(KeyT key) {return history.find(key);};

    void push_front(KeyT key) {hashTbl.insert(key); history.push_front(key);};

    void pop_back(KeyT key) {hashTbl.erase(key); history.pop_back(key);};

    void add(KeyT key);
};

template<typename PageT, typename KeyT = int>
class cache_t
{
private:
    std::size_t size;
    std::list<PageT> cache;
    std::size_t DataT_size;
    std::size_t ptr;
    using ListIt = typename std::list<PageT>::iterator;
    std::unordered_map<KeyT, ListIt> hashTbl;

    history_t<KeyT> B1;
    history_t<KeyT> B2;

public:
    cache_t(std::size_t _size) : size(_size), ptr(0), cache(), hashTbl(), B1(_size), B2(_size) {};
    ~cache_t();


    std::size_t get_DataTsize() {return DataT_size;};
    std::size_t get_KeyTsize() {return cache.size() - DataT_size;};

    bool is_B1(KeyT key) {return B1.find(key) != B1.end();};
    bool is_B2(KeyT key) {return B2.find(key) != B2.end();};


    void change_ptr(KeyT key);

    template<typename F>
    bool lookup_update(KeyT key,  F slow_get_page);
};


#endif

