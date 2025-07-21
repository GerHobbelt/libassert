
// test whether `#include <assert.h>` indeed would load our libassert incantation, given the proper set of include paths for the compiler...

#include <cassert>

#ifndef LIBASSERT_ASSERT
#error "libassert include paths are not included or don't have precedence over system's assert.h + cassert header files."
#endif

#ifndef LIBASSERT_OFFER_SYSTEM_ASSERT_REPLACEMENT
#error "libassert include path didn't have precedence over system's assert.h + cassert header files."
#endif

#if LIBASSERT_PREFIX_ASSERTIONS != 0
#error "LIBASSERT_LIBASSERT_PREFIX_ASSERTIONS: libassert did not set the expected default."
#endif

#if LIBASSERT_LOWERCASE != 0
#error "LIBASSERT_LOWERCASE: libassert did not set the expected default."
#endif

#if LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS != 0
#error "LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS: libassert did not set the expected default."
#endif

#include <stdlib.h>

#include "compile-tests/code-compile-testset.h"

static float fooc(void) {
	return 2.5f;
}

void libassert_cppt_assert_h_include_test(void) {
	int x = 4;
	LIBASSERT_DEBUG_ASSERT(x % 2 == 0);
	LIBASSERT_ASSERT(1 + 1 != 3);

	float f = /* LIBASSERT_DEBUG_ASSERT_VAL */ (fooc());
	assert(f == 2.5f);

	LIBASSERT_DEBUG_ASSERT(!!0);
	// ^^^ Using `!!` operator because otherwise: error C2338: static_assert failed: 'assertion expression result type must be boolean: implicit type conversions are NOT accepted.'
	LIBASSERT_DEBUG_ASSERT(0);

	LIBASSERT_ASSERT(x < 20, "foobar");

	LIBASSERT_ASSERT(1 == 2);

	assert(x == 4, "(message)");

	std::string s = libassert::detail::format("(message: %s %s @ %d)", "kukurutz", "shoobidoosah", 777);

	assert(x + f < 7.0, "(message: %s %s @ %d)", "kukurutz", "shoobidoosah", 777);

	assert(x + f * 11 == 7, s);
}

