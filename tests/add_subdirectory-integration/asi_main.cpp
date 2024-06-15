#include <libassert/assert.hpp>


#if defined(BUILD_MONOLITHIC)
#define main    assert_add_subdirectory_integration_test_main
#endif

int main() {
#if defined(VERIFY)
    VERIFY(true);
#endif
    ASSUME(true);
    ASSERT(true);
		DEBUG_ASSERT(true);
		return 0;
}
