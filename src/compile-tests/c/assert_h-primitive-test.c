
// test whether `#include <assert.h>` indeed would load our libassert incantation, given the proper set of include paths for the compiler...

#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS               1
//#define LIBASSERT_PREFIX_ASSERTIONS                           1
//#define LIBASSERT_LOWERCASE                                   1
//#define LIBASSERT_ASSERT_IS_EXPRESSION                        1

#include <assert.h>

#ifndef LIBASSERT_ASSERT
#error "libassert include paths are not included or don't have precedence over system's assert.h + cassert header files."
#endif

#ifndef LIBASSERT_OFFER_SYSTEM_ASSERT_REPLACEMENT
#error "libassert include path didn't have precedence over system's assert.h + cassert header files."
#endif

#if LIBASSERT_PREFIX_ASSERTIONS != 0
#error "LIBASSERT_LIBASSERT_PREFIX_ASSERTIONS: libassert did not set the expected default."
#endif

#if LIBASSERT_LOWERCASE != 0
#error "LIBASSERT_LOWERCASE: libassert did not set the expected default."
#endif

#if LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS != 1
#error "LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS: libassert did not set the expected default."
#endif

#include <stdlib.h>

#include "compile-tests/code-compile-testset.h"


#define ASSERT_EQ(e1, e2)		assert(((e1) == (e2)), "ASSERT_EQ assertion failed: %d != %d", (int)(e1), (int)(e2))

static float foo(void) {
	return 2.5f;
}

void libassert_ct_assert_h_primitive_style_test(void) {
	int x = 4;
	LIBASSERT_PRIMITIVE_DEBUG_ASSERT(x % 3 == 0, "(msg: x = %d)", x);
	LIBASSERT_PRIMITIVE_ASSERT(1 + x != 5, "(msg: x = %d)", x);
	LIBASSERT_PRIMITIVE_ASSERT(x % 2 == 1);
	LIBASSERT_PRIMITIVE_DEBUG_ASSERT(1 + 1 > 3);
	LIBASSERT_DEBUG_ASSERT(x % 3 == 0, "(msg: x = %d)", x);
	LIBASSERT_ASSERT(1 + x != 5, "(msg: x = %d)", x);
	LIBASSERT_ASSERT(x % 5 == 0);
	LIBASSERT_DEBUG_ASSERT(3 * 7 <= x);

	assert(foo() / 5);
	float f = foo();

	assert(foo() == 2.5f);   assert(x > 5);   int a = 11 + x;

	assert(!0);
	assert(0);

	assert(~-1, "(msg)");

	assert(x < 20, "foobar");

	assert(1 == 2);

	assert(a == 4, "(message)");   int b = 1;

	char* s = NULL;
	libassert_asprintf(&s, "(message: %s %s @ %d)", "kukurutz", "shoobidoosah", 777);

	assert(a + f < 7.0, "(message: %s %s @ %d)", "kukurutz", "shoobidoosah", 777);   int c = 2;

	assert(a + b / c + f * 11 <= 7, s);

	ASSERT_EQ(a, b);

	free(s);
}

