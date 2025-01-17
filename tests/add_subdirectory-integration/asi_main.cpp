#include <libassert/assert.hpp>

#include "monolithic_examples.h"


#if defined(BUILD_MONOLITHIC)
#define main    assert_add_subdirectory_integration_test_main
#endif

extern "C"
int main(void) {
#if defined(VERIFY)
	VERIFY(true);
#endif
	ASSERT(true);
	ASSUME(true);
	DEBUG_ASSERT(true);
	return 0;
}
