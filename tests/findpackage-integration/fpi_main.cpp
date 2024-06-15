#include <libassert/assert.hpp>

#include <iostream>


#if defined(BUILD_MONOLITHIC)
#define main    assert_findpackage_integration_test_main
#endif

int main() {
    ASSERT(true);
    ASSUME(true);
    DEBUG_ASSERT(true);
    std::cout<<"Good to go"<<std::endl;
	return 0;
}
