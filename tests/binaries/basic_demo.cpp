#define LIBASSERT_PREFIX_ASSERTIONS                          1
#include <libassert/assert.h>

#include "monolithic_examples.h"

#if defined(BUILD_MONOLITHIC)
#define main    assert_basic_demo_test_main
#endif

extern "C"
int main(void) {
    ASSERT(1 + 1 == 3);

	return 0;
}
