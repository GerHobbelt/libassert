
// test whether `#include <cassert>` indeed would load our libassert incantation, given the proper set of include paths for the compiler...

#define LIBASSERT_ASSERT_IS_EXPRESSION

#define LIBASSERT_PREFIX_ASSERTIONS                1
#include <cassert>

#ifndef LIBASSERT_ASSERT
#error "libassert include paths are not included or don't have precedence over system's assert.h + cassert header files."
#endif

#include "c-code-test.h"


static LIBASSERT_ATTR_NOINLINE float foopp(void) {
	return 2.5f;
}

extern "C"
void cassert_include_expression_test(void) {
	int x = 4;
	DEBUG_ASSERT(x % 2 == 0);
	ASSERT(1 + 1 != 3);

	DEBUG_ASSERT(foopp());
	float f = foopp();
	assert(f == 2.5f);

	assert(f == 2.5f), assert(x > 5);

#if defined(debug_assert)
	#error "debug_assert was NOT expected to be defined: LIBASSERT_LOWERCASE=0"
#endif

	LIBASSERT_ASSERT(x < 20, "foobar");
}

