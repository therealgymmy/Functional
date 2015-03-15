#ifndef __FN_DETAIL_MACRO__
#define __FN_DETAIL_MACRO__

namespace fn {
namespace detail {

struct Dummy {};

}
}

#define REQUIRES(...) \
    typename std::enable_if<(__VA_ARGS__), ::fn::detail::Dummy>::type = {}

#define X_TO_STRING(s) TO_STRING(s)
#define TO_STRING(s) #s

#define CONCAT(a,b) CONCAT_HIDDEN(a,b)
#define CONCAT_HIDDEN(a,b) a ## b

#endif
