#include "arc.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct HistoryClassTest1 : public testing::Test
{
    history_t<int> *history; 
    int key = 1;

    void SetUp() {history = new history_t<int>(); history->push_front(key);};
    void TearDown() {delete history;};
};


TEST_F(HistoryClassTest1, TEST_size)
{
    EXPECT_EQ(history->size(), 1);

    history->push_front(5);
    EXPECT_EQ(history->size(), 2);
}

TEST_F(HistoryClassTest1, TEST_hit)
{
    history->push_front(5);
    history->push_front(6);

    EXPECT_TRUE(history->hit(5));
    EXPECT_TRUE(history->hit(6));
    EXPECT_FALSE(history->hit(8));
    EXPECT_FALSE(history->hit(0));
}
int get_page(int key)
{
    return key;
}

int main(int argc, char **argv)
{
    // std::vector<int> page_keys = {1, 2, 1, 3, 4, 5};
    // std::vector<int> pages = {1, 2, 1, 3, 4, 5};
    //
    // typedef int (*func_t)(int);
    //
    // cache_t<int, func_t, int> cache{5};
    // for(int i = 0; i < pages.size(); i++)
    // {
    //     // cache.lookup_update<int (int)>(page_keys[i], get_page);
    //     cache.lookup_update(page_keys[i], get_page);
    //
    // }

    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

    return 0;
}
