#include "pcache.hpp"
#include <fstream>
#include <iostream>
#include <limits>

int get_page(int key) {return key;};

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

int main()
{
    std::ifstream file_r {"./tests/data_30_2000.txt"};
    std::ofstream file_w {"pcache_res.txt"};
    int p_hits = 0;
    for (int i = 0; i < 100; i++)
    {
        p_hits = manage_input_perfect_cache(file_r);
        file_w << p_hits << std::endl;
    }
    file_r.close();
    file_w.close();
    return 0;
}

