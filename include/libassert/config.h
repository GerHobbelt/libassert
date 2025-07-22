
// NOTE: no include guard

#include <libassert/platform.hpp>

//
// NOTE: there's a few config define's that we're not going to mess/default-set in here:
// it's the list above the bar line:
//
// 
// LIBASSERT_OFFER_SYSTEM_ASSERT_REPLACEMENT
//
// LIBASSERT_ASSERT_IS_EXPRESSION
//			assert() must act like it's an expression type, rather than a statement type.
//			Some libraries' assertions depend on this behaviour, where the assert() macro
//			can be incorporated inside a comma-separated expression statement.
//
// ======================================================================================
//

#ifndef LIBASSERT_USE_ENCHANTUM
#define LIBASSERT_USE_ENCHANTUM						0 // default, if you or platform.h hasn't overriden it already
#endif

#ifndef LIBASSERT_USE_MAGIC_ENUM
#define LIBASSERT_USE_MAGIC_ENUM                    0 // default, if you or platform.h hasn't overriden it already
#endif

#ifndef LIBASSERT_USE_FMT
#define LIBASSERT_USE_FMT                           1 // default, if you or platform.h hasn't overriden it already
#endif

#ifndef LIBASSERT_USE_STD_FORMAT
#define LIBASSERT_USE_STD_FORMAT                    0 // default, if you or platform.h hasn't overriden it already
#endif

#ifndef LIBASSERT_LOWERCASE
#define LIBASSERT_LOWERCASE                         0 // default, if you haven't overriden it already
#endif

// wake up your debugger, iff we're running inside one!
#ifndef LIBASSERT_BREAK_ON_FAIL
#define LIBASSERT_BREAK_ON_FAIL                     1 // default, if you haven't overriden it already
#endif

#ifndef LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS
#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS     0 // default, if you haven't overriden it already
#endif

// --> define ASSERT() et al
#ifndef LIBASSERT_PREFIX_ASSERTIONS
#define LIBASSERT_PREFIX_ASSERTIONS                 0 // default, if you haven't overriden it already
#endif

#ifndef LIBASSERT_ENFORCE_BOOLEAN_ASSERT_EXPRESSIONS
#define LIBASSERT_ENFORCE_BOOLEAN_ASSERT_EXPRESSIONS   0 // default, if you haven't overriden it already
#endif

#ifndef LIBASSERT_NO_STACKTRACE
#define LIBASSERT_NO_STACKTRACE                     0 // default, if you haven't overriden it already
#endif

//
// Here we make sure each configuration parameter is either 0 or 1.
//
// The conundrum we face at this time is that we can have any of THREE scenarios per 'define': 
// 
// 1a) a basic `#define XYZ`                      --> forced TRUE(1)
// 1b) `#define XYZ 1`                            --> forced TRUE(1)
// 2) `#undef XYZ` or plain *nothing*             --> (undecided)   ==> picked up our default setting 0/1
// 3) explicit `#define XYZ 0` to disable         --> forced FALSE(0)
//
// The preprocessor trick we use to determine if the user did any of these
// is by using a little integer unary/binary operator arithmetic, f.e.:
//
// #define CONFIG_PARAM                    0
//
// #define TEST_VAL        (~ CONFIG_PARAM +1)
//
// const int x = TEST_VAL;
// 
// (I.  2) --> #undef CONFIG_PARAM   => x=(~   +1)          => x = -2
// (II. 1a)--> #define CONFIG_PARAM  => x=(~   +1)          => x = -2
// (III.3) --> CONFIG_PARAM = 0      => x=(~ 0 +1) = (-1+1) => x =  0
// (IV. 1) --> CONFIG_PARAM = 1      => x=(~ 1 +1) = (-2+1) => x = -1
//
// where scenario (I.2) (`#undef CONFIG_PARAM`) CANNOT happen as that one will already have
// resulted in our 0/1 default setting above having been picked up, thus having moved on towards
// state (III.3) `CONFIG_PARAM = 0` or (IV.1) `CONFIG_PARAM = 1`...
//
// ... hence we can test each of these 3 scenarios in the preprocessor
// and decide which path our decision making should follow, always producing a preprocessor parameter
// valued 0 or 1 and never merely *empty*!
//
// --------------------------------------------------------------
//
// I've seen other preprocessor mechanics executed out there, but these always ended up with
// the preprocessor barfing a hairball or at least a pack of warnings, at least at the highest
// warning levels -- which is the preferred setting around here in the dev bunker!
// 
// > Generally I dial up the warning level to maximum, then explicit disable the warnings that are
// > very obnoxious and unhelpful all around; sometimes these compilers get too noisy for their own
// > good!


#if (~ LIBASSERT_USE_ENCHANTUM +1) == -2
#undef LIBASSERT_USE_ENCHANTUM
#define LIBASSERT_USE_ENCHANTUM                     1
#endif

#if (~ LIBASSERT_USE_MAGIC_ENUM +1) == -2
#undef LIBASSERT_USE_MAGIC_ENUM
#define LIBASSERT_USE_MAGIC_ENUM                    1
#endif

#if (~ LIBASSERT_USE_FMT +1) == -2
#undef LIBASSERT_USE_FMT
#define LIBASSERT_USE_FMT                           1
#endif

#if (~ LIBASSERT_USE_STD_FORMAT +1) == -2
#undef LIBASSERT_USE_STD_FORMAT
#define LIBASSERT_USE_STD_FORMAT                    1
#endif

#if (~ LIBASSERT_LOWERCASE +1) == -2
#undef LIBASSERT_LOWERCASE
#define LIBASSERT_LOWERCASE                         1
#endif

#if (~ LIBASSERT_BREAK_ON_FAIL +1) == -2
#undef LIBASSERT_BREAK_ON_FAIL
#define LIBASSERT_BREAK_ON_FAIL                     1
#endif

#if (~ LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS +1) == -2
#undef LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS
#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS     1
#endif

#if (~ LIBASSERT_PREFIX_ASSERTIONS +1) == -2
#undef LIBASSERT_PREFIX_ASSERTIONS
#define LIBASSERT_PREFIX_ASSERTIONS                 1
#endif

#if (~ LIBASSERT_ENFORCE_BOOLEAN_ASSERT_EXPRESSIONS +1) == -2
#undef LIBASSERT_ENFORCE_BOOLEAN_ASSERT_EXPRESSIONS
#define LIBASSERT_ENFORCE_BOOLEAN_ASSERT_EXPRESSIONS   1
#endif

#if (~ LIBASSERT_NO_STACKTRACE +1) == -2
#undef LIBASSERT_NO_STACKTRACE
#define LIBASSERT_NO_STACKTRACE                     1
#endif


// sanity checks: can't have both of these: pick the std::format system-provided one over {fmt}!

#if LIBASSERT_USE_FMT && LIBASSERT_USE_STD_FORMAT
#undef LIBASSERT_USE_FMT
#define LIBASSERT_USE_FMT                           0
#endif

#if LIBASSERT_USE_ENCHANTUM && LIBASSERT_USE_MAGIC_ENUM
#undef LIBASSERT_USE_MAGIC_ENUM
#define LIBASSERT_USE_MAGIC_ENUM                    0
#endif

//-----------------------------------------------------------------------------------------------------

// #define LIBASSERT_STATIC_DATA(name, type, expr_str, ...) 

// #define LIBASSERT_BREAKPOINT_IF_DEBUGGING()                    ...
// #define LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL()            ...

// #define LIBASSERT_INVOKE(expr, name, type, failaction, ...)    ...
// -->
// libassert::detail::process_assert_fail(decomposer, params, ...)
// libassert::detail::process_assert_fail_n(decomposer, params, ...)

// #define LIBASSERT_INVOKE_PANIC(name, type, ...) 
// -->
// libassert::detail::process_panic(params, ...)

// #define LIBASSERT_INVOKE_VAL(expr, doreturn, check_expression, name, type, failaction, ...)
// -->
// libassert::detail::process_assert_fail(decomposer, params, ...)
// libassert::detail::process_assert_fail_n(decomposer, params, ...)

// #define LIBASSERT_DEBUG_ASSERT(expr, ...)                     LIBASSERT_INVOKE(expr, "DEBUG_ASSERT", debug_assertion, , __VA_ARGS__)

// #define LIBASSERT_ASSERT(expr, ...)                           LIBASSERT_INVOKE(expr, "ASSERT", assertion, , __VA_ARGS__)

// #define LIBASSERT_ASSUME(expr, ...)                           LIBASSERT_INVOKE(expr, "ASSUME", assumption, LIBASSERT_ASSUME_ACTION, __VA_ARGS__)

// #define LIBASSERT_PANIC(...)                                  LIBASSERT_INVOKE_PANIC("PANIC", panic, __VA_ARGS__)

// #define LIBASSERT_UNREACHABLE(...)                            LIBASSERT_INVOKE_PANIC("UNREACHABLE", unreachable, __VA_ARGS__)

// #define LIBASSERT_DEBUG_ASSERT_VAL(expr, ...)                 LIBASSERT_INVOKE_VAL(expr, true, true, "DEBUG_ASSERT_VAL", debug_assertion, , __VA_ARGS__)

// #define LIBASSERT_ASSUME_VAL(expr, ...)                       LIBASSERT_INVOKE_VAL(expr, true, true, "ASSUME_VAL", assumption, LIBASSERT_ASSUME_ACTION, __VA_ARGS__)

// #define LIBASSERT_ASSERT_VAL(expr, ...)                       LIBASSERT_INVOKE_VAL(expr, true, true, "ASSERT_VAL", assertion, , __VA_ARGS__)

