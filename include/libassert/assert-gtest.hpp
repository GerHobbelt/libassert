#ifndef LIBASSERT_GTEST_HPP
#define LIBASSERT_GTEST_HPP

#ifndef __cplusplus
#error error 1003: Unexpected compiler, expected C++ compiler.
#endif // !defined(__cplusplus)

#undef  LIBASSERT_PREFIX_ASSERTIONS   
//#define LIBASSERT_PREFIX_ASSERTIONS   1
#include <libassert/config.h>

#include <gtest/gtest.h>

#include <libassert/assert.h>
#include <libassert/assert-gtest-macros.hpp>

#endif
