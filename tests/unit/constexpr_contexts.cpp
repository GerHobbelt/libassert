#include <libassert/assert.hpp>

#include "monolithic_examples.h"

template<int X> void foo() {}

constexpr int bar(int x) {
    DEBUG_ASSERT(x % 2 == 0);
    return x / 2;
}


#if defined(BUILD_MONOLITHIC)
#define main    assert_constexpr_contexts_main
#endif

extern "C"
int main(void) {
    foo<bar(2)>();

	return 0;
}
