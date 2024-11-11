#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cstring>
#include <fstream>

#include "io.hpp"

int Ntests = 1000;
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
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

