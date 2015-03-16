#ifndef __FN_FILTER__
#define __FN_FILTER__

#include <algorithm>

#include "fit/conditional.h"
#include "fit/pipable.h"

#include "detail/trait.h"
#include "detail/macro.h"

namespace fn {

FIT_STATIC_FUNCTION(filter) = ::fit::pipable(::fit::conditional(

    // specialization for sequence container
    [] (auto input, auto pred,

        REQUIRES(
            detail::is_sequence_container<decltype(input)>::value
        )
    ) {
        decltype(input) output(input.size());
        output.erase(
            ::std::copy_if(
                ::std::begin(input),
                ::std::end(input),
                ::std::begin(output),
                pred
            ),
            ::std::end(output)
        );
        return output;
    },

    // specialization for associative container
    [] (auto input, auto pred,

        REQUIRES(
            detail::is_associative_container<decltype(input)>::value
        )
    ) {
        decltype(input) output;
        ::std::for_each(
            ::std::begin(input),
            ::std::end(input),
            [pred, &output] (auto val) {
                if (pred(val))
                    output.insert(val);
            }
        );
        return output;
    }

));

FIT_STATIC_FUNCTION(filter_not) = ::fit::pipable(
    [] (auto input, auto pred,

        REQUIRES(
            detail::is_container<decltype(input)>()
        )
    ) {
        return input | filter([pred] (auto val) { return !pred(val); });
    }
);

}

#endif
