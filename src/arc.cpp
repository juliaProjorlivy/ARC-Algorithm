#include "arc.hpp"

// history


// cache
template<typename PageT, typename KeyT>
template<typename F>
bool cache_t<PageT, KeyT>::lookup_update(KeyT key,  F slow_get_page)
{
    auto hit = hashTbl.find(key);
    //if not in T1+T2
    if(hit == hashTbl.end())
    {
        //if in B1
        ptr = std::min(size, ptr + std::max(B2.length() / B1.length(), 1));

    }
    else
    {
    
    }

}

template<typename PageT, typename KeyT>
void cache_t<PageT, KeyT>::move_to(history_t<KeyT> B, KeyT key)
{
    // if B1 and B2 are full => pop one elem from B1
    if(B1.length() + B2.length() >= size)
    {
        B.pop_back();
    }
    B.push_front(key);
}

template<typename PageT, typename KeyT>
void cache_t<PageT, KeyT>::replace(KeyT key_new)
{
    auto key_popped = cache.pop_front();
    hashTbl.erase(key_popped);
    if(T1_size >= 1 && (is_B2(key_new) && T1_size == ptr) || T1_size > ptr)
    {
        move_to(&B1, key_popped);
    }
    else
    {
        move_to_B2(key_popped);
    }
}

