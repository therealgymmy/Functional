#ifndef __FN_FMAP__
#define __FN_FMAP__

#include <algorithm>

#include "fit/conditional.h"
#include "fit/pipable.h"

#include "detail/trait.h"
#include "detail/macro.h"

namespace fn {

FIT_STATIC_FUNCTION(fmap) = ::fit::pipable(::fit::conditional(

    // specialization for sequence container
    [] (auto input, auto func,

        REQUIRES(
            detail::is_sequence_container<decltype(input)>::value
        )
    ) {
        decltype(input) output(input.size());
        ::std::transform(
            ::std::begin(input),
            ::std::end(input),
            ::std::begin(output),
            func
        );
        return output;
    },

    // specialization for associative container
    [] (auto input, auto func,

        REQUIRES(
            detail::is_associative_container<decltype(input)>::value
        )
    ) {
        decltype(input) output;
        for (auto element : input) {
            output.insert(func(element));
        }
        return output;
    }

));

}

#endif
