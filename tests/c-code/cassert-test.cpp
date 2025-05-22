
// test whether `#include <cassert>` indeed would load our libassert incantation, given the proper set of include paths for the compiler...

#include <cassert>

#ifndef LIBASSERT_ASSERT
#error "libassert include paths are not included or don't have precedence over system's assert.h + cassert header files."
#endif

#ifndef LIBASSERT_PHASE_3_ALL_DONE
#error "libassert macros vs. codebase epansion process failed; see the assert-macros.h driver file for more info."
#endif

#include "c-code-test.h"

static LIBASSERT_ATTR_NOINLINE float foopp(void) {
	return 2.5f;
}

extern "C"
void cassert_include_test(void) {
	int x = 4;
	DEBUG_ASSERT(x % 2 == 0);
	ASSERT(1 + 1 != 3);

	float f = DEBUG_ASSERT_VAL(foopp());
	assert(f == 2.5f);

	debug_assert(FALSE);

	LIBASSERT_ASSERT(x < 20, "foobar");

	ASSERT_EQ(1, 2);
}

