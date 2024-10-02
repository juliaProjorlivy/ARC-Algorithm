#include "io.hpp"
#include <fstream>
#include <iostream>

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
