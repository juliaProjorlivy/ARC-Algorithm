#include "arc.hpp"

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
