#ifndef __FN_TO__
#define __FN_TO__

#include <algorithm>

#include "fit/conditional.h"
#include "fit/pipable.h"

#include "detail/trait.h"
#include "detail/macro.h"

namespace fn {

namespace detail {

template <template <typename...> class C>
struct ContainerFactory {
    template <typename... Ts>
    auto gen() -> C<Ts...> {
        return C<Ts...> {};
    }
};

}

template <template <typename...> class C>
auto type() -> detail::ContainerFactory<C> {
    return detail::ContainerFactory<C> {};
}

#define TYPE(factory, input) \
    decltype(factory.template \
        gen<::std::remove_reference_t< \
            typename decltype(input)::value_type>>())

FIT_STATIC_FUNCTION(to) = ::fit::pipable(::fit::conditional(

    // specialization for sequence container -> sequence container
    //                    std::set           -> sequence container
    [] (auto input, auto factory,

        REQUIRES(detail::and_args(
            detail::or_args(
                detail::is_sequence_container<decltype(input)>(),
                detail::is_set<decltype(input)>()
            ),
            detail::is_sequence_container<TYPE(factory, input)>()
        ))
    ) {
        TYPE(factory, input) output(input.size());
        ::std::copy(input.begin(), input.end(), output.begin());
        return output;
    },

    // specialization for sequence container -> std::set
    [] (auto input, auto factory,

        REQUIRES(detail::and_args(
            detail::is_sequence_container<decltype(input)>(),
            detail::is_set<TYPE(factory, input)>()
        ))
    ) {
        TYPE(factory, input) output;
        output.insert(::std::begin(input), ::std::end(input));
        return output;
    }

));

#undef TYPE

}

#endif
