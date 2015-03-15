#ifndef __FN_CONTAINER_UTILITY__
#define __FN_CONTAINER_UTILITY__

#include <utility>

#include "fit/conditional.h"
#include "fit/partial.h"

#include "detail/macro.h"

namespace fn {

FIT_STATIC_FUNCTION(on_map_value) = ::fit::partial(::fit::conditional(

    // specialization for void return type func
    // assumed to be used with `each`
    [] (auto func, auto pair,

        REQUIRES(
            ::std::is_same<decltype(func(pair.second)),
                           void>::value
        )
    ) {
        func(pair.second);
    },

    // specialization for bool return type func
    // assumed to be used with `filter`
    [] (auto func, auto pair,
        REQUIRES(
            ::std::is_same<decltype(func(pair.second)),
                           bool>::value
        )
    ) {
        return func(pair.second);
    },

    // specialization for decltype(pair.second) return type func
    // assumed to be used with `fmap`
    [] (auto func, auto pair,

        REQUIRES(
            ::std::is_same<decltype(func(pair.second)),
                           decltype(pair.second)>::value
        )
    ) {
        return ::std::make_pair(pair.first, func(pair.second));
    },

    // specialization for func being a BinaryFunction
    // assumed to be used with `reduce`
    [] (auto func, auto init, auto pair,
        REQUIRES(
            ::std::is_same<decltype(func(init, pair.second)),
                           decltype(init)>::value
        )
    ) {
        return func(init, pair.second);
    }

));

}

#endif
