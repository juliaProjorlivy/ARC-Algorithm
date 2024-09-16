// #include "arc.hpp"
//
// template<typename PageT, typename F, typename KeyT>
// void cache_t<PageT, F, KeyT>::replace(KeyT key)
// {
//     if((lru_size >= 1) && ((mfu_hist.hit(key) && lru_size == p) || (lru_size > p)))
//     {
//         auto lru_page = pop_back_lru();
//         lru_hist.push_front(lru_page);
//     }
//     else
//     {
//         auto mfu_page = pop_back_mfu();
//         mfu_hist.push_front(mfu_page);
//     }
// }
//
// template<typename PageT, typename KeyT>
// template<typename F> void cache_t<PageT, KeyT>::lookup_update(KeyT key, F slow_get_page)
// {
//     auto find_page = hashTbl.find(key);
//     if(hashTbl.end() != find_page)
//     {
//         move_to_mfu_from_lru(find_page);
//     }
//     else if(lru_hist.hit(key))
//     {
//         p = std::min(size, p + std::max(mfu_hist.size() / lru_hist.size(), 1));
//         replace(key);
//         PageT page = slow_get_page(key);
//         push_front_mfu(page);
//     }
//     else if(mfu_hist.hit(key))
//     {
//         p = std::max(0, p - std::max(lru_hist.size() / mfu_hist.size(), 1));
//         replace(key);
//         push_front_mfu(slow_get_page(key));
//     }
//     else
//     {
//         std::size_t L1_size = lru_hist.size() + lru_size == size;
//         if(L1_size)
//         {
//             if(lru_size < size)
//             {
//                 lru_hist.pop_back();
//                 replace(key);
//             }
//             else
//             {
//                 pop_back_lru();
//             }
//         }
//         else if(L1_size < size && L1_size + mfu_hist.size() + mfu_size >= size)
//         {
//             if(L1_size + mfu_hist.size() + mfu_size == 2 * size)
//             {
//                 mfu_hist.pop_back();
//             }
//             replace(key);
//         }
//         push_front_lru(slow_get_page(key), key);
//     }
// }

