#include "io.hpp"
#include <fstream>
#include <iostream>
#include <limits>

int main()
{
    // std::ifstream file("./arc_in_py/data.txt");
    // int hits = 0;
    // int expected_res = 0;
    // for(int i = 0; i < 100; i++)
    // {
    //     if(manage_input(file, hits)) {file.close(); return 1;}
    //     std::cout << hits << std::endl;
    //     file >> expected_res;
    //     file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //     hits = 0;
    // }
    // file.close();
    //
    int hits = 0;
    if(manage_input(std::cin, hits)) {return 1;}
    std::cout << hits << std::endl;
    return 0;
}

