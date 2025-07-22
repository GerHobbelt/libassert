
// test whether `#include <cassert>` indeed would load our libassert incantation, given the proper set of include paths for the compiler...

#include <cassert>

#ifndef LIBASSERT_ASSERT
#error "libassert include paths are not included or don't have precedence over system's assert.h + cassert header files."
#endif

#include "c-code-test.h"

static LIBASSERT_ATTR_NOINLINE float foopp(void) {
	return 2.5f;
}

extern "C"
void cassert_include_test(void) {
	int x = 4;
	LIBASSERT_DEBUG_ASSERT(x % 2 == 0);
	LIBASSERT_ASSERT(1 + 1 != 3);

	float f = LIBASSERT_DEBUG_ASSERT_VAL(foopp());
	assert(f == 2.5f);
	float &r = f;
	float g = LIBASSERT_DEBUG_ASSERT_VAL(r);
	assert(g == 2.5f);
	float *p = &f;
	auto h = LIBASSERT_DEBUG_ASSERT_VAL(p);
	assert(h == &f);

	LIBASSERT_DEBUG_ASSERT(false);

	LIBASSERT_ASSERT(x < 20, "foobar");
}

