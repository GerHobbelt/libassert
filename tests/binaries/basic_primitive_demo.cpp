#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS
#include <libassert/assert.hpp>

#include "monolithic_examples.h"

#if defined(BUILD_MONOLITHIC)
#define main    assert_basic_primitive_demo_test_main
#endif

extern "C"
int main(void) {
    ASSERT(1 + 1 == 3);

	return 0;
}
