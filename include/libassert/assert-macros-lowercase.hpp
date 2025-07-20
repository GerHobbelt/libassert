#ifndef LIBASSERT_ASSERT_MACROS_LOWERCASE_HPP
#define LIBASSERT_ASSERT_MACROS_LOWERCASE_HPP

// Copyright (c) 2021-2025 Jeremy Rifkin under the MIT license
// https://github.com/jeremy-rifkin/libassert

#include <libassert/assert-macros.hpp>

#if LIBASSERT_LOWERCASE

// Lowercase variants

 #ifndef NDEBUG
  #define debug_assert(expr, ...) LIBASSERT_INVOKE(expr, "debug_assert", debug_assertion, LIBASSERT_EMPTY_ACTION, __VA_ARGS__)
 #else
  #define debug_assert(expr, ...) (void)0
 #endif

 #ifndef NDEBUG
  #define debug_assert_val(expr, ...) LIBASSERT_INVOKE_VAL(expr, true, true, "debug_assert_val", debug_assertion, LIBASSERT_EMPTY_ACTION, __VA_ARGS__)
 #else
  #define debug_assert_val(expr, ...) LIBASSERT_INVOKE_VAL(expr, true, false, "debug_assert_val", debug_assertion, LIBASSERT_EMPTY_ACTION, __VA_ARGS__)
 #endif

 #define assert_val(expr, ...) LIBASSERT_INVOKE_VAL(expr, true, true, "assert_val", assertion, LIBASSERT_EMPTY_ACTION, __VA_ARGS__)

// Wrapper macro to allow support for C++26's user generated static_assert messages.
// The backup message version also allows for the user to provide a backup version that will
// be used if the compiler does not support user generated messages.
// More info on user generated static_assert's
// can be found here: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2741r1.pdf
//
// Currently the functionality works as such. If we are in a C++26 environment, the user generated message will be used.
// If we are not in a C++26 environment, then either the static_assert will be used without a message or the backup message.
// TODO: Maybe give these a better name? Ideally one that is shorter and more descriptive?
// TODO: Maybe add a helper to make passing user generated static_assert messages easier?
#if defined(__cpp_static_assert) && __cpp_static_assert >= 202306L
  #define libassert_user_static_assert(cond, constant) static_assert(cond, constant)
  #define libassert_user_static_assert_backup_msg(cond, msg, constant) static_assert(cond, constant)
  #define user_static_assert(cond, constant) static_assert(cond, constant)
  #define user_static_assert_backup_msg(cond, msg, constant) static_assert(cond, constant)
#else
  #define libassert_user_static_assert(cond, constant) static_assert(cond)
  #define libassert_user_static_assert_backup_msg(cond, msg, constant) static_assert(cond, msg)
  #define user_static_assert(cond, constant) static_assert(cond)
  #define user_static_assert_backup_msg(cond, msg, constant) static_assert(cond, msg)
#endif

#endif // LIBASSERT_LOWERCASE

#endif // LIBASSERT_HPP
