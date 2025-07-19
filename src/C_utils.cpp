
#include <libassert/assert.hpp>

// A nasty `using` statement, which *fakes* the C type `libassert_assert_type_t`.
//
// We did not include this `using` statement in the header file itself as then we would be cluttering global namespace with
// **non-prefixed identifiers** such as `assertion` and `debug_assertion` and the whole intent of the separate C typedef `libassert_assert_type_t`
// is to have *namespace-prefixed* enum constants in any C language files so there's zero risk of enum name collisions!
//
// This hack also implies that we must tread carefully and make sure both libassert_detail_primitive_assert_impl() implementation, usage and prototype
// match up; the implementation is an almost-clone of C++ `libassert_detail_primitive_assert_implpp()`...
//
// Lucky for us, C does not check for exact type match of function parameters: this `using` statement produces a *type* that *technically* is not identical
// to the C enum `libassert_assert_type_t`, while both MUST HAVE the same constants (or this trick will fail horribly!)
//
using libassert_assert_type_t = ::libassert::assert_type;

extern "C"
[[noreturn]] LIBASSERT_EXPORT void libassert_detail_primitive_assert_impl(libassert_assert_type_t mode, const char* expr, const char* signature, const char* file, const int line, const char* function, const char* message) {
	using namespace ::libassert;

	source_location location{ function, file, line };
	detail::primitive_assert_impl(static_cast<::libassert::assert_type>(mode), expr, signature, location, message);
}

