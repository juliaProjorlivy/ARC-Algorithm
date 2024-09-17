#include "arc.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct HistoryClassTest1 : public testing::Test
{
    history_t<int> *history; 

    void SetUp() {history = new history_t<int>();};
    void TearDown() {delete history;};
};


TEST_F(HistoryClassTest1, TEST_size)
{
    history->push_front(1);
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

TEST_F(HistoryClassTest1, TEST_pop_back)
{
    history->push_front(5);
    history->push_front(6);
    history->push_front(30);

    history->pop_back();
    EXPECT_FALSE(history->hit(5));

    history->pop_back();
    EXPECT_FALSE(history->hit(6));

    history->pop_back();
    EXPECT_FALSE(history->hit(30));

    history->pop_back();
    EXPECT_FALSE(history->hit(30));
}




