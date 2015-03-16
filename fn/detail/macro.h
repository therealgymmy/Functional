#ifndef __FN_DETAIL_MACRO__
#define __FN_DETAIL_MACRO__

namespace fn {
namespace detail {

struct Dummy {};

}
}

#define REQUIRES(...) \
    typename ::std::enable_if<(__VA_ARGS__), ::fn::detail::Dummy>::type = {}

#define DEFINE_IS_TEMPLATE(Name, Type) \
    template <typename C> \
    struct Name : ::std::false_type {}; \
    template <typename... Ts> \
    struct Name<Type<Ts...>>: ::std::true_type {}

#define X_TO_STRING(s) TO_STRING(s)
#define TO_STRING(s) #s

#define CONCAT(a,b) CONCAT_HIDDEN(a,b)
#define CONCAT_HIDDEN(a,b) a ## b

#define LOCATION "file: " __FILE__ ", line: " X_TO_STRING(__LINE__)

#define STATIC_ASSERT(...) static_assert((__VA_ARGS__), LOCATION)

#endif
