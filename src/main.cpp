#include "arc.hpp"
#include <vector>
#include <iostream>

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

// int main(int argc, char **argv)
// {
//     std::vector<int> page_keys = {1, 2, 1, 3, 4, 5};
//     std::vector<int> pages = {1, 2, 1, 3, 4, 5};
//
//     int hits = 0;
//
//     typedef int (*func_t)(int);
//
//     cache_t<int, int> cache{3};
//     for(int i = 0; i < pages.size(); i++)
//     {
//         hits += cache.lookup_update(page_keys[i], get_page);
//
//     }
//
//     return 0;
// }
