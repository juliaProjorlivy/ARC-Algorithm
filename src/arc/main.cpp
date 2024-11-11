#include "io.hpp"
#include <iostream>

int main()
{
    int hits = 0;
    if(manage_input(std::cin, hits)) {return 1;}
    std::cout << hits << std::endl;
    return 0;
}

