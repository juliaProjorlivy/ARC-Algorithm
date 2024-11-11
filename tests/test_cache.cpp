#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

#include "arc.hpp"
#include "io.hpp"

struct CacheClassTestInt : public testing::Test
{
    cache_t<int, int> *cache;
    std::vector<int> key = {1, 2, 1, 3, 4, 5};
    std::vector<int> page = {1, 2, 1, 3, 4, 5};

    void SetUp() {cache = new cache_t<int, int>(3);};
    void TearDown() {delete cache;};
};

TEST_F(CacheClassTestInt, TEST_push_front_lru)
{
    // {1, 1}
    EXPECT_EQ(std::get<0>(*(cache->push_front_lru(page[0], key[0]))), key[0]);
    EXPECT_EQ(cache->get_lru_size(), 1);
    EXPECT_EQ(std::get<0>(cache->get_lru_end()), 1);
    EXPECT_TRUE(cache->hit(key[0]));

    // {2, 2}
    EXPECT_EQ(std::get<0>(*(cache->push_front_lru(page[1], key[1]))), key[1]);
    EXPECT_EQ(cache->get_lru_size(), 2);
    EXPECT_EQ(std::get<0>(cache->get_lru_end()), 1);
    EXPECT_TRUE(cache->hit(key[1]));

    // {1, 1}
    EXPECT_EQ(std::get<0>(*(cache->push_front_lru(page[2], key[2]))), key[2]);
    EXPECT_EQ(cache->get_lru_size(), 3);
    EXPECT_EQ(std::get<0>(cache->get_lru_end()), 1);
    EXPECT_TRUE(cache->hit(key[2]));
    
    // {3, 3}
    EXPECT_EQ(std::get<0>(*(cache->push_front_lru(page[3], key[3]))), key[3]);
    EXPECT_EQ(cache->get_lru_size(), 4);
    EXPECT_EQ(std::get<0>(cache->get_lru_end()), 1);
    EXPECT_TRUE(cache->hit(key[3]));
}

TEST_F(CacheClassTestInt, TEST_push_front_mfu)
{
    // {1, 1}
    EXPECT_EQ(std::get<0>(*(cache->push_front_mfu(page[0], key[0]))), key[0]);
    EXPECT_EQ(cache->get_mfu_size(), 1);
    EXPECT_EQ(std::get<0>(cache->get_mfu_end()), 1);
    EXPECT_TRUE(cache->hit(key[0]));

    // {2, 2}
    EXPECT_EQ(std::get<0>(*(cache->push_front_mfu(page[1], key[1]))), key[1]);
    EXPECT_EQ(cache->get_mfu_size(), 2);
    EXPECT_EQ(std::get<0>(cache->get_mfu_end()), 1);
    EXPECT_TRUE(cache->hit(key[1]));

    // {1, 1}
    EXPECT_EQ(std::get<0>(*(cache->push_front_mfu(page[2], key[2]))), key[2]);
    EXPECT_EQ(cache->get_mfu_size(), 3);
    EXPECT_EQ(std::get<0>(cache->get_mfu_end()), 1);
    EXPECT_TRUE(cache->hit(key[2]));
    
    // {3, 3}
    EXPECT_EQ(std::get<0>(*(cache->push_front_mfu(page[3], key[3]))), key[3]);
    EXPECT_EQ(cache->get_mfu_size(), 4);
    EXPECT_EQ(std::get<0>(cache->get_mfu_end()), 1);
    EXPECT_TRUE(cache->hit(key[3]));
}

TEST_F(CacheClassTestInt, TEST_move_to_mfu)
{
    auto lruIter1 = cache->push_front_lru(page[0], key[0]);
    auto lruIter2 = cache->push_front_lru(page[1], key[1]);
    auto lruIter3 = cache->push_front_lru(page[3], key[3]);
    auto mfuIter1 = cache->push_front_mfu(page[4], key[4]);
    auto mfuIter2 = cache->push_front_mfu(page[5], key[5]);

    EXPECT_EQ(std::get<0>(*(cache->move_to_mfu(lruIter1))), 1);
    EXPECT_EQ(std::get<0>(*(cache->move_to_mfu(lruIter2))), 2);
    EXPECT_EQ(std::get<0>(*(cache->move_to_mfu(lruIter3))), 3);
}

TEST_F(CacheClassTestInt, TEST_lookup_update)
{
    int hits = 0;

    //add {1, 1}
    hits += cache->lookup_update(key[0], get_page);
    EXPECT_EQ(hits, 0);
    EXPECT_EQ(cache->get_lru_size(), 1);
    EXPECT_EQ(cache->get_mfu_size(), 0);
    EXPECT_EQ(std::get<0>(cache->get_lru_end()), 1);

    //add {2, 2}
    hits += cache->lookup_update(key[1], get_page);
    EXPECT_EQ(hits, 0);
    EXPECT_EQ(cache->get_lru_size(), 2);
    EXPECT_EQ(cache->get_mfu_size(), 0);
    EXPECT_EQ(std::get<0>(cache->get_lru_end()), 1);

    //add {1, 1}
    hits += cache->lookup_update(key[2], get_page);
    EXPECT_EQ(hits, 1);
    EXPECT_EQ(cache->get_lru_size(), 1);
    EXPECT_EQ(cache->get_mfu_size(), 1);
    EXPECT_EQ(std::get<0>(cache->get_lru_end()), 2);

    //add {3, 3}
    hits += cache->lookup_update(key[3], get_page);
    EXPECT_EQ(hits, 1);
    EXPECT_EQ(cache->get_lru_size(), 2);
    EXPECT_EQ(cache->get_mfu_size(), 1);
    EXPECT_EQ(std::get<0>(cache->get_lru_end()), 2);

    //add {4, 4}
    hits += cache->lookup_update(key[4], get_page);
    EXPECT_EQ(hits, 1);
    EXPECT_EQ(cache->get_lru_size(), 2);
    EXPECT_EQ(cache->get_mfu_size(), 1);
    EXPECT_EQ(std::get<0>(cache->get_lru_end()), 3);

    //add {5, 5}
    hits += cache->lookup_update(key[5], get_page);
    EXPECT_EQ(hits, 1);
    EXPECT_EQ(cache->get_lru_size(), 2);
    EXPECT_EQ(cache->get_mfu_size(), 1);
    EXPECT_EQ(std::get<0>(cache->get_lru_end()), 4);

    EXPECT_EQ(hits, 1);
}


