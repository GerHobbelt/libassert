
#include <libassert/assert.h>

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


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
LIBASSERT_EXPORT void libassert_detail_primitive_assert_impl(libassert_assert_type_t mode, const char* expr, const char* signature, const char* file, const int line, const char* function, const char* message, ...) {
	using namespace ::libassert;

	source_location location{ function, file, line };

	char *nfmt = nullptr;

	/* best effort to even work in out of memory situations */
	if (message != nullptr && strchr(message, '%') != nullptr) {
		va_list ap;
		va_start(ap, message);
		if (libassert_vasprintf(&nfmt, message, ap) <= 0) {
			free(nfmt);
			nfmt = nullptr;
		}
		va_end(ap);
	}

	detail::primitive_assert_impl(static_cast<::libassert::assert_type>(mode), expr, signature, location, nfmt ? nfmt : message ? message : "");

	free(nfmt);
}






/* Avoid calling asprintf, in case our compiler doesn't support it.
 * Vaguely unhappy about relying on vsnprintf, but... */
extern "C"
LIBASSERT_EXPORT int libassert_asprintf(char **ret, const char *format, ...)
{
	va_list va;
	int n;
	int n2;

	va_start(va, format);
	n = vsnprintf(nullptr, 0, format, va);
	va_end(va);
	if (n < 0)
		return n;

	*ret = (char *)malloc(n+1);
	if (*ret == nullptr)
		return -1;

	va_start(va, format);
	n2 = vsnprintf(*ret, n + 1, format, va);
	va_end(va);

	return n2;
}

/* Avoid calling vasprintf, in case our compiler doesn't support it.
 * Vaguely unhappy about relying on vsnprintf, but... */
extern "C"
LIBASSERT_EXPORT int libassert_vasprintf(char **ret, const char *format, va_list ap)
{
	int n;
	va_list ap2;
	va_copy(ap2, ap);

	n = vsnprintf(nullptr, 0, format, ap);
	if (n < 0) {
		va_end(ap2);
		return n;
	}

	*ret = (char *)malloc(n+1);
	if (*ret == nullptr) {
		va_end(ap2);
		return -1;
	}

	n = vsnprintf(*ret, n + 1, format, ap2);
	va_end(ap2);

	return n;
}

