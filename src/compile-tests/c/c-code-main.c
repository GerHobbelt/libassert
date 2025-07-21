
#include <libassert/assert.h>

#include "compile-tests/code-compile-testset.h"

#ifndef FALSE
#define FALSE 0
#endif

#define ASSERT_EQ(e1, e2)		LIBASSERT_DEBUG_ASSERT(((e1) == (e2)), "ASSERT_EQ assertion failed: %d != %d", (int)(e1), (int)(e2))

static float foo(void) {
	return 2.5f;
}

int assert_c_code_test(void) {
	int x = 4;
	LIBASSERT_DEBUG_ASSERT(x % 2 == 0);
	LIBASSERT_ASSERT(1 + 1 != 3);

	DEBUG_ASSERT_VAL(foo());

	LIBASSERT_ASSERT(foo() == 2.5f);

	LIBASSERT_DEBUG_ASSERT(FALSE, "(msg)");

	LIBASSERT_ASSERT(x < 20, "foobar");

	ASSERT_EQ(1, 2);
}

