#ifndef LIBASSERT_EXPRESSION_TYPECHECK_HPP
#define LIBASSERT_EXPRESSION_TYPECHECK_HPP

#if defined __cplusplus

#include <type_traits>
#include <utility>

#endif // __cplusplus

#include <libassert/platform.hpp>
#include <libassert/utilities.hpp>

// =====================================================================================================================
// || Expression compile-time typechecking micro-library                                                              ||
// =====================================================================================================================

// C++11 and above provides typechecking for expressions: https://stackoverflow.com/questions/4021981/use-static-assert-to-check-types-passed-to-macro
//
// We use this ability to check whether userland code has been written using BOOLEAN expressions for their assertion checks:
// yes, that sounds a little pedantic, but we've uncovered several subtle yet nasty bugs in production code by being
// finicky about what we tolerate in terms of "implicit conversions" to boolean:
//
//    assert(false);
//
// is cool, and we MAY be lenient when it comes to 'int' based pre- and postcondition expressions, such as:
//
//    assert(0); // should never get here
//
// but that's already something to frown upon.
//
//    assert(!"Should never get here.");
//
// is a classic that happens to be a *boolean* expression, thanks to the `!` operator, and we're fine with these,
// but writing lazy stuff like
//
//     assert(internal_library_call(arg1, arg2) - second_call(a2, a3));
//
// should get you stomped on your big toe, as this is uselessly lazy. Write
//
//     assert(0 == internal_library_call(arg1, arg2) - second_call(a2, a3));
//
// instead. That's 5 more keypresses and ZERO mental effort for any code reviewer at any time in the future, including you yourselves.
//
// This is why we have these compile-time checks provided here: to ensure your assertions/assumption-checks are
// *fully qualified boolean expressions*, stripped of any "implied" null/zero/false type conversion.
//
// I myself am among many who are prone to write
//
//     assert(ptr);
//
// and that is now also a thing of the past. Write
//
//     assert(ptr == nullptr);
//
// instead. This makes the assert (and the expected types *inside the expression* bloody obvious; once we introduced a previous
// incantation (using C++ function polymorphism and `delete`d function specifications) about 2 years ago, several bugs inside
// these assertion expressions were uncovered (also thanks to our compiler runs having been dialed up to the pedantic max in warning level!),
// especially around the time when internal library function interfaces were in flux during the initial development of those libraries:
// *implicit* conversions to boolean are a *bad* thing then, and we should all be aware of that (as they help hide interface changes
// that impact the code behaviour and should have been dealt with in the using code already, but there's always that one spot where
// you forget to follow up...)
//
// Typechecking the expressions fed to the assertion library WILL help uncover such mistakes/omisions: it's not a sure-fire way, but
// everything helps here!
// 

#if defined __cplusplus

#define LIBASSERT_CHECK_EXPR_TYPE_AS_BOOLEAN(expr) \
	static_assert(std::is_same<std::remove_cv<decltype(expr)>::type, bool>::value, \
		"assertion expression result type must be boolean: implicit type conversions are NOT accepted.")

#else // __cplusplus

#define LIBASSERT_CHECK_EXPR_TYPE_AS_BOOLEAN(expr) \
	(void)(0)

#endif // __cplusplus

#endif
