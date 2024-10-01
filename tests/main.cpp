#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cstring>
#include <fstream>

#include "io.hpp"

int Ntests = 100;
std::string filename {"data_30_2000.txt"};

TEST(e2e_cache_tests, TEST_RESUTL)
{
    int hits = 0;
    int expected_res = 0;
    std::ifstream file {filename};
    for(int i = 0; i < Ntests; i++)
    {
        if(manage_input(file, hits)){break;};
        file >> expected_res;
        EXPECT_EQ(hits, expected_res) << "Failed " << i + 1 << " line in " << filename;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        hits = 0;
    }
    file.close();
}


int main(int argc, char *argv[])
{
    if (argc < 2) {}
    else if (argc == 3)
    {
        if (!strcmp(argv[1], "-f"))
        {
            filename = argv[2];
        }
        else if (!strcmp(argv[1], "-n"))
        {
            Ntests = std::stoi(argv[2]);
        }
        else {std::cout << "Incorrect arguments\n"; return 1;}
    }
    else if (argc == 5)
    {
        if (!strcmp(argv[1], "-f"))
        {
            filename = argv[2];
            if (strcmp(argv[3], "-n")) {std::cout << "Incorrect arguments\n"; return 1;}
            Ntests = std::atoi(argv[4]);
        }
        else if (!strcmp(argv[1], "-n"))
        {
            Ntests = std::stoi(argv[2]);
            if (strcmp(argv[3], "-f")) {std::cout << "Incorrect arguments\n"; return 1;}
            filename = argv[4];
        }
        else {std::cout << "Incorrect arguments\n"; return 1;}
    }
    else {std::cout << "Incorrect arguments\n"; return 1;}

    // std::ifstream file("./arc_in_py/data.txt");
    // int hits = 0;
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

