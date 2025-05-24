
#define LIBASSERT_LOWERCASE

#include <libassert/assert.hpp>

#include "c-code-test.h"

#include "monolithic_examples.h"

#ifndef FALSE
#define FALSE 0
#endif

#define ASSERT_EQ(e1, e2, ...)		debug_assert(((e1) == (e2)), "ASSERT_EQ assertion failed", (e1), (e2) __VA_OPT__(,) __VA_ARGS__)

static float foo(void) {
	return 2.5f;
}

#if defined(BUILD_MONOLITHIC)
#define main    assert_c_code_test_main
#endif

int main(void) {
	int x = 4;
	DEBUG_ASSERT(x % 2 == 0);
	ASSERT(1 + 1 != 3);

#if 0
	DEBUG_ASSERT_VAL(foo());
#endif
	assert(foo() == 2.5f);

	debug_assert(FALSE);

	LIBASSERT_ASSERT(x < 20, "foobar");

	ASSERT_EQ(1, 2);

	assert_h_include_test();
	cassert_include_test();

	assert_h_include_primitive_test();
	cassert_include_primitive_test();

	return 0;
}

