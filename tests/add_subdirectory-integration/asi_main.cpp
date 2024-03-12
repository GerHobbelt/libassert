#include <assert.hpp>


#if defined(BUILD_MONOLITHIC)
#define main    assert_add_subdirectory_integration_test_main
#endif

int main() {
    VERIFY(true);
    ASSUME(true);
    ASSERT(true);
	return 0;
}
