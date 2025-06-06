
// test whether `#include <assert.h>` indeed would load our libassert incantation, given the proper set of include paths for the compiler...

#include <assert.h>

#ifndef LIBASSERT_ASSERT
#error "libassert include paths are not included or don't have precedence over system's assert.h + cassert header files."
#endif

#include <stdlib.h>

#include "c-code-test.h"

static float fooc(void) {
	return 2.5f;
}

void assert_h_include_test(void) {
	int x = 4;
	DEBUG_ASSERT(x % 2 == 0);
	ASSERT(1 + 1 != 3);

	float f = DEBUG_ASSERT_VAL(fooc());
	assert(f == 2.5f);

	debug_assert(!!0);
	// ^^^ Using `!!` operator because otherwise: error C2338: static_assert failed: 'assertion expression result type must be boolean: implicit type conversions are NOT accepted.'

	LIBASSERT_ASSERT(x < 20, "foobar");

	LIBASSERT_ASSERT(1 == 2);
}

