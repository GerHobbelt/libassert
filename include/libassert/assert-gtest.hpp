#ifndef LIBASSERT_GTEST_HPP
#define LIBASSERT_GTEST_HPP

#ifndef __cplusplus
#error error 1003: Unexpected compiler, expected C++ compiler.
#endif // !defined(__cplusplus)

#define LIBASSERT_PREFIX_ASSERTIONS
#include <gtest/gtest.h>
#include <libassert/assert.hpp>
#include <libassert/assert-gtest-macros.hpp>

#endif
