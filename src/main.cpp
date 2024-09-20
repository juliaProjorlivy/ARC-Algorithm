#include "arc.hpp"
#include <vector>

int get_page(int key) {return key;};

int main(int argc, char **argv)
{
    std::vector<int> page_keys = {1, 2, 1, 3, 4, 5};
    std::vector<int> pages = {1, 2, 1, 3, 4, 5};

    int hits = 0;

    typedef int (*func_t)(int);

    cache_t<int, int> cache{3};
    for(int i = 0; i < pages.size(); i++)
    {
        hits += cache.lookup_update(page_keys[i], get_page);

    }

    return 0;
}
