#include "arc.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct HistoryClassTestInt : public testing::Test
{
    history_t<int> *history; 

    void SetUp() {history = new history_t<int>();};
    void TearDown() {delete history;};
};


TEST_F(HistoryClassTestInt, TEST_size)
{
    history->push_front(1);
    EXPECT_EQ(history->size(), 1);

    history->push_front(5);
    EXPECT_EQ(history->size(), 2);
}

TEST_F(HistoryClassTestInt, TEST_hit)
{
    history->push_front(5);
    history->push_front(6);

    EXPECT_TRUE(history->hit(5));
    EXPECT_TRUE(history->hit(6));
    EXPECT_FALSE(history->hit(8));
    EXPECT_FALSE(history->hit(0));
}

TEST_F(HistoryClassTestInt, TEST_pop_back)
{
    history->push_front(1);
    history->push_front(2);
    history->push_front(3);

    for (int i = 0; i < 3; i++)
    {
        history->pop_back();
        try {history->pop_back();}
        catch (EmptyList& empty_list_ex) {std::cout << empty_list_ex.what(); break;}
        catch (HashListMissmatched& hash_list_ex) {std::cout << hash_list_ex.what(); break;}
        EXPECT_FALSE(history->hit(i + 1));
    }
}

