#ifndef __FN_EACH__
#define __FN_EACH__

#include <algorithm>

#include "fit/conditional.h"
#include "fit/pipable.h"

#include "detail/trait.h"
#include "detail/macro.h"

namespace fn {

FIT_STATIC_FUNCTION(each) = ::fit::pipable(::fit::conditional(

    // specialization for container
    [] (auto input, auto func,

        REQUIRES(
            detail::is_container<decltype(input)>::value
        )
    ) {
        for (auto element : input) {
            func(element);
        }
        return input;
    }

));

}

#endif
