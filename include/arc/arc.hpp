#ifndef ARC_HPP
#define ARC_HPP

#include <list>
#include <unordered_map>
#include <algorithm>

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

    int size() const {return hist.size();};
    bool hit(KeyT key) const {return hashTbl.find(key) != hashTbl.end();};

    KeyT remove(KeyT key)
    {

        auto found = hashTbl.find(key);
        hist.erase(found->second);
        hashTbl.erase(found);
        return key;
    }

    //delete an element from the history; return key of the removed element
    KeyT pop_back()
    {
        KeyT remove_key = hist.back();
        remove(remove_key);
        return remove_key;
    };

    //add new element to the history
    void push_front(KeyT key)
    {
        hist.push_front(key);
        hashTbl.insert(std::make_pair(key, hist.begin()));
    };
};

template<typename PageT, typename KeyT = int>
class cache_t
{
private:
    int size;
    std::list<std::tuple<KeyT, PageT, int>> cache;
    enum {in_mfu = 0, in_lru = 1};

    using ListIt = typename std::list<std::tuple<KeyT, PageT, int>>::iterator;
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
    cache_t(int size_) : size(size_), cache(), hashTbl(), lru_hist(), mfu_hist(), lru_size(0), mfu_size(0), p(0), divider() {};
    ~cache_t() {};

    int get_lru_size() const {return lru_size;};
    int get_mfu_size() const {return mfu_size;};
    int get_p_size() const {return p;};
    bool hit(KeyT key) const {return hashTbl.find(key) != hashTbl.end();}


    std::tuple<KeyT, PageT, int> get_lru_end() const {return cache.front();};
    std::tuple<KeyT, PageT, int> get_mfu_end() const {return cache.back();};

    //pops an element from lru cache and hashTbl; returns the key of popped elelment
    KeyT pop_back_lru()
    {
        KeyT remove_key = std::get<0>(*(cache.begin()));
        auto remove_elem = hashTbl.find(remove_key);

        //returns iterator following the last removed element
        hashTbl.erase(remove_elem);
        cache.pop_front();
        lru_size--;
        return remove_key;
    };

    //pops an element from mfu cache and hashTbl; returns the key of popped elelment
    KeyT pop_back_mfu() 
    {
        if(std::prev(cache.end()) == divider)
        {
            divider = std::next(divider);
        }

        KeyT remove_key = std::get<0>(cache.back());
        auto remove_elem = hashTbl.find(remove_key);

        //returns iterator following the last removed element
        hashTbl.erase(remove_elem);
        cache.pop_back();
        mfu_size--;
        return remove_key;
    };

    //just inserts page in lru cache and hashTbl, change lru_size and returns an interator of inserted elemnt
    ListIt push_front_lru(PageT elem, KeyT key)
    {
        if(cache.empty())
        {
            cache.push_front(std::make_tuple(key, elem, in_lru));
            divider = cache.end();
            hashTbl.insert(std::make_pair(key, cache.begin()));
        }
        else
        {
            cache.insert(divider, std::make_tuple(key, elem, in_lru));
            hashTbl.insert(std::make_pair(key, std::prev(divider)));
        }
        lru_size++;
        return std::prev(divider);
    };

    //just inserts page in mfu cache and hashTbl, change mfu_size and returns an iterator of inserted element
    ListIt push_front_mfu(PageT elem, KeyT key)
    {
        if(cache.empty())
        {
            cache.push_front(std::make_tuple(key, elem, in_mfu));
            divider = cache.begin();
            hashTbl.insert(std::make_pair(key, divider));
        }
        else
        {
            divider = cache.insert(divider, std::make_tuple(key, elem, in_mfu));
            hashTbl.insert(std::make_pair(key, divider));
        }
        mfu_size++;
        return divider;
    };

    //take an element from cache and put it into the beginning of mfu cache, cahnges lru_size and mfu_size, returns an iterator of moved element
    ListIt move_to_mfu(ListIt elem) 
    {
        if(elem == divider) {return divider;}
        cache.splice(divider, cache, elem, std::next(elem));
        divider = std::prev(divider);
        if (std::get<2>(*divider) == in_lru)
        {
            lru_size--; mfu_size++;
            std::get<2>(*divider) = in_mfu;
        }
        return divider;
    };

    //takes an element from cache and puts it into the history (pop from hashTbl and push into history hashTbl)
    void replace(KeyT key)
    {
        if((lru_size >= 1) && ((mfu_hist.hit(key) && lru_size == p) || (lru_size > p)))
        {
            auto lru_page = pop_back_lru();
            lru_hist.push_front(lru_page);
        }
        else
        {
            auto mfu_page = pop_back_mfu();
            mfu_hist.push_front(mfu_page);
        }
    }

    //the main algorithm
    template<typename F>
    bool lookup_update(KeyT key, F slow_get_page)
    {
        auto find_page = hashTbl.find(key);
        if(hashTbl.end() != find_page)
        {
            move_to_mfu(find_page->second);
            return 1;
        }
        else if(lru_hist.hit(key))
        {
            p = std::min(size, p + std::max((int)(mfu_hist.size() / lru_hist.size()), 1));

            replace(key);
            lru_hist.remove(key);
            push_front_mfu(slow_get_page(key), key);
        }
        else if(mfu_hist.hit(key))
        {
            p = std::max(0, p - std::max((int)(lru_hist.size() / mfu_hist.size()), 1));

            replace(key);
            mfu_hist.remove(key);
            push_front_mfu(slow_get_page(key), key);
        }
        else
        {
            int L1_size = lru_hist.size() + lru_size;
            if(L1_size == size)
            {
                if(lru_size < size)
                {
                    lru_hist.pop_back();
                    replace(key);
                }
                else
                {
                    pop_back_lru();
                }
            }
            else if(L1_size + mfu_hist.size() + mfu_size >= size)
            {
                if(L1_size + mfu_hist.size() + mfu_size == 2 * size)
                {
                    mfu_hist.pop_back();
                }
                replace(key);
            }
            push_front_lru(slow_get_page(key), key);
        }
        return 0;
    }
};

#endif
