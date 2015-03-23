#ifndef __FN_TAKE__
#define __FN_TAKE__

#include <algorithm>

#include "fit/conditional.h"
#include "fit/pipable.h"

#include "detail/trait.h"
#include "detail/macro.h"

namespace fn {

FIT_STATIC_FUNCTION(take) = ::fit::pipable(::fit::conditional(

    [] (auto input, size_t number,

        REQUIRES(
            detail::is_sequence_container<decltype(input)>::value
        )
    ) {
        if (number > input.size()) {
            return input;
        }

        decltype(input) output(number);
        ::std::copy_n(
            ::std::begin(input),
            number,
            ::std::begin(output)
        );
        return output;
    },

    [] (auto input, size_t number,

        REQUIRES(
            detail::is_associative_container<decltype(input)>::value
        )
    ) {
        if (number > input.size()) {
            return input;
        }

        decltype(input) output;
        auto itr = ::std::begin(input);
        for (size_t i = 0; i < number; ++i, ++itr) {
            output.insert(*itr);
        }
        return output;
    }

));

FIT_STATIC_FUNCTION(first) = ::fit::pipable([] (auto input,

    REQUIRES(
        detail::is_container<decltype(input)>::value
    )
) {
    return *::std::begin(input);
});

FIT_STATIC_FUNCTION(last) = ::fit::pipable([] (auto input,

    REQUIRES(
        detail::is_container<decltype(input)>::value
    )
) {
    // Bug: libstdc++ does not yet have ::std::rbegin
    return *::std::prev(::std::end(input));
});

}

#endif
