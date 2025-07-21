#ifndef LIBASSERT_PRECURSOR_MACROS_HPP
#define LIBASSERT_PRECURSOR_MACROS_HPP

#include <libassert/config.h>
#include <libassert/platform.hpp>
#include <libassert/utilities.hpp>


// When we include magic_enum, et al, we need an "early" version of the LIBASSERT_INVOKE macro for the preprocessor to expand
// the assertion statements in those library header files while we load them from stringification.hpp.

#define LIBASSERT_INVOKE(expr, name, type, failaction, ...) \
    LIBASSERT_PRIMITIVE_ASSERT(expr, __VA_ARGS__)

#endif

