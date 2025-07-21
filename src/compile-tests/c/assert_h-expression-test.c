
// test whether `#include <assert.h>` indeed would load our libassert incantation, given the proper set of include paths for the compiler...

#define LIBASSERT_ASSERT_IS_EXPRESSION            1

#include <assert.h>

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

void libassert_ct_assert_as_expression_test(void) {
	int x = 4;
	float f = 2.5f;
	int a = (assert(f == 2.5f), x);
	int b = (assert(a == 4, "(message)"), 1);

	char* s = NULL;
	libassert_asprintf(&s, "(message: %s %s @ %d)", "kukurutz", "shoobidoosah", 777);

	int c = (assert(a + f < 7.0, "(message: %s %s @ %d)", "kukurutz", "shoobidoosah", 777), 2);

	assert(a + b + c == 7, s);

	free(s);
}

