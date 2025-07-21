// ----------------------------------------------------------------------
// WARNING: No include guard. This was done intentionally. See below.
// ----------------------------------------------------------------------

// Copyright (c) 2021-2025 Jeremy Rifkin under the MIT license
// https://github.com/jeremy-rifkin/libassert

#include <libassert/config.h>
#include <libassert/assert-macros.hpp>

// Intentionally done outside the include guard. Libc++ leaks `assert` (among other things), so the include for
// assert.hpp should go after other includes when using -DLIBASSERT_LOWERCASE.
#if LIBASSERT_LOWERCASE || defined(LIBASSERT_OFFER_SYSTEM_ASSERT_REPLACEMENT)

 #ifdef assert
  #undef assert
 #endif

 #ifndef LIBASSERT_INVOKE
  #error "libassert's assert load process failed to properly initialize the `assert` & `LIBASSERT_INVOKE` macros. This suggests there's a bug in libassert itself."
 #endif


#if defined __cplusplus

// assert() must act like it's an expression type, rather than a statement type.
// Some libraries' assertions depend on this behaviour, where the assert() macro
// can be incorporated inside a comma-separated expression statement.
#if !defined(LIBASSERT_ASSERT_IS_EXPRESSION)
#ifndef NDEBUG
#define assert(expr, ...) LIBASSERT_INVOKE(expr, "assert_simple", assertion, LIBASSERT_EMPTY_ACTION __VA_OPT__(,) __VA_ARGS__)
#else
#define assert(expr, ...) LIBASSERT_NOOP_STATEMENT()
#endif
#else
#ifndef NDEBUG
#define assert(expr, ...) LIBASSERT_INVOKE_EXPRESSION(expr, "assert_simple", assertion __VA_OPT__(,) __VA_ARGS__)
#else
#define assert(expr, ...) LIBASSERT_NOOP_EXPRESSION()
#endif
#endif

#else // __cplusplus

// assert() must act like it's an expression type, rather than a statement type.
// Some libraries' assertions depend on this behaviour, where the assert() macro
// can be incorporated inside a comma-separated expression statement.
#if !defined(LIBASSERT_ASSERT_IS_EXPRESSION)
#ifndef NDEBUG
#define assert(expr, ...) LIBASSERT_INVOKE(expr, "assert_simple", assertion, LIBASSERT_EMPTY_ACTION __VA_OPT__(,) __VA_ARGS__)
#else
#define assert(expr, ...) LIBASSERT_NOOP_STATEMENT()
#endif
#else
#ifndef NDEBUG
#define assert(expr, ...) LIBASSERT_INVOKE_EXPRESSION(expr, "assert_simple", assertion __VA_OPT__(,) __VA_ARGS__)
#else
#define assert(expr, ...) LIBASSERT_NOOP_EXPRESSION()
#endif
#endif

#endif // __cplusplus

#else // LIBASSERT_LOWERCASE

#if 0
#pragma message(LIBASSERT_PM_REMINDER "libassert NOTICE: assert() system macros are NOT defined/overriden by libassert as neither LIBASSERT_LOWERCASE nor LIBASSERT_OFFER_SYSTEM_ASSERT_REPLACEMENT are set.")
#endif

#endif // LIBASSERT_LOWERCASE

