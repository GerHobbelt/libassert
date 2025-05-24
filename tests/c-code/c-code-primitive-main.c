
#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS

#include <libassert/assert.hpp>

#include "c-code-test.h"

#include "monolithic_examples.h"

static float foo(void) {
	return 2.5f;
}

#if defined(BUILD_MONOLITHIC)
#define main    assert_c_code_primitive_test_main
#endif

int main(void) {
	int x = 4;
	DEBUG_ASSERT(x % 2 == 0);
	ASSERT(1 + 1 != 3);

	DEBUG_ASSERT_VAL();
	assert(foo() == 2.5f);

	debug_assert(false);

	LIBASSERT_ASSERT(x < 20, "foobar");

	ASSERT_EQ(1, 2);

	assert_h_include_test();
	cassert_include_test();

	return 0;
}

