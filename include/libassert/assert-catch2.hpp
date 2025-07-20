#ifndef LIBASSERT_CATCH2_HPP
#define LIBASSERT_CATCH2_HPP

#ifndef __cplusplus
#error error 1003: Unexpected compiler, expected C++ compiler.
#endif // !defined(__cplusplus)

#undef  LIBASSERT_PREFIX_ASSERTIONS   
#define LIBASSERT_PREFIX_ASSERTIONS   1
#include <libassert/config.h>

#include <catch2/catch_test_macros.hpp>

#include <libassert/assert.h>
#include <libassert/assert-catch2-macros.hpp>

#endif
