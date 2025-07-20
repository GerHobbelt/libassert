#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS              1
#define LIBASSERT_PREFIX_ASSERTIONS                          1

#include <libassert/assert.h>

#if LIBASSERT_PREFIX_ASSERTIONS != 1
#error "LIBASSERT_LIBASSERT_PREFIX_ASSERTIONS: libassert did not set the expected preset."
#endif

#if LIBASSERT_LOWERCASE != 0
#error "LIBASSERT_LOWERCASE: libassert did not set the expected default."
#endif

#if LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS != 1
#error "LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS: libassert did not set the expected preset."
#endif

#include "monolithic_examples.h"

#if defined(BUILD_MONOLITHIC)
#define main    assert_basic_primitive_demo_test_main
#endif

extern "C"
int main(void) {
    ASSERT(1 + 1 == 3);

	return 0;
}
