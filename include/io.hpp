#ifndef IO_HPP
#define IO_HPP

#include <istream>

int manage_input(std::istream &is, int &hits);

int get_page(int key);

int manage_input_perfect_cache(std::istream &is);

#endif

