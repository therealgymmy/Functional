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

namespace fn {
namespace detail {

template <typename T>
struct is_template : ::std::false_type {};

template <template <typename...> class Func, typename... Ts>
struct is_template<Func<Ts...>> : ::std::true_type {};

template <template <typename...> class C1, template <typename...> class C2>
struct is_same_template : ::std::false_type {};

template <template <typename...> class C>
struct is_same_template<C, C> : ::std::true_type {};

DEFINE_IS_TEMPLATE(is_array,        ::std::array);
DEFINE_IS_TEMPLATE(is_deque,        ::std::deque);
DEFINE_IS_TEMPLATE(is_forward_list, ::std::forward_list);
DEFINE_IS_TEMPLATE(is_list,         ::std::list);
DEFINE_IS_TEMPLATE(is_map,          ::std::map);
DEFINE_IS_TEMPLATE(is_multimap,     ::std::multimap);
DEFINE_IS_TEMPLATE(is_multiset,     ::std::multiset);
DEFINE_IS_TEMPLATE(is_vector,       ::std::vector);
DEFINE_IS_TEMPLATE(is_set,          ::std::set);

template <typename T>
constexpr bool is_sequence_container_func() {
    return or_args(
        is_array<T>::value,
        is_deque<T>::value,
        is_forward_list<T>::value,
        is_list<T>::value,
        is_vector<T>::value
    );
}

template <typename T>
constexpr bool is_associative_container_func() {
    return or_args(
        is_set<T>::value,
        is_map<T>::value,
        is_multimap<T>::value,
        is_multiset<T>::value
    );
}

template <typename T>
constexpr bool is_container_func() {
    return or_args(
        is_sequence_container_func<T>(),
        is_associative_container_func<T>()
    );
}

template <typename T>
struct is_sequence_container {
    static constexpr bool value = is_sequence_container_func<T>();
};

template <typename T>
struct is_associative_container {
    static constexpr bool value = is_associative_container_func<T>();
};

template <typename T>
struct is_container {
    static constexpr bool value = is_container_func<T>();
};

}
}

#endif
