#include "arc.hpp"
#include <vector>

int get_page(int key)
{
    return key;
}

int main()
{
    std::vector<int> page_keys = {1, 2, 1, 3, 4, 5};
    std::vector<int> pages = {1, 2, 1, 3, 4, 5};

    cache_t<int, int> cache(5);
    for(int i = 0; i < pages.size(); i++)
    {
        // cache.lookup_update<int (int)>(page_keys[i], get_page);
        cache.lookup_update(page_keys[i], get_page);

    }




    return 0;
}


