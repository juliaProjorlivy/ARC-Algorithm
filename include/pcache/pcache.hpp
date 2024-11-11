#ifndef PERFECT_CACHE_HPP
#define PERFECT_CACHE_HPP

#include <list>
#include <unordered_map>
#include <vector>
#include <iostream>

int manage_input_perfect_cache(std::istream &is);

//perfect cache for comparison
template<typename PageT, typename KeyT = int>
class pcache_t
{
private:
    int size;
    std::list<std::pair<KeyT, PageT>> cache;

    using ListIt = typename std::list<std::pair<KeyT, PageT>>::iterator;
    std::unordered_map<KeyT, ListIt> hashTbl;

    // key -> i-place in input
    std::unordered_map<KeyT, std::vector<int>> inputTbl;
    std::vector<KeyT> input;

public:
    pcache_t(int size_, std::unordered_map<KeyT, std::vector<int>> inputTbl_, std::vector<int> input_): size(size_), cache(), hashTbl(), inputTbl(inputTbl_), input(input_) {};
    ~pcache_t() {};

    bool hit(KeyT key) const {return hashTbl.find(key) != hashTbl.end();};

    KeyT find_latest()
    {
        int latest_It = -1;
        KeyT latest_key;
        for(auto elem : cache)
        {
            //if it was not found in the input -> it won't show no more
            auto found = inputTbl.find(elem.first);
            if(found == inputTbl.end())
            {
                return elem.first;
            }

            if(latest_It <= found->second[0])
            {
                latest_It = found->second[0];
                latest_key = found->first;
            }
        }
        return latest_key;
    }

    void remove_from_inputTbl(KeyT key)
    {
        if (inputTbl.find(key) == inputTbl.end()) {return;}
        if(inputTbl[key].size() == 1) {inputTbl.erase(inputTbl.find(key));}
        else {inputTbl[key].erase(inputTbl[key].begin());}
    }

    void pop_latest()
    {
        KeyT latest_key = find_latest();

        cache.erase(hashTbl[latest_key]);
        hashTbl.erase(hashTbl.find(latest_key));
    }

    void push_back(KeyT key, PageT page)
    {
        remove_from_inputTbl(key);
        cache.push_back(std::make_pair(key, page));
        hashTbl.insert(std::make_pair(key, std::prev(cache.end())));
    }

    template<typename F>
    bool lookup_update(KeyT key, F slow_get_page)
    {
        auto find_page = hashTbl.find(key);
        if(hashTbl.end() != find_page)
        {
            remove_from_inputTbl(key);
            return 1;
        }
        else if(cache.size() == size)
        {
            pop_latest();
            push_back(key, slow_get_page(key));
        }
        else
        {
            push_back(key, slow_get_page(key));
        }
        return 0;
    }

    template<typename F>
    int count_hits( F slow_get_page)
    {
        int hits = 0;
        int Nelems = input.size();
        for(int i = 0; i < Nelems; i++)
        {
            KeyT next_key = input[0];
            input.erase(input.begin());

            hits += lookup_update(next_key, slow_get_page);
        }
        return hits;
    }
};

#endif

