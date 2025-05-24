// Most basic of tests

#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS

#include <cassert>
#include <optional>
#include <type_traits>

#include <libassert/assert.hpp>

#include "monolithic_examples.h"

static std::optional<float> foo() {
    return 2.5f;
}


#if defined(BUILD_MONOLITHIC)
#define main    assert_basic_test_main
#endif

extern "C"
int main(void) {
    DEBUG_ASSERT(foo());
	auto f = *foo();
	static_assert(std::is_same<decltype(f), float>::value);
    assert(f == 2.5f);

	return 0;
}
