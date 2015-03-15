#ifndef __FN_DETAIL_MISC_HELPER__
#define __FN_DETAIL_MISC_HELPER__

namespace fn {
namespace detail {

constexpr bool and_args(bool arg) {
    return arg;
}

template <typename... Args>
constexpr bool and_args(bool arg1, Args... args) {
    return arg1 && and_args(args...);
}

constexpr bool or_args(bool arg) {
    return arg;
}

template <typename... Args>
constexpr bool or_args(bool arg1, Args... args) {
    return arg1 || or_args(args...);
}

}
}

#endif
