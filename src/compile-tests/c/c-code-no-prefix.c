
#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS      1
//#define LIBASSERT_PREFIX_ASSERTIONS                  1
//#define LIBASSERT_LOWERCASE                          1

#include <libassert/assert.h>

#include "compile-tests/code-compile-testset.h"

#ifndef FALSE
#define FALSE 0
#endif

#define ASSERT_EQ(e1, e2)		LIBASSERT_DEBUG_ASSERT(((e1) == (e2)), "ASSERT_EQ assertion failed: %d != %d", (int)(e1), (int)(e2))

static float foo(void) {
	return 2.5f;
}

int assert_c_code_primitive_style_test(void) {
	int x = 4;
	LIBASSERT_DEBUG_ASSERT(x % 2 == 0, "(msg)");
	LIBASSERT_ASSERT(1 + 1 != 3, "(msg)");

	int a = (LIBASSERT_DEBUG_ASSERT_VAL(foo()), LIBASSERT_DEBUG_ASSERT_VAL(x > 7), 11);

	LIBASSERT_ASSERT(foo() == 2.5f);

	LIBASSERT_DEBUG_ASSERT(FALSE, "(msg)");

	LIBASSERT_ASSERT(x < 20, "foobar");

	ASSERT_EQ(a, x);
}

