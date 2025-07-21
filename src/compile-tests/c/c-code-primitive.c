
#define LIBASSERT_ASSERT_IS_EXPRESSION         1
#define LIBASSERT_LOWERCASE                    1

#include <libassert/assert.h>

#include "compile-tests/code-compile-testset.h"

#ifndef FALSE
#define FALSE 0
#endif

#define ASSERT_EQ(e1, e2)		LIBASSERT_PRIMITIVE_DEBUG_ASSERT(((e1) == (e2)), "ASSERT_EQ assertion failed: %d != %d", (e1), (e2))

static float foo(void) {
	return 2.5f;
}

void assert_primitive_style_test(void) {
	int x = 4;
	LIBASSERT_PRIMITIVE_DEBUG_ASSERT(x % 2 == 0, "(msg)");
	LIBASSERT_PRIMITIVE_ASSERT(1 + 1 != 3, "(msg)");

	LIBASSERT_PRIMITIVE_ASSERT(x % 2 == 0);
	LIBASSERT_PRIMITIVE_DEBUG_ASSERT(1 + 1 != 3);
	LIBASSERT_ASSERT(x % 5 == 0);
	LIBASSERT_DEBUG_ASSERT(1 + 7 != 9);

	LIBASSERT_PRIMITIVE_DEBUG_ASSERT(foo());

	LIBASSERT_PRIMITIVE_ASSERT(foo() == 2.5f);

	LIBASSERT_PRIMITIVE_ASSERT(foo() == 2.5f), LIBASSERT_PRIMITIVE_ASSERT(x > 5);

	debug_assert(FALSE, "(msg)");

	LIBASSERT_PRIMITIVE_ASSERT(x < 20, "foobar");

	ASSERT_EQ(1, 2);
}

