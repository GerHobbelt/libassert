#undef LIBASSERT_PREFIX_ASSERTIONS

#include "catch2/catch_test_macros.hpp"
#include <libassert/assert-catch2.hpp>

// Tests marked with `/* <*> */` are expected to produce reports via libassert.

CATCH_TEST_CASE("1 + 1 is 2") {
    ASSERT(1 + 1 == 3);                   /* <*> */
}

CATCH_TEST_CASE("1 + 2 is 3") {
	LIBASSERT_ASSERT(1 + 2 == 4);         /* <*> */
}

CATCH_TEST_CASE("1 + 0 is 1") {
	// lowercase `assert()` should also have been made available by libassert/assert.hpp
	assert(1 + 1 == 1);                   /* <*> */
}

static void foo(int x) {
	LIBASSERT_INVOKE(x >= 20, "ASSERT", assertion, , "foobar");
}

CATCH_TEST_CASE("REQUIRE_ASSERT FAIL") {
	REQUIRE_ASSERT(foo(20));              /* <*> */
}

CATCH_TEST_CASE("REQUIRE_ASSERT PASS") {
    REQUIRE_ASSERT(foo(5));
}
