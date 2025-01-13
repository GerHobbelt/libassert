#include <libassert/assert.hpp>

#if defined(BUILD_MONOLITHIC)
#define main    assert_basic_demo_test_main
#endif

int main(void) {
    ASSERT(1 + 1 == 3);
		return 0;
}
