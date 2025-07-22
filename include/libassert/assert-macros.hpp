#ifndef LIBASSERT_ASSERT_MACROS_HPP
#define LIBASSERT_ASSERT_MACROS_HPP

// Copyright (c) 2021-2025 Jeremy Rifkin under the MIT license
// https://github.com/jeremy-rifkin/libassert

#include <libassert/config.h>
#include <libassert/platform.hpp>

#if defined __cplusplus
#include <string_view>
#endif

#if LIBASSERT_IS_CLANG || LIBASSERT_IS_GCC || !LIBASSERT_NON_CONFORMANT_MSVC_PREPROCESSOR
 // Macro mapping utility by William Swanson https://github.com/swansontec/map-macro/blob/master/map.h
 #define LIBASSERT_EVAL0(...) __VA_ARGS__
 #define LIBASSERT_EVAL1(...) LIBASSERT_EVAL0(LIBASSERT_EVAL0(LIBASSERT_EVAL0(__VA_ARGS__)))
 #define LIBASSERT_EVAL2(...) LIBASSERT_EVAL1(LIBASSERT_EVAL1(LIBASSERT_EVAL1(__VA_ARGS__)))
 #define LIBASSERT_EVAL3(...) LIBASSERT_EVAL2(LIBASSERT_EVAL2(LIBASSERT_EVAL2(__VA_ARGS__)))
 #define LIBASSERT_EVAL4(...) LIBASSERT_EVAL3(LIBASSERT_EVAL3(LIBASSERT_EVAL3(__VA_ARGS__)))
 #define LIBASSERT_EVAL(...)  LIBASSERT_EVAL4(LIBASSERT_EVAL4(LIBASSERT_EVAL4(__VA_ARGS__)))
 #define LIBASSERT_MAP_END(...)
 #define LIBASSERT_MAP_OUT
 #define LIBASSERT_MAP_COMMA ,
 #define LIBASSERT_MAP_GET_END2() 0, LIBASSERT_MAP_END
 #define LIBASSERT_MAP_GET_END1(...) LIBASSERT_MAP_GET_END2
 #define LIBASSERT_MAP_GET_END(...) LIBASSERT_MAP_GET_END1
 #define LIBASSERT_MAP_NEXT0(test, next, ...) next LIBASSERT_MAP_OUT
 #define LIBASSERT_MAP_NEXT1(test, next) LIBASSERT_MAP_NEXT0(test, next, 0)
 #define LIBASSERT_MAP_NEXT(test, next)  LIBASSERT_MAP_NEXT1(LIBASSERT_MAP_GET_END test, next)
 #define LIBASSERT_MAP0(f, x, peek, ...) f(x) LIBASSERT_MAP_NEXT(peek, LIBASSERT_MAP1)(f, peek, __VA_ARGS__)
 #define LIBASSERT_MAP1(f, x, peek, ...) f(x) LIBASSERT_MAP_NEXT(peek, LIBASSERT_MAP0)(f, peek, __VA_ARGS__)
 #define LIBASSERT_MAP_LIST_NEXT1(test, next) LIBASSERT_MAP_NEXT0(test, LIBASSERT_MAP_COMMA next, 0)
 #define LIBASSERT_MAP_LIST_NEXT(test, next)  LIBASSERT_MAP_LIST_NEXT1(LIBASSERT_MAP_GET_END test, next)
 #define LIBASSERT_MAP_LIST0(f, x, peek, ...) \
                                   f(x) LIBASSERT_MAP_LIST_NEXT(peek, LIBASSERT_MAP_LIST1)(f, peek, __VA_ARGS__)
 #define LIBASSERT_MAP_LIST1(f, x, peek, ...) \
                                   f(x) LIBASSERT_MAP_LIST_NEXT(peek, LIBASSERT_MAP_LIST0)(f, peek, __VA_ARGS__)
 #define LIBASSERT_MAP(f, ...) LIBASSERT_EVAL(LIBASSERT_MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
 // LIBASSERT_MAP(f, 1, 2, 3)  -->  f(1) f(2) f(3)
#else
 // https://stackoverflow.com/a/29474124/15675011
 #define LIBASSERT_PLUS_TEXT_(x,y) x ## y
 #define LIBASSERT_PLUS_TEXT(x, y) LIBASSERT_PLUS_TEXT_(x, y)
 #define LIBASSERT_ARG_1(_1, ...) _1
 #define LIBASSERT_ARG_2(_1, _2, ...) _2
 #define LIBASSERT_ARG_3(_1, _2, _3, ...) _3
 #define LIBASSERT_ARG_40( _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, \
                 _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
                 _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
                 _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
                 ...) _39
 #define LIBASSERT_OTHER_1(_1, ...) __VA_ARGS__
 #define LIBASSERT_OTHER_3(_1, _2, _3, ...) __VA_ARGS__
 #define LIBASSERT_EVAL0(...) __VA_ARGS__
 #define LIBASSERT_EVAL1(...) LIBASSERT_EVAL0(LIBASSERT_EVAL0(LIBASSERT_EVAL0(__VA_ARGS__)))
 #define LIBASSERT_EVAL2(...) LIBASSERT_EVAL1(LIBASSERT_EVAL1(LIBASSERT_EVAL1(__VA_ARGS__)))
 #define LIBASSERT_EVAL3(...) LIBASSERT_EVAL2(LIBASSERT_EVAL2(LIBASSERT_EVAL2(__VA_ARGS__)))
 #define LIBASSERT_EVAL4(...) LIBASSERT_EVAL3(LIBASSERT_EVAL3(LIBASSERT_EVAL3(__VA_ARGS__)))
 #define LIBASSERT_EVAL(...) LIBASSERT_EVAL4(LIBASSERT_EVAL4(LIBASSERT_EVAL4(__VA_ARGS__)))
 #define LIBASSERT_EXPAND(x) x
 #define LIBASSERT_MAP_SWITCH(...) \
     LIBASSERT_EXPAND(LIBASSERT_ARG_40(__VA_ARGS__, 2, 2, 2, 2, 2, 2, 2, 2, 2, \
             2, 2, 2, 2, 2, 2, 2, 2, 2, 2, \
             2, 2, 2, 2, 2, 2, 2, 2, 2, \
             2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0))
 #define LIBASSERT_MAP_A(...) LIBASSERT_PLUS_TEXT(LIBASSERT_MAP_NEXT_, \
                                            LIBASSERT_MAP_SWITCH(0, __VA_ARGS__)) (LIBASSERT_MAP_B, __VA_ARGS__)
 #define LIBASSERT_MAP_B(...) LIBASSERT_PLUS_TEXT(LIBASSERT_MAP_NEXT_, \
                                            LIBASSERT_MAP_SWITCH(0, __VA_ARGS__)) (LIBASSERT_MAP_A, __VA_ARGS__)
 #define LIBASSERT_MAP_CALL(fn, Value) LIBASSERT_EXPAND(fn(Value))
 #define LIBASSERT_MAP_OUT
 #define LIBASSERT_MAP_NEXT_2(...) \
     LIBASSERT_MAP_CALL(LIBASSERT_EXPAND(LIBASSERT_ARG_2(__VA_ARGS__)), \
     LIBASSERT_EXPAND(LIBASSERT_ARG_3(__VA_ARGS__))) \
     LIBASSERT_EXPAND(LIBASSERT_ARG_1(__VA_ARGS__)) \
     LIBASSERT_MAP_OUT \
     (LIBASSERT_EXPAND(LIBASSERT_ARG_2(__VA_ARGS__)), LIBASSERT_EXPAND(LIBASSERT_OTHER_3(__VA_ARGS__)))
 #define LIBASSERT_MAP_NEXT_0(...)
 #define LIBASSERT_MAP(...)    LIBASSERT_EVAL(LIBASSERT_MAP_A(__VA_ARGS__))
#endif

#define LIBASSERT_STRINGIFY(x) #x,
#define LIBASSERT_COMMA ,

// Church boolean
#define LIBASSERT_IF(b) LIBASSERT_IF_##b
#define LIBASSERT_IF_true(t,...) t
#define LIBASSERT_IF_false(t,f,...) f

#if LIBASSERT_IS_CLANG || LIBASSERT_IS_GCC
 #if LIBASSERT_IS_GCC
  #define LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_GCC \
     _Pragma("GCC diagnostic ignored \"-Wparentheses\"") \
     _Pragma("GCC diagnostic ignored \"-Wuseless-cast\"") // #49
  #define LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_CLANG
  #define LIBASSERT_WARNING_PRAGMA_PUSH_GCC _Pragma("GCC diagnostic push")
  #define LIBASSERT_WARNING_PRAGMA_POP_GCC _Pragma("GCC diagnostic pop")
  #define LIBASSERT_WARNING_PRAGMA_PUSH_CLANG
  #define LIBASSERT_WARNING_PRAGMA_POP_CLANG
  #define LIBASSERT_WARNING_PRAGMA_PUSH_MSVC
  #define LIBASSERT_WARNING_PRAGMA_POP_MSVC
 #else
  #define LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_CLANG \
     _Pragma("GCC diagnostic ignored \"-Wparentheses\"") \
     _Pragma("GCC diagnostic ignored \"-Woverloaded-shift-op-parentheses\"")
  #define LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_GCC
  #define LIBASSERT_WARNING_PRAGMA_PUSH_GCC
  #define LIBASSERT_WARNING_PRAGMA_POP_GCC
  #define LIBASSERT_WARNING_PRAGMA_PUSH_CLANG _Pragma("GCC diagnostic push")
  #define LIBASSERT_WARNING_PRAGMA_POP_CLANG _Pragma("GCC diagnostic pop")
  #define LIBASSERT_WARNING_PRAGMA_PUSH_MSVC
  #define LIBASSERT_WARNING_PRAGMA_POP_MSVC
 #endif
#elif LIBASSERT_IS_MSVC
 #define LIBASSERT_WARNING_PRAGMA_PUSH_CLANG
 #define LIBASSERT_WARNING_PRAGMA_POP_CLANG
 #define LIBASSERT_WARNING_PRAGMA_PUSH_GCC
 #define LIBASSERT_WARNING_PRAGMA_POP_GCC
 // https://learn.microsoft.com/en-us/cpp/preprocessor/pragma-directives-and-the-pragma-keyword?view=msvc-170
 #define LIBASSERT_WARNING_PRAGMA_PUSH_MSVC   _Pragma("warning(push)")
 #define LIBASSERT_WARNING_PRAGMA_POP_MSVC    _Pragma("warning(pop)")
 #define LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_GCC
 #define LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_CLANG
#else
 #define LIBASSERT_WARNING_PRAGMA_PUSH_CLANG
 #define LIBASSERT_WARNING_PRAGMA_POP_CLANG
 #define LIBASSERT_WARNING_PRAGMA_PUSH_GCC
 #define LIBASSERT_WARNING_PRAGMA_POP_GCC
 #define LIBASSERT_WARNING_PRAGMA_PUSH_MSVC
 #define LIBASSERT_WARNING_PRAGMA_POP_MSVC
 #define LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_GCC
 #define LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_CLANG
#endif

#if defined __cplusplus

LIBASSERT_BEGIN_NAMESPACE
    inline void ERROR_ASSERTION_FAILURE_IN_CONSTEXPR_CONTEXT() {
        // This non-constexpr method is called from an assertion in a constexpr context if a failure occurs. It is
        // intentionally a no-op.
    }
LIBASSERT_END_NAMESPACE

#endif // __cplusplus

// __PRETTY_FUNCTION__ used because __builtin_FUNCTION() used in source_location (like __FUNCTION__) is just the method
// name, not signature
// The arg strings at the very least must be static constexpr. Unfortunately static constexpr variables are not allowed
// in constexpr functions pre-C++23.
// TODO: Try to do a hybrid in C++20 with std::is_constant_evaluated?
#if defined(__cpp_constexpr) && __cpp_constexpr >= 202211L
// Can just use static constexpr everywhere
#define LIBASSERT_STATIC_DATA(name, type, expr_str, ...) \
    /* extra string here because of extra comma from map, also serves as terminator */ \
    /* LIBASSERT_STRINGIFY LIBASSERT_VA_ARGS because msvc */ \
    /* Trailing return type here to work around a gcc <= 9.2 bug */ \
    /* Oddly only affecting builds under -DNDEBUG https://godbolt.org/z/5Treozc4q */ \
    using libassert_params_t = libassert::detail::assert_static_parameters; \
    /* NOLINTNEXTLINE(*-avoid-c-arrays) */ \
    static constexpr std::string_view libassert_arg_strings[] = { \
        LIBASSERT_MAP(LIBASSERT_STRINGIFY LIBASSERT_VA_ARGS(__VA_ARGS__)) "" \
    }; \
    static constexpr libassert_params_t _libassert_params = { \
        name LIBASSERT_COMMA \
        type LIBASSERT_COMMA \
        expr_str LIBASSERT_COMMA \
        {} LIBASSERT_COMMA \
        {libassert_arg_strings, sizeof(libassert_arg_strings) / sizeof(std::string_view)} LIBASSERT_COMMA \
    }; \
    const libassert_params_t* libassert_params = &_libassert_params;
#else
#define LIBASSERT_STATIC_DATA(name, type, expr_str, ...) \
    using libassert_params_t = libassert::detail::assert_static_parameters; \
    /* NOLINTNEXTLINE(*-avoid-c-arrays) */ \
    const libassert_params_t* libassert_params = []() -> const libassert_params_t* { \
        static constexpr std::string_view libassert_arg_strings[] = { \
            LIBASSERT_MAP(LIBASSERT_STRINGIFY LIBASSERT_VA_ARGS(__VA_ARGS__)) "" \
        }; \
        static constexpr libassert_params_t _libassert_params = { \
            name LIBASSERT_COMMA \
            type LIBASSERT_COMMA \
            expr_str LIBASSERT_COMMA \
            {} LIBASSERT_COMMA \
            {libassert_arg_strings, sizeof(libassert_arg_strings) / sizeof(std::string_view)} LIBASSERT_COMMA \
        }; \
        return &_libassert_params; \
    }();
#endif

// Note about statement expressions: These are needed for two reasons. The first is putting the arg string array and
// source location structure in .rodata rather than on the stack, the second is a _Pragma for warnings which isn't
// allowed in the middle of an expression by GCC. The semantics are similar to a function return:
// Given M m; in parent scope, ({ m; }) is an rvalue M&& rather than an lvalue
// ({ M m; m; }) doesn't move, it copies
// ({ M{}; }) does move
// Of relevance to this: in foo(__extension__ ({ M{1} + M{1}; })); the lifetimes of the M{1} objects end during the
// statement expression but the lifetime of the returned object is extend to the end of the full foo() expression.
// A wrapper struct is used here to return an lvalue reference from a gcc statement expression.
// Note: There is a current issue with ternaries: auto x = assert(b ? y : y); must copy y. This can be fixed with
// lambdas but that's potentially very expensive compile-time wise. Need to investigate further.
// Note: libassert::detail::expression_decomposer(libassert::detail::expression_decomposer{} << expr) done for ternary
#if defined __cplusplus

#if LIBASSERT_IS_MSVC
#define LIBASSERT_INVOKE_VAL_PRETTY_FUNCTION_ARG ,libassert::detail::pretty_function_name_wrapper{libassert_msvc_pfunc}
#else
#define LIBASSERT_INVOKE_VAL_PRETTY_FUNCTION_ARG ,libassert::detail::pretty_function_name_wrapper{LIBASSERT_PFUNC}
#endif
#define LIBASSERT_PRETTY_FUNCTION_ARG ,libassert::detail::pretty_function_name_wrapper{LIBASSERT_PFUNC}

#else // __cplusplus

#define LIBASSERT_INVOKE_VAL_PRETTY_FUNCTION_ARG ,libassert_pretty_function_name_wrapper(LIBASSERT_PFUNC)
#define LIBASSERT_PRETTY_FUNCTION_ARG ,libassert_pretty_function_name_wrapper(LIBASSERT_PFUNC)

const char *libassert_pretty_function_name_wrapper(const char *pfuncname);

#endif // __cplusplus


#if LIBASSERT_IS_CLANG // -Wall in clang
 #define LIBASSERT_IGNORE_UNUSED_VALUE _Pragma("GCC diagnostic ignored \"-Wunused-value\"")
#elif LIBASSERT_IS_MSVC
#define LIBASSERT_IGNORE_UNUSED_VALUE  _Pragma("warning(disable: 4101)") // warning C4101: 'info': unreferenced local variable
#else
 #define LIBASSERT_IGNORE_UNUSED_VALUE
#endif


#if defined __cplusplus
extern "C"
#endif // __cplusplus
LIBASSERT_EXPORT void libassert_breakpoint_if_debugger_present(void);


#if defined __cplusplus

#define LIBASSERT_BREAKPOINT_IF_DEBUGGING() \
    do \
        if(libassert::is_debugger_present()) { \
            LIBASSERT_BREAKPOINT(); \
        } \
    while(0)

#else // __cplusplus

#define LIBASSERT_BREAKPOINT_IF_DEBUGGING() \
    libassert_breakpoint_if_debugger_present()

#endif // __cplusplus

#if LIBASSERT_BREAK_ON_FAIL
 #define LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL() LIBASSERT_BREAKPOINT_IF_DEBUGGING()
#else
 #define LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL()
#endif

#if !LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS

// kill the "early definition" from further above, which we used for magic_enum & friends.
#undef LIBASSERT_INVOKE

#if defined __cplusplus

#define LIBASSERT_INVOKE(expr, name, type, failaction, ...) \
    /* must push/pop out here due to nasty clang bug https://github.com/llvm/llvm-project/issues/63897 */ \
    /* must do awful stuff to workaround differences in where gcc and clang allow these directives to go */ \
    do { \
        LIBASSERT_WARNING_PRAGMA_PUSH_CLANG \
        LIBASSERT_WARNING_PRAGMA_PUSH_MSVC \
        LIBASSERT_IGNORE_UNUSED_VALUE \
        LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_CLANG \
        LIBASSERT_WARNING_PRAGMA_PUSH_GCC \
        LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_GCC \
        auto libassert_decomposer = ::libassert::detail::expression_decomposer( \
            libassert::detail::expression_decomposer{} << expr \
        ); \
        LIBASSERT_WARNING_PRAGMA_POP_GCC \
        LIBASSERT_CHECK_EXPR_TYPE_AS_BOOLEAN(expr); \
        if(LIBASSERT_STRONG_EXPECT(!static_cast<bool>(libassert_decomposer.get_value()), 0)) { \
            libassert::ERROR_ASSERTION_FAILURE_IN_CONSTEXPR_CONTEXT(); \
            LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL(); \
            failaction \
            LIBASSERT_STATIC_DATA(name, ::libassert::assert_type::type, #expr, __VA_ARGS__) \
            if constexpr(sizeof libassert_decomposer > 32) { \
                ::libassert::detail::process_assert_fail( \
                    libassert_decomposer, \
                    libassert_params \
                    LIBASSERT_VA_ARGS(__VA_ARGS__) LIBASSERT_PRETTY_FUNCTION_ARG \
                ); \
            } else { \
                /* std::move it to assert_fail_m, will be moved back to r */ \
                ::libassert::detail::process_assert_fail_n( \
                    std::move(libassert_decomposer), \
                    libassert_params \
                    LIBASSERT_VA_ARGS(__VA_ARGS__) LIBASSERT_PRETTY_FUNCTION_ARG \
                ); \
            } \
        } \
        LIBASSERT_WARNING_PRAGMA_POP_MSVC \
        LIBASSERT_WARNING_PRAGMA_POP_CLANG \
    } while(0) \

#else // __cplusplus

#define LIBASSERT_INVOKE(expr, name, type, failaction, ...) \
    /* must push/pop out here due to nasty clang bug https://github.com/llvm/llvm-project/issues/63897 */ \
    /* must do awful stuff to workaround differences in where gcc and clang allow these directives to go */ \
    do { \
        LIBASSERT_WARNING_PRAGMA_PUSH_CLANG \
        LIBASSERT_WARNING_PRAGMA_PUSH_MSVC \
        LIBASSERT_IGNORE_UNUSED_VALUE \
        LIBASSERT_CHECK_EXPR_TYPE_AS_BOOLEAN(expr); \
        if(!(expr)) { \
            LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL(); \
            failaction \
			(void)libassert_detail_primitive_assert_impl( \
					libassert_## type ##_type, \
					#expr, \
					name, __FILE__, __LINE__, LIBASSERT_PFUNC  \
					__VA_OPT__(,) __VA_ARGS__, NULL \
			); \
        } \
        LIBASSERT_WARNING_PRAGMA_POP_MSVC \
        LIBASSERT_WARNING_PRAGMA_POP_CLANG \
    } while(0) \

#endif // __cplusplus

#endif // !LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS

#if defined __cplusplus

#define LIBASSERT_INVOKE_PANIC(name, type, ...) \
    do { \
        libassert::ERROR_ASSERTION_FAILURE_IN_CONSTEXPR_CONTEXT(); \
        LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL(); \
        LIBASSERT_STATIC_DATA(name, libassert::assert_type::type, "", __VA_ARGS__) \
        libassert::detail::process_panic( \
            libassert_params \
            LIBASSERT_VA_ARGS(__VA_ARGS__) LIBASSERT_PRETTY_FUNCTION_ARG \
        ); \
    } while(0) \

#else // __cplusplus

#define LIBASSERT_INVOKE_PANIC(name, type, ...) \
    do { \
        LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL(); \
        LIBASSERT_STATIC_DATA(name, libassert_## type ##_type, "", __VA_ARGS__) \
        libassert_process_panic( \
            libassert_params LIBASSERT_PFUNC  \
            LIBASSERT_PRETTY_FUNCTION_ARG, \
			0 ## __VA_OPT__(1,) __VA_ARGS__  \
        ); \
    } while(0) \

#endif // __cplusplus

// Workaround for gcc bug 105734 / libassert bug #24
#define LIBASSERT_DESTROY_DECOMPOSER libassert_decomposer.~expression_decomposer() /* NOLINT(bugprone-use-after-move,clang-analyzer-cplusplus.Move) */

#if LIBASSERT_IS_GCC
 #if __GNUC__ == 12 && __GNUC_MINOR__ == 1
  LIBASSERT_BEGIN_NAMESPACE
  namespace detail {
      template<typename T> constexpr void destroy(T& t) {
          t.~T();
      }
  }
  LIBASSERT_END_NAMESPACE
  #undef LIBASSERT_DESTROY_DECOMPOSER
  #define LIBASSERT_DESTROY_DECOMPOSER libassert::detail::destroy(libassert_decomposer)
 #endif
#endif // LIBASSERT_IS_GCC

#if LIBASSERT_IS_CLANG || LIBASSERT_IS_GCC
 // Extra set of parentheses here because clang treats __extension__ as a low-precedence unary operator which interferes
 // with decltype(auto) in an expression like decltype(auto) x = __extension__ ({...}).y;
 #define LIBASSERT_STMTEXPR(B, R) (__extension__ ({ B R }))
 #define LIBASSERT_STATIC_CAST_TO_BOOL(x) static_cast<bool>(x)
#else
 #define LIBASSERT_STMTEXPR(B, R) [&](const char* libassert_msvc_pfunc) { B return R }(LIBASSERT_PFUNC)
 // Workaround for msvc bug
 #define LIBASSERT_STATIC_CAST_TO_BOOL(x) libassert::detail::static_cast_to_bool(x)

#if defined __cplusplus

 LIBASSERT_BEGIN_NAMESPACE
 namespace detail {
     template<typename T> constexpr bool static_cast_to_bool(T&& t) {
         return static_cast<bool>(t);
     }
 }
 LIBASSERT_END_NAMESPACE

#endif // __cplusplus

#endif // LIBASSERT_IS_CLANG || LIBASSERT_IS_GCC

#if defined __cplusplus

#if !LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS

#define LIBASSERT_INVOKE_VAL(expr, doreturn, check_expression, name, type, failaction, ...) \
    /* must push/pop out here due to nasty clang bug https://github.com/llvm/llvm-project/issues/63897 */ \
    /* must do awful stuff to workaround differences in where gcc and clang allow these directives to go */ \
    LIBASSERT_WARNING_PRAGMA_PUSH_CLANG \
    LIBASSERT_WARNING_PRAGMA_PUSH_MSVC \
    LIBASSERT_IGNORE_UNUSED_VALUE \
    LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_CLANG \
    LIBASSERT_STMTEXPR( \
        LIBASSERT_WARNING_PRAGMA_PUSH_GCC \
        LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_GCC \
        auto libassert_decomposer = libassert::detail::expression_decomposer( \
            libassert::detail::expression_decomposer{} << expr \
        ); \
        LIBASSERT_WARNING_PRAGMA_POP_GCC \
        /* LIBASSERT_CHECK_EXPR_TYPE_AS_BOOLEAN(expr); */ \
        LIBASSERT_CHECK_EXPR_TYPE_AS_BOOLEAN(check_expression); \
        decltype(auto) libassert_value = libassert_decomposer.get_value(); \
        constexpr bool libassert_ret_lhs = libassert_decomposer.ret_lhs(); \
        if constexpr(check_expression) { \
            /* For *some* godforsaken reason static_cast<bool> causes an ICE in MSVC here. Something very specific */ \
            /* about casting a decltype(auto) value inside a lambda. Workaround is to put it in a wrapper. */ \
            /* https://godbolt.org/z/Kq8Wb6q5j https://godbolt.org/z/nMnqnsMYx */ \
            if(LIBASSERT_STRONG_EXPECT(!LIBASSERT_STATIC_CAST_TO_BOOL(libassert_value), 0)) { \
                libassert::ERROR_ASSERTION_FAILURE_IN_CONSTEXPR_CONTEXT(); \
                LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL(); \
                failaction \
                LIBASSERT_STATIC_DATA(name, libassert::assert_type::type, #expr, __VA_ARGS__) \
                if constexpr(sizeof libassert_decomposer > 32) { \
                    libassert::detail::process_assert_fail( \
                        libassert_decomposer, \
                        libassert_params \
                        LIBASSERT_VA_ARGS(__VA_ARGS__) LIBASSERT_INVOKE_VAL_PRETTY_FUNCTION_ARG \
                    ); \
                } else { \
                    /* std::move it to assert_fail_m, will be moved back to r */ \
                    auto libassert_r = libassert::detail::process_assert_fail_m( \
                        std::move(libassert_decomposer), \
                        libassert_params \
                        LIBASSERT_VA_ARGS(__VA_ARGS__) LIBASSERT_INVOKE_VAL_PRETTY_FUNCTION_ARG \
                    ); \
                    /* can't move-assign back to decomposer if it holds reference members */ \
                    LIBASSERT_DESTROY_DECOMPOSER; \
                    new (&libassert_decomposer) libassert::detail::expression_decomposer(std::move(libassert_r)); \
                } \
            } \
        }, \
        /* Note: std::launder needed in 17 in case of placement new / move shenanigans above */ \
        /* https://timsong-cpp.github.io/cppwp/n4659/basic.life#8.3 */ \
        /* Note: Somewhat relying on this call being inlined so inefficiency is eliminated */ \
        libassert::detail::get_expression_return_value< \
            doreturn LIBASSERT_COMMA \
            libassert_ret_lhs LIBASSERT_COMMA \
            std::is_lvalue_reference_v<decltype(libassert_value)> \
        >(libassert_value, *std::launder(&libassert_decomposer)); \
    ) LIBASSERT_IF(doreturn)(.value,) \
    LIBASSERT_WARNING_PRAGMA_POP_MSVC \
    LIBASSERT_WARNING_PRAGMA_POP_CLANG

#else // !LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS

#define LIBASSERT_INVOKE_VAL(expr, doreturn, check_expression, name, type, failaction, ...) \
    /* must push/pop out here due to nasty clang bug https://github.com/llvm/llvm-project/issues/63897 */ \
    /* must do awful stuff to workaround differences in where gcc and clang allow these directives to go */ \
    LIBASSERT_WARNING_PRAGMA_PUSH_CLANG \
    LIBASSERT_WARNING_PRAGMA_PUSH_MSVC \
    LIBASSERT_IGNORE_UNUSED_VALUE \
    LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_CLANG \
    LIBASSERT_STMTEXPR( \
        LIBASSERT_CHECK_EXPR_TYPE_AS_BOOLEAN(expr); \
        LIBASSERT_CHECK_EXPR_TYPE_AS_BOOLEAN(check_expression); \
        /* For *some* godforsaken reason static_cast<bool> causes an ICE in MSVC here. Something very specific */ \
        /* about casting a decltype(auto) value inside a lambda. Workaround is to put it in a wrapper. */ \
        /* https://godbolt.org/z/Kq8Wb6q5j https://godbolt.org/z/nMnqnsMYx */ \
        bool libassert_check_fail = !LIBASSERT_STATIC_CAST_TO_BOOL(expr); \
        if(LIBASSERT_STRONG_EXPECT(libassert_check_fail, 0)) { \
            libassert::ERROR_ASSERTION_FAILURE_IN_CONSTEXPR_CONTEXT(); \
            LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL(); \
            failaction \
            LIBASSERT_STATIC_DATA(name, libassert::assert_type::type, #expr, __VA_ARGS__) \
            libassert::detail::process_assert_fail_primitive( \
                libassert_params \
                LIBASSERT_VA_ARGS(__VA_ARGS__) LIBASSERT_INVOKE_VAL_PRETTY_FUNCTION_ARG \
            ); \
        }, \
        libassert_check_fail; ); \
    ) LIBASSERT_IF(doreturn)(,) \
    LIBASSERT_WARNING_PRAGMA_POP_MSVC \
    LIBASSERT_WARNING_PRAGMA_POP_CLANG

#endif // !LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS

#else // __cplusplus

#define LIBASSERT_INVOKE_VAL(expr, doreturn, check_expression, name, type, failaction, ...) \
    /* must push/pop out here due to nasty clang bug https://github.com/llvm/llvm-project/issues/63897 */ \
    /* must do awful stuff to workaround differences in where gcc and clang allow these directives to go */ \
    LIBASSERT_WARNING_PRAGMA_PUSH_CLANG \
    LIBASSERT_WARNING_PRAGMA_PUSH_MSVC \
    LIBASSERT_IGNORE_UNUSED_VALUE \
    LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_CLANG \
    LIBASSERT_STMTEXPR( \
        LIBASSERT_WARNING_PRAGMA_PUSH_GCC \
        LIBASSERT_EXPRESSION_DECOMP_WARNING_PRAGMA_GCC \
        auto libassert_decomposer = libassert::detail::expression_decomposer( \
            libassert::detail::expression_decomposer{} << expr \
        ); \
        LIBASSERT_WARNING_PRAGMA_POP_GCC \
        /* LIBASSERT_CHECK_EXPR_TYPE_AS_BOOLEAN(expr); */ \
        LIBASSERT_CHECK_EXPR_TYPE_AS_BOOLEAN(check_expression); \
        decltype(auto) libassert_value = libassert_decomposer.get_value(); \
        constexpr bool libassert_ret_lhs = libassert_decomposer.ret_lhs(); \
        if constexpr(check_expression) { \
            /* For *some* godforsaken reason static_cast<bool> causes an ICE in MSVC here. Something very specific */ \
            /* about casting a decltype(auto) value inside a lambda. Workaround is to put it in a wrapper. */ \
            /* https://godbolt.org/z/Kq8Wb6q5j https://godbolt.org/z/nMnqnsMYx */ \
            if(LIBASSERT_STRONG_EXPECT(!LIBASSERT_STATIC_CAST_TO_BOOL(libassert_value), 0)) { \
                libassert::ERROR_ASSERTION_FAILURE_IN_CONSTEXPR_CONTEXT(); \
                LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL(); \
                failaction \
                LIBASSERT_STATIC_DATA(name, libassert::assert_type::type, #expr, __VA_ARGS__) \
                if constexpr(sizeof libassert_decomposer > 32) { \
                    libassert::detail::process_assert_fail( \
                        libassert_decomposer, \
                        libassert_params \
                        LIBASSERT_VA_ARGS(__VA_ARGS__) LIBASSERT_INVOKE_VAL_PRETTY_FUNCTION_ARG \
                    ); \
                } else { \
                    /* std::move it to assert_fail_m, will be moved back to r */ \
                    auto libassert_r = libassert::detail::process_assert_fail_m( \
                        std::move(libassert_decomposer), \
                        libassert_params \
                        LIBASSERT_VA_ARGS(__VA_ARGS__) LIBASSERT_INVOKE_VAL_PRETTY_FUNCTION_ARG \
                    ); \
                    /* can't move-assign back to decomposer if it holds reference members */ \
                    LIBASSERT_DESTROY_DECOMPOSER; \
                    new (&libassert_decomposer) libassert::detail::expression_decomposer(std::move(libassert_r)); \
                } \
            } \
        }, \
        /* Note: std::launder needed in 17 in case of placement new / move shenanigans above */ \
        /* https://timsong-cpp.github.io/cppwp/n4659/basic.life#8.3 */ \
        /* Note: Somewhat relying on this call being inlined so inefficiency is eliminated */ \
        libassert::detail::get_expression_return_value< \
            doreturn LIBASSERT_COMMA \
            libassert_ret_lhs LIBASSERT_COMMA \
            std::is_lvalue_reference_v<decltype(libassert_value)> \
        >(libassert_value, *std::launder(&libassert_decomposer)); \
    ) LIBASSERT_IF(doreturn)(.value,) \
    LIBASSERT_WARNING_PRAGMA_POP_MSVC \
    LIBASSERT_WARNING_PRAGMA_POP_CLANG

#endif // __cplusplus


#if defined __cplusplus

// same as LIBASSERT_INVOKE, but now the entire macro is an expression rather than a statement type.
#define LIBASSERT_INVOKE_EXPRESSION(expr, name, type, ...) \
        (static_cast<bool>(expr) ? \
		((void)0) : \
		(libassert_breakpoint_if_debugger_present(), \
		(void)::libassert::detail::libassert_detail_primitive_assert_implpp( \
				::libassert::assert_type::type, \
				#expr, \
				name, __FILE__, __LINE__, LIBASSERT_PFUNC, \
				::libassert::detail::format(__VA_ARGS__) \
			) \
        ))

#else // __cplusplus

// same as LIBASSERT_INVOKE, but now the entire macro is an expression rather than a statement type.
#define LIBASSERT_INVOKE_EXPRESSION(expr, name, type, ...) \
        (!!(expr) ? \
		((void)0) : \
		(libassert_breakpoint_if_debugger_present(), \
		(void)libassert_detail_primitive_assert_impl( \
				libassert_## type ##_type, \
				#expr, \
				name, __FILE__, __LINE__, LIBASSERT_PFUNC  \
				__VA_OPT__(,) __VA_ARGS__, NULL \
			) \
        ))

#endif // __cplusplus


#define LIBASSERT_EMPTY_ACTION   LIBASSERT_NOOP_STATEMENT();

#ifdef NDEBUG
 #define LIBASSERT_ASSUME_ACTION LIBASSERT_UNREACHABLE_CALL();
#else
 #define LIBASSERT_ASSUME_ACTION LIBASSERT_EMPTY_ACTION
#endif

// assertion macros

// Debug assert
#ifndef NDEBUG
 #if !defined(LIBASSERT_PREFIX_ASSERTIONS)
  #define LIBASSERT_DEBUG_ASSERT(expr, ...) LIBASSERT_INVOKE(expr, "DEBUG_ASSERT", debug_assertion, LIBASSERT_EMPTY_ACTION, __VA_ARGS__)
 #else
  #define LIBASSERT_DEBUG_ASSERT(expr, ...) LIBASSERT_INVOKE_EXPRESSION(expr, "DEBUG_ASSERT", debug_assertion, __VA_ARGS__)
 #endif
#else
 #define LIBASSERT_DEBUG_ASSERT(expr, ...) (void)0
#endif

// Assert
#if !defined(LIBASSERT_PREFIX_ASSERTIONS)
 #define LIBASSERT_ASSERT(expr, ...) LIBASSERT_INVOKE(expr, "ASSERT", assertion, LIBASSERT_EMPTY_ACTION, __VA_ARGS__)
#else
 #define LIBASSERT_ASSERT(expr, ...) LIBASSERT_INVOKE_EXPRESSION(expr, "ASSERT", assertion, __VA_ARGS__)
#endif
// lowercase version intentionally done outside of the include guard here

// Assume
#if !defined(LIBASSERT_PREFIX_ASSERTIONS)
 #define LIBASSERT_ASSUME(expr, ...) LIBASSERT_INVOKE(expr, "ASSUME", assumption, LIBASSERT_ASSUME_ACTION, __VA_ARGS__)
#else
 #define LIBASSERT_ASSUME(expr, ...) LIBASSERT_INVOKE_EXPRESSION(expr, "ASSUME", assumption, __VA_ARGS__)
#endif

// Panic
#define LIBASSERT_PANIC(...) LIBASSERT_INVOKE_PANIC("PANIC", panic, __VA_ARGS__)

// Unreachable
#ifndef NDEBUG
 #define LIBASSERT_UNREACHABLE(...) LIBASSERT_INVOKE_PANIC("UNREACHABLE", unreachable, __VA_ARGS__)
#else
 #define LIBASSERT_UNREACHABLE(...) LIBASSERT_UNREACHABLE_CALL()
#endif

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
  #define LIBASSERT_USER_STATIC_ASSERT(cond, constant) static_assert(cond, constant)
  #define LIBASSERT_USER_STATIC_ASSERT_BACKUP_MSG(cond, msg, constant) static_assert(cond, constant)
  #define USER_STATIC_ASSERT(cond, constant) static_assert(cond, constant)
  #define USER_STATIC_ASSERT_BACKUP_MSG(cond, msg, constant) static_assert(cond, constant)
#else
  #define LIBASSERT_USER_STATIC_ASSERT(cond, constant) static_assert(cond)
  #define LIBASSERT_USER_STATIC_ASSERT_BACKUP_MSG(cond, msg, constant) static_assert(cond, msg)
  #define USER_STATIC_ASSERT(cond, constant) static_assert(cond)
  #define USER_STATIC_ASSERT_BACKUP_MSG(cond, msg, constant) static_assert(cond, msg)
#endif

#endif // LIBASSERT_HPP

