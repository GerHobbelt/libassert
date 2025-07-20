//
// assert.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Defines the assert macro and related functionality.
//
// NOTE: this header file OVERRIDES any system/library-defined `assert()` macro and replaces it with the libassert one.
// *Also* introduced is the use of C++-based functionality underneath this macro/function to ensure userland code
// only feeds **boolean expressions** to the assert macro: arbitrary assert argument expressions which *assume*
// *implicit* conversion to boolean (i.e. implicit non-null test) SHOULD cause a compiler error!
//

// NOTE: no include guard

#if defined(_MSC_VER) && _MSC_VER >= 1929
# include <corecrt.h>
#endif

#if defined(_MSC_VER) 

#ifndef _CRT_PACKING 
#define _CRT_PACKING 8
#endif

#endif

#if !defined(LIBASSERT_BEGIN_C_HEADER) && !defined(LIBASSERT_END_C_HEADER)

// All C headers have a common prologue and epilogue, to enclose the header in
// an extern "C" declaration when the header is #included in a C++ translation
// unit and to push/pop the packing.
#if defined __cplusplus

#if defined(_MSC_VER) 

#define LIBASSERT_BEGIN_C_HEADER										\
        __pragma(pack(push, _CRT_PACKING))						\
        extern "C" {

#define LIBASSERT_END_C_HEADER										\
        }														\
        __pragma(pack(pop))

#else

#define LIBASSERT_BEGIN_C_HEADER										\
        extern "C" {

#define LIBASSERT_END_C_HEADER										\
        }														

#endif

#else    // __cplusplus

#if defined(_MSC_VER) 

#define LIBASSERT_BEGIN_C_HEADER										\
        __pragma(pack(push, _CRT_PACKING))

#define LIBASSERT_END_C_HEADER										\
        __pragma(pack(pop))

#else

#define LIBASSERT_BEGIN_C_HEADER										

#define LIBASSERT_END_C_HEADER										

#endif

#endif

#endif // !defined(LIBASSERT_BEGIN_C_HEADER) && !defined(LIBASSERT_END_C_HEADER)


#undef assert
#undef assert_and_continue


LIBASSERT_BEGIN_C_HEADER

void __cdecl fz_sysassert(const char * _Message, const char * _File, const char * _Function, unsigned int _Line);
void __cdecl fz_sysassert_and_continue(const char * _Message, const char * _File, const char * _Function, unsigned int _Line);

LIBASSERT_END_C_HEADER

#if 0
#define LIBASSERT_USE_MAGIC_ENUM     1
#endif

#if 0
#define LIBASSERT_USE_FMT            1
//#define LIBASSERT_USE_STD_FORMAT     1  // <-- is set up in libassert/platform.hpp
#endif

#define LIBASSERT_LOWERCASE     1

#if 0
#define LIBASSERT_BREAK_ON_FAIL 1   // wake up your debugger, iff we're running inside one!
#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS 1
#undef  LIBASSERT_PREFIX_ASSERTIONS   // --> define ASSERT() et al
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

// #define LIBASSERT_INVOKE_VAL(expr, doreturn, check_expression, name, type, failaction, ...)     ....
// -->
// libassert::detail::process_assert_fail(decomposer, params, ...)
// libassert::detail::process_assert_fail_n(decomposer, params, ...)

// #define LIBASSERT_DEBUG_ASSERT(expr, ...) LIBASSERT_INVOKE(expr, "DEBUG_ASSERT", debug_assertion, , __VA_ARGS__)

// #define LIBASSERT_ASSERT(expr, ...) LIBASSERT_INVOKE(expr, "ASSERT", assertion, , __VA_ARGS__)

// #define LIBASSERT_ASSUME(expr, ...) LIBASSERT_INVOKE(expr, "ASSUME", assumption, LIBASSERT_ASSUME_ACTION, __VA_ARGS__)

// #define LIBASSERT_PANIC(...) LIBASSERT_INVOKE_PANIC("PANIC", panic, __VA_ARGS__)

//  #define LIBASSERT_UNREACHABLE(...) LIBASSERT_INVOKE_PANIC("UNREACHABLE", unreachable, __VA_ARGS__)

//  #define LIBASSERT_DEBUG_ASSERT_VAL(expr, ...) LIBASSERT_INVOKE_VAL(expr, true, true, "DEBUG_ASSERT_VAL", debug_assertion, , __VA_ARGS__)

// #define LIBASSERT_ASSUME_VAL(expr, ...) LIBASSERT_INVOKE_VAL(expr, true, true, "ASSUME_VAL", assumption, LIBASSERT_ASSUME_ACTION, __VA_ARGS__)

// #define LIBASSERT_ASSERT_VAL(expr, ...) LIBASSERT_INVOKE_VAL(expr, true, true, "ASSERT_VAL", assertion, , __VA_ARGS__)


#include <libassert/assert.hpp>


#if 0

#ifndef assert

LIBASSERT_BEGIN_C_HEADER

#ifndef NDEBUG

#define assert(expression) ((void)(                                                     \
            (!!(expression)) ||                                                         \
            (fz_sysassert(#expression, __FILE__, __func__, __LINE__), 0)				\
        ))

#define assert_and_continue(expression) ((void)(                                        \
            (!!(expression)) ||                                                         \
            (fz_sysassert_and_continue(#expression, __FILE__, __func__, __LINE__), 0)	\
        ))

#else

#define assert(expression) (void)(0)

#define assert_and_continue(expression) (void)(expression)

#endif   // NDEBUG

LIBASSERT_END_C_HEADER

#endif  // !assert

#endif


#pragma warning(pop) // _UCRT_DISABLED_WARNINGS


