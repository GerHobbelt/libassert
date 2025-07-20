// Most basic of tests

#define LIBASSERT_USE_ONLY_PRIMITIVE_ASSERTIONS            1
//#define LIBASSERT_PREFIX_ASSERTIONS                       1

#include <cassert>
#include <optional>
#include <type_traits>

#include <libassert/assert.h>

#include "monolithic_examples.h"

static std::optional<float> foo() {
    return 2.5f;
}


#if defined(BUILD_MONOLITHIC)
#define main    assert_basic_primitive_test_main
#endif

extern "C"
int main(void) {
    LIBASSERT_DEBUG_ASSERT(foo());
	auto f = *foo();
	static_assert(std::is_same<decltype(f), float>::value);
    assert(f == 2.5f);

	return 0;
}
