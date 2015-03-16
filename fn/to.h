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
    using gen_t = C<Ts...>;

    template <typename... Ts>
    auto gen() {
        return gen_t<Ts...> {};
    }
};

template <typename C>
struct extract_container_type : std::false_type {};

template <template <typename...> class C>
struct extract_container_type<ContainerFactory<C>> : ContainerFactory<C> {};

template <typename T, typename... Ts>
using specialized_container_t =
    typename extract_container_type<T>::template gen_t<Ts...>;

}

template <template <typename...> class C>
auto type() -> detail::ContainerFactory<C> {
    return detail::ContainerFactory<C> {};
}

#define TYPE(factory, input) \
    detail::specialized_container_t< \
        decltype(factory), \
        ::std::remove_cv_t<::std::remove_reference_t< \
            decltype(*::std::begin(input)) \
        >> \
    >

FIT_STATIC_FUNCTION(to) = ::fit::pipable(::fit::conditional(

    // specialization for sequence container -> sequence container
    //                    std::set           -> sequence container
    [] (auto input, auto factory,

        REQUIRES(detail::and_args(
            detail::or_args(
                detail::is_sequence_container<decltype(input)>::value,
                detail::is_set<decltype(input)>::value
            ),
            detail::is_sequence_container<TYPE(factory, input)>::value
        ))
    ) {
        TYPE(factory, input) output(input.size());
        ::std::copy(input.begin(), input.end(), output.begin());
        return output;
    },

    // specialization for sequence container -> std::set
    [] (auto input, auto factory,

        REQUIRES(detail::and_args(
            detail::is_sequence_container<decltype(input)>::value,
            detail::is_set<TYPE(factory, input)>::value
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
