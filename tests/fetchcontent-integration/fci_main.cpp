#include <libassert/assert.hpp>

#include <iostream>

#include "monolithic_examples.h"


#if defined(BUILD_MONOLITHIC)
#define main    assert_fetchcontent_integration_test_main
#endif

extern "C"
int main(void) {
    ASSERT(true);
    ASSUME(true);
    DEBUG_ASSERT(true);
    std::cout<<"Good to go"<<std::endl;
	return 0;
}
