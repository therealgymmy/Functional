#ifndef __FN_REDUCE__
#define __FN_REDUCE__

#include <algorithm>

#include "fit/conditional.h"
#include "fit/pipable.h"

#include "detail/trait.h"
#include "detail/macro.h"

namespace fn {

FIT_STATIC_FUNCTION(reduce) = ::fit::pipable(::fit::conditional(

    [] (auto input, auto func,

        REQUIRES(
            detail::is_container<decltype(input)>()
        )
    ) {
        ::std::remove_reference_t<decltype(*::std::begin(input))> init {};
        return ::std::accumulate(
            ::std::begin(input),
            ::std::end(input),
            init,
            func
        );
    },

    [] (auto input, auto func, auto init,

        REQUIRES(
            detail::is_container<decltype(input)>()
        )
    ) {
        return ::std::accumulate(
            ::std::begin(input),
            ::std::end(input),
            init,
            func
        );
    }

));

}

#endif
