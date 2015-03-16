#ifndef __FN_MAYBE__
#define __FN_MAYBE__

#include <stdexcept>

namespace fn {

template <typename T>
class Maybe;

namespace detail {

template <typename C>
struct is_maybe : std::false_type {};

template <typename... Ts>
struct is_maybe<Maybe<Ts...>>: std::true_type {};

}

template <typename T>
class Maybe {
public:
    Maybe() : valid(false) {}
    Maybe(T v) : valid(true), val(v) {}

    explicit operator bool() const {
        return valid;
    }

    T ok() {
        if (!valid) {
            throw ::std::runtime_error("Maybe is in invalid state");
        }
        return val;
    }

    template <typename U>
    T or_expect(U other) {
        if (!valid) {
            return other;
        }
        return val;
    }

private:
    bool valid;
    T val;
};

template <typename T>
auto maybe(T v) {
    return Maybe<T>(v);
}

template <typename T>
auto maybe() {
    return Maybe<T>();
}

FIT_STATIC_FUNCTION(ok) = ::fit::pipable(
    [] (auto input,

        REQUIRES(
            detail::is_maybe<decltype(input)>::value
        )
    ) {
        return input.ok();
    }
);

}

#endif
