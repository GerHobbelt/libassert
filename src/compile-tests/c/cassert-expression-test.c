#define LIBASSERT_ASSERT_IS_EXPRESSION            1

#include <cassert>
#include <stdlib.h>

#include "compile-tests/code-compile-testset.h"

#ifndef LIBASSERT_ASSERT
#error "libassert include paths are not included or don't have precedence over system's assert.h + cassert header files."
#endif

void libassert_ct_cassert_as_expression_test(void) {
	int x = 4;
	float f = 2.5f;
	int a = (assert(f == 2.5f), x);
	int b = (assert(a == 4, "(message)"), 1);

	char* s = NULL;
	libassert_asprintf(&s, "(message: %s %s @ %d)", "kukurutz", "shoobidoosah", 777);

	int c = (assert(a + f < 7.0, "(message: %s %s @ %d)", "kukurutz", "shoobidoosah", 777), 2);

	assert(a + b + c == 7, s);

	free(s);
}

