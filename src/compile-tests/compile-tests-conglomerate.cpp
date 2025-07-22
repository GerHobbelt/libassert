
#include "compile-tests/code-compile-testset.h"

int compile_tests_conglomerate_test(void) {

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

