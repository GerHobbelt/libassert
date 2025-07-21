
#define LIBASSERT_ASSERT_IS_EXPRESSION         1
#define LIBASSERT_LOWERCASE                    1

#include <libassert/assert.h>

#include "compile-tests/code-compile-testset.h"

#ifndef FALSE
#define FALSE 0
#endif

#define ASSERT_EQ(e1, e2)		debug_assert(((e1) == (e2)), "ASSERT_EQ assertion failed: %d != %d", (int)(e1), (int)(e2))

static float foo(void) {
	return 2.5f;
}

void assert_expression_test(void) {
	int x = 4;
	debug_assert(x % 2 == 0, "(msg)");
	assert(1 + 1 != 3, "(msg)");

	assert(foo() == 2.5f);

	int a = (assert(foo() == 2.5f), assert(x > 5), 11);

	debug_assert(FALSE, "(msg)");

	debug_assert(foo() == 2.5f);
	debug_assert(x > 5, "(msg: %s)", "arg");

	LIBASSERT_ASSERT(x < 20, "foobar");

	ASSERT_EQ(a, x);
}

