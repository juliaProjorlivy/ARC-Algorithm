#include "pcache.hpp"
#include <iostream>
#include <istream>

int get_page(int key) {return key;};

int manage_input_perfect_cache()
{
    int cache_size = 0;
    int Npages = 0;

    std::cin >> cache_size;

    std::cin >> Npages;
    std::unordered_map<int, std::vector<int>> map;
    std::vector<int> input;

    int key = 0;
    for(int i_page = 0; i_page < Npages; ++i_page)
    {
        std::cin >> key;
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
    pcache_t<int, int> pcache(cache_size, map, input);
    return pcache.count_hits(get_page);
}

int main()
{
    int p_hits = 0;

    p_hits = manage_input_perfect_cache();
    std::cout << p_hits << std::endl;

    return 0;
}

