#include <iostream>

#include "arc.hpp"

int get_page(int key) {return key;};

int main()
{
    int cache_size = 0;
    int Npages = 0;

    std::cin >> cache_size;
    cache_t<int, int> cache{cache_size};
    std::cin >> Npages;

    int key_page = 0;
    int hits = 0;
    for(int i = 0; i < Npages; i++)
    {
        std::cin >> key_page;
        try
        {
            hits += cache.lookup_update(key_page, get_page);
        }
        catch (HashListMissmatched &HashList_ex) {std::cout << HashList_ex.what();return 1;}
        catch (EmptyList &EmptyList_ex) {std::cout << EmptyList_ex.what(); return 1;}
    }

    std::cout << hits << std::endl;
    return 0;
}

