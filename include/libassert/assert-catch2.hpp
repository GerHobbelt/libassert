#ifndef LIBASSERT_CATCH2_HPP
#define LIBASSERT_CATCH2_HPP

#ifndef __cplusplus
#error error 1003: Unexpected compiler, expected C++ compiler.
#endif // !defined(__cplusplus)

#include <catch2/catch_test_macros.hpp>

#define LIBASSERT_PREFIX_ASSERTIONS
#include <libassert/assert.hpp>
#include <libassert/assert-catch2-macros.hpp>

#endif
