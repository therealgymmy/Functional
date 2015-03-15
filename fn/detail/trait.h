#ifndef __FN_DETAIL_TRAIT__
#define __FN_DETAIL_TRAIT__

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <vector>
#include <set>

#include "misc_helper.h"

#define DEFINE_IS_CONTAINER(Name, Type) \
    template<typename C> \
    struct Name : std::false_type {}; \
    template<typename... Ts> \
    struct Name<Type<Ts...>>: std::true_type {}

namespace fn {
namespace detail {

DEFINE_IS_CONTAINER(is_array,        ::std::array);
DEFINE_IS_CONTAINER(is_deque,        ::std::deque);
DEFINE_IS_CONTAINER(is_forward_list, ::std::forward_list);
DEFINE_IS_CONTAINER(is_list,         ::std::list);
DEFINE_IS_CONTAINER(is_map,          ::std::map);
DEFINE_IS_CONTAINER(is_multimap,     ::std::multimap);
DEFINE_IS_CONTAINER(is_multiset,     ::std::multiset);
DEFINE_IS_CONTAINER(is_vector,       ::std::vector);
DEFINE_IS_CONTAINER(is_set,          ::std::set);

template <typename T>
constexpr bool is_sequence_container() {
    return or_args(
        is_array<T>::value,
        is_deque<T>::value,
        is_forward_list<T>::value,
        is_list<T>::value,
        is_vector<T>::value
    );
}

template <typename T>
constexpr bool is_associative_container() {
    return or_args(
        is_set<T>::value,
        is_map<T>::value,
        is_multimap<T>::value,
        is_multiset<T>::value
    );
}

template <typename T>
constexpr bool is_container() {
    return or_args(
        is_sequence_container<T>(),
        is_associative_container<T>()
    );
}

}
}

#undef DEFINE_IS_CONTAINER

#endif
