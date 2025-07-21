
#define LIBASSERT_ASSERT_IS_EXPRESSION         1
#define LIBASSERT_LOWERCASE                    1

#include <libassert/assert.h>

#include "compile-tests/code-compile-testset.h"

#ifndef FALSE
#define FALSE 0
#endif

#define ASSERT_EQ(e1, e2, ...)		debug_assert(((e1) == (e2)), "ASSERT_EQ assertion failed" /* , (e1), (e2) __VA_OPT__(,) __VA_ARGS__ */ )

static float foo(void) {
	return 2.5f;
}

void assert_h_include_expression_test(void) {
	int x = 4;
	LIBASSERT_DEBUG_ASSERT(x % 2 == 0, "(msg)");
	LIBASSERT_ASSERT(1 + 1 != 3, "(msg)");

	LIBASSERT_DEBUG_ASSERT_VAL(foo());

	assert(foo() == 2.5f);

	assert(foo() == 2.5f), assert(x > 5);

	debug_assert(FALSE, "(msg)");

	LIBASSERT_ASSERT(x < 20, "foobar");

	ASSERT_EQ(1, 2);
}

