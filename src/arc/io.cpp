#include "io.hpp"
#include "arc.hpp"

#include <iostream>

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
        hits += cache.lookup_update(key_page, get_page);
    }

    return 0;
}

