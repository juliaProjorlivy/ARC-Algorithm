#include "arc.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct HistoryClassTest : public testing::Test
{
    history_t<int> *history; 

    void SetUp() {history = new history_t<int>();};
    void TearDown() {delete history;};
};

TEST_F(HistoryClassTest, TEST_pop_back)
{
    history->push_front(1);
    history->push_front(2);
    history->push_front(3);

    for (int i = 0; i < 3; i++)
    {
        history->pop_back();
        EXPECT_FALSE(history->hit(i + 1));
    }
}

