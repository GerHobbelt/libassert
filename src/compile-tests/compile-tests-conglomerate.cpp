
#include "compile-tests/code-compile-testset.h"

#include <libassert/assert.h>

using namespace libassert;

static bool assert_failure_handler(const libassert::assertion_info& info) {

	LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL();

	std::string message = info.to_string(
		terminal_width(fileno(stderr)),
		/* ::isatty(fileno(stderr)) ? get_color_scheme() : */ color_scheme::blank
	);

	switch (info.type) {
	case assert_type::debug_assertion:
	case assert_type::assertion:
	case assert_type::assumption:
	case assert_type::panic:
	case assert_type::unreachable:
		(void)fflush(stderr);
		return false;

	default:
		LIBASSERT_PRIMITIVE_PANIC("Unknown assertion type in assertion failure handler");
	}

	throw std::runtime_error(std::move(message));
}

int compile_tests_conglomerate_test(void) {
	libassert::deinit_handler_for_uncaught_exceptions();
#if 0
	libassert::setup_handler_for_uncaught_exceptions(handler_for_uncaught_exceptions);
#else
	libassert::setup_default_handler_for_uncaught_exceptions();
#endif
	libassert::set_failure_handler(assert_failure_handler);

	libassert_ct_assert_h_as_expression_test();
	libassert_ct_assert_h_primitive_style_test();
	libassert_ct_assert_h_include_test();
	assert_c_code_expression_test();
	assert_c_code_lowercase_expression_test();
	assert_c_code_lowercase_test();
	assert_c_code_no_prefix_expression_test();
	assert_c_code_no_prefix_test();
	assert_c_code_primitive_style_expression_test();
	assert_c_code_primitive_style_test();
	assert_c_code_test();
	libassert_ct_cassert_as_expression_test();
	libassert_ct_cassert_primitive_style_test();
	libassert_ct_cassert_include_test();
	libassert_cppt_assert_as_expression_test();
	libassert_cppt_assert_h_primitive_style_test();
	libassert_cppt_assert_h_include_test();
	libassert_cppt_cassert_as_expression_test();
	libassert_cppt_cassert_primitive_style_test();
	libassert_cppt_cassert_include_test();
	assert_cpp_code_expression_test();
	assert_cpp_code_lowercase_expression_test();
	assert_cpp_code_lowercase_test();
	assert_cpp_code_no_prefix_expression_test();
	assert_cpp_code_no_prefix_test();
	assert_cpp_code_primitive_style_expression_test();
	assert_cpp_code_primitive_style_test();
	assert_cpp_code_test();

	return 0;
}

