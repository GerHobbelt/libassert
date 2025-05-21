
#include <assert.h>
#include <libassert/assert.hpp>

#include "monolithic_examples.h"

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

	float f = DEBUG_ASSERT_VAL(foo());
	assert(f == 2.5f);

	debug_assert(false);

	LIBASSERT_ASSERT(x < 20, "foobar");

	ASSERT_EQ(1, 2);

	return 0;
}

