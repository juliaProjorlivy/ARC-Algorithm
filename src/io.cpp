#include "io.hpp"
#include "arc.hpp"

#include <iostream>
#include <unordered_map>
#include <limits>

int get_page(int key) {return key;};

//parse input string (cache size; N pages; pages).
int manage_input(std::istream &is, int &hits)
{
    int cache_size = 0;
    int Npages = 0;

    is >> cache_size;
    if(is.eof()) {return 1;}

    cache_t<int, int> cache{cache_size};
    is >> Npages;

    int key_page = 0;
    for(int i_page = 0; i_page < Npages; i_page++)
    {
        is >> key_page;
        try
        {
            hits += cache.lookup_update(key_page, get_page);
        }
        catch (HashListMissmatched &HashList_ex) {std::cout << HashList_ex.what();return 1;}
        catch (EmptyList &EmptyList_ex) {std::cout << EmptyList_ex.what(); return 1;}
    }

    return 0;
}

int manage_input_perfect_cache(std::istream &is)
{
    int cache_size = 0;
    int Npages = 0;

    is >> cache_size;

    is >> Npages;
    std::unordered_map<int, std::vector<int>> map;
    std::vector<int> input;

    int key = 0;
    for(int i_page = 0; i_page < Npages; i_page++)
    {
        is >> key;
        auto found = map.find(key);
        if(found == map.end())
        {
            map.insert(std::make_pair(key, std::vector<int> {i_page}));
        }
        else
        {
            map[key].push_back(i_page);
        }
        input.push_back(key);
    }
    is >> key;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    pcache_t<int, int> pcache(cache_size, map, input);
    return pcache.count_hits(get_page);
}

