#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

#include "arc.hpp"


int get_page(int key) {return key;};

struct CacheClassTest : public testing::Test
{
    cache_t<int, int> *cache;
    std::vector<int> key = {1, 2, 1, 3, 4, 5};
    std::vector<int> page = {1, 2, 1, 3, 4, 5};
    // std::vector<std::pair<int, int>> key_page = {{1, 1}, {2, 2}, {1, 1}, {3, 3}, {4, 4}, {5, 5}};

    void SetUp() {cache = new cache_t<int, int>(5);};
    void TearDown() {delete cache;};
};

TEST_F(CacheClassTest, TEST_push_front_lru)
{
    // {1, 1}
    EXPECT_EQ(std::get<0>(*(cache->push_front_lru(page[0], key[0]))), key[0]);
    EXPECT_EQ(cache->get_lru_size(), 1);
    EXPECT_EQ(std::get<0>(cache->lru_end()), 1);
    EXPECT_TRUE(cache->hit(key[0]));

    // {2, 2}
    EXPECT_EQ(std::get<0>(*(cache->push_front_lru(page[1], key[1]))), key[1]);
    EXPECT_EQ(cache->get_lru_size(), 2);
    EXPECT_EQ(std::get<0>(cache->lru_end()), 1);
    EXPECT_TRUE(cache->hit(key[1]));

    // {1, 1}
    EXPECT_EQ(std::get<0>(*(cache->push_front_lru(page[2], key[2]))), key[2]);
    EXPECT_EQ(cache->get_lru_size(), 3);
    EXPECT_EQ(std::get<0>(cache->lru_end()), 1);
    EXPECT_TRUE(cache->hit(key[2]));
    
    // {3, 3}
    EXPECT_EQ(std::get<0>(*(cache->push_front_lru(page[3], key[3]))), key[3]);
    EXPECT_EQ(cache->get_lru_size(), 4);
    EXPECT_EQ(std::get<0>(cache->lru_end()), 1);
    EXPECT_TRUE(cache->hit(key[3]));
}

TEST_F(CacheClassTest, TEST_push_front_mfu)
{
    // {1, 1}
    EXPECT_EQ(std::get<0>(*(cache->push_front_mfu(page[0], key[0]))), key[0]);
    EXPECT_EQ(cache->get_mfu_size(), 1);
    EXPECT_EQ(std::get<0>(cache->mfu_end()), 1);
    EXPECT_TRUE(cache->hit(key[0]));

    // {2, 2}
    EXPECT_EQ(std::get<0>(*(cache->push_front_mfu(page[1], key[1]))), key[1]);
    EXPECT_EQ(cache->get_mfu_size(), 2);
    EXPECT_EQ(std::get<0>(cache->mfu_end()), 1);
    EXPECT_TRUE(cache->hit(key[1]));

    // {1, 1}
    EXPECT_EQ(std::get<0>(*(cache->push_front_mfu(page[2], key[2]))), key[2]);
    EXPECT_EQ(cache->get_mfu_size(), 3);
    EXPECT_EQ(std::get<0>(cache->mfu_end()), 1);
    EXPECT_TRUE(cache->hit(key[2]));
    
    // {3, 3}
    EXPECT_EQ(std::get<0>(*(cache->push_front_mfu(page[3], key[3]))), key[3]);
    EXPECT_EQ(cache->get_mfu_size(), 4);
    EXPECT_EQ(std::get<0>(cache->mfu_end()), 1);
    EXPECT_TRUE(cache->hit(key[3]));
}

TEST_F(CacheClassTest, TEST_move_to_mfu_from_lru)
{
    auto lruIter1 = cache->push_front_lru(page[0], key[0]);
    auto lruIter2 = cache->push_front_lru(page[1], key[1]);
    auto lruIter3 = cache->push_front_lru(page[3], key[3]);
    auto mfuIter1 = cache->push_front_mfu(page[4], key[4]);
    auto mfuIter2 = cache->push_front_mfu(page[5], key[5]);

    EXPECT_EQ(std::get<0>(*(cache->move_to_mfu_from_lru(lruIter1))), 1);
    EXPECT_EQ(std::get<0>(*(cache->move_to_mfu_from_lru(lruIter2))), 2);
    EXPECT_EQ(std::get<0>(*(cache->move_to_mfu_from_lru(lruIter3))), 3);
    EXPECT_EQ(std::get<0>(*(cache->move_to_mfu_from_lru(mfuIter1))), 4);
    EXPECT_EQ(std::get<0>(*(cache->move_to_mfu_from_lru(mfuIter2))), 5);
}

/*TEST_F(CacheClassTest, TEST_lookup_update)
{
    int hits = 0;

    //add {1, 1}
    hits += cache->lookup_update(key_page[0].first, get_page);
    EXPECT_EQ(hits, 0);
    EXPECT_EQ(cache->get_lru_size(), 1);
    EXPECT_EQ(cache->get_mfu_size(), 0);
    EXPECT_EQ(cache->lru_end().first, 1);

    //add {2, 2}
    hits += cache->lookup_update(key_page[1].first, get_page);
    EXPECT_EQ(hits, 0);
    EXPECT_EQ(cache->get_lru_size(), 2);
    EXPECT_EQ(cache->get_mfu_size(), 0);
    EXPECT_EQ(cache->lru_end().first, 1);

    //add {1, 1}
    hits += cache->lookup_update(key_page[2].first, get_page);
    EXPECT_EQ(hits, 1);
    EXPECT_EQ(cache->get_lru_size(), 1);
    EXPECT_EQ(cache->get_mfu_size(), 1);
    EXPECT_EQ(cache->lru_end().first, 2);

    //add {3, 3}
    hits += cache->lookup_update(key_page[3].first, get_page);
    EXPECT_EQ(hits, 1);
    EXPECT_EQ(cache->get_lru_size(), 2);
    EXPECT_EQ(cache->get_mfu_size(), 1);
    EXPECT_EQ(cache->lru_end().first, 2);

    //add {4, 4}
    hits += cache->lookup_update(key_page[4].first, get_page);
    EXPECT_EQ(hits, 1);
    EXPECT_EQ(cache->get_lru_size(), 2);
    EXPECT_EQ(cache->get_mfu_size(), 1);
    EXPECT_EQ(cache->lru_end().first, 3);

    //add {5, 5}
    hits += cache->lookup_update(key_page[5].first, get_page);
    EXPECT_EQ(hits, 1);
    EXPECT_EQ(cache->get_lru_size(), 2);
    EXPECT_EQ(cache->get_mfu_size(), 1);
    EXPECT_EQ(cache->lru_end().first, 4);
    // for(auto kp : key_page)
    // {
    //
    //     hits += cache->lookup_update(kp.first, get_page);
    // }
    // EXPECT_EQ(hits, 1);
}*/


