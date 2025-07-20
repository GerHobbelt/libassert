
// NOTE: no include guard

#include <libassert/platform.h>


#ifndef LIBASSERT_USE_MAGIC_ENUM
#define LIBASSERT_USE_MAGIC_ENUM                    0 // default, if you or platform.h hasn't overriden it already
#endif
#if LIBASSERT_USE_MAGIC_ENUM != 0
#undef LIBASSERT_USE_MAGIC_ENUM
#define LIBASSERT_USE_MAGIC_ENUM                    1
#endif

#ifndef LIBASSERT_USE_FMT
#define LIBASSERT_USE_FMT                           1 // default, if you or platform.h hasn't overriden it already
#endif
#if LIBASSERT_USE_FMT != 0
#undef LIBASSERT_USE_FMT
#define LIBASSERT_USE_FMT                           1
#endif

#ifndef LIBASSERT_USE_STD_FORMAT
#define LIBASSERT_USE_STD_FORMAT                    0 // default, if you or platform.h hasn't overriden it already
#endif
#if LIBASSERT_USE_STD_FORMAT != 0
#undef LIBASSERT_USE_STD_FORMAT
#define LIBASSERT_USE_STD_FORMAT                    1
#endif

#ifndef LIBASSERT_LOWERCASE
#define LIBASSERT_LOWERCASE                         0 // default, if you haven't overriden it already
#endif
#if LIBASSERT_LOWERCASE != 0
#undef LIBASSERT_LOWERCASE
#define LIBASSERT_LOWERCASE                         1
#endif

// wake up your debugger, iff we're running inside one!
#ifndef LIBASSERT_BREAK_ON_FAIL
#define LIBASSERT_BREAK_ON_FAIL                     1 // default, if you haven't overriden it already
#endif
#if LIBASSERT_BREAK_ON_FAIL != 0
#undef LIBASSERT_BREAK_ON_FAIL
#define LIBASSERT_BREAK_ON_FAIL                     1
#endif

#ifndef LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS
#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS     0 // default, if you haven't overriden it already
#endif
#if LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS != 0
#undef LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS
#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS     1
#endif

// --> define ASSERT() et al
#ifndef LIBASSERT_PREFIX_ASSERTIONS
#define LIBASSERT_PREFIX_ASSERTIONS                 0 // default, if you haven't overriden it already
#endif
#if LIBASSERT_PREFIX_ASSERTIONS != 0
#undef LIBASSERT_PREFIX_ASSERTIONS
#define LIBASSERT_PREFIX_ASSERTIONS                 1
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

//  #define LIBASSERT_UNREACHABLE(...)                           LIBASSERT_INVOKE_PANIC("UNREACHABLE", unreachable, __VA_ARGS__)

//  #define LIBASSERT_DEBUG_ASSERT_VAL(expr, ...)                LIBASSERT_INVOKE_VAL(expr, true, true, "DEBUG_ASSERT_VAL", debug_assertion, , __VA_ARGS__)

// #define LIBASSERT_ASSUME_VAL(expr, ...)                       LIBASSERT_INVOKE_VAL(expr, true, true, "ASSUME_VAL", assumption, LIBASSERT_ASSUME_ACTION, __VA_ARGS__)

// #define LIBASSERT_ASSERT_VAL(expr, ...)                       LIBASSERT_INVOKE_VAL(expr, true, true, "ASSERT_VAL", assertion, , __VA_ARGS__)

