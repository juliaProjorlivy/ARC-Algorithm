#include <iostream>
#include <fstream>
#include <limits>

#include "arc.hpp"

int get_page(int key) {return key;};

int manage_input(std::istream &is, int &hits)
{
    int cache_size = 0;
    int Npages = 0;

    is >> cache_size;
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

    int right_ans = 0;
    is >> right_ans;
    std::cout << "hits: " << hits << " correct: " << right_ans << std::endl;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}

int main()
{
    std::ifstream file("./arc_in_py/data.txt");
    int hits = 0;
    for(int i = 0; i < 100; i++)
    {
        if(manage_input(file, hits)) {file.close(); return 1;}
        hits = 0;
    }
    file.close();
    // std::cout << hits << std::endl;
    return 0;
}

