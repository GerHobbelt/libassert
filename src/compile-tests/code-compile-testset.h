
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void libassert_ct_assert_h_as_expression_test(void);
void libassert_ct_assert_h_primitive_style_test(void);
void libassert_ct_assert_h_include_test(void);
void libassert_ct_cassert_as_expression_test(void);
void libassert_ct_cassert_primitive_style_test(void);
void libassert_ct_cassert_include_test(void);

void libassert_cppt_assert_as_expression_test(void);
void libassert_cppt_assert_h_primitive_style_test(void);
void libassert_cppt_assert_h_include_test(void);
void libassert_cppt_cassert_as_expression_test(void);
void libassert_cppt_cassert_primitive_style_test(void);
void libassert_cppt_cassert_include_test(void);

void assert_c_code_expression_test(void);
void assert_c_code_lowercase_expression_test(void);
void assert_c_code_lowercase_test(void);
void assert_c_code_no_prefix_expression_test(void);
void assert_c_code_no_prefix_test(void);
void assert_c_code_primitive_style_expression_test(void);
void assert_c_code_primitive_style_test(void);
void assert_c_code_test(void);

void assert_cpp_code_expression_test(void);
void assert_cpp_code_lowercase_expression_test(void);
void assert_cpp_code_lowercase_test(void);
void assert_cpp_code_no_prefix_expression_test(void);
void assert_cpp_code_no_prefix_test(void);
void assert_cpp_code_primitive_style_expression_test(void);
void assert_cpp_code_primitive_style_test(void);
void assert_cpp_code_test(void);

int compile_tests_conglomerate_test(void);

#ifdef __cplusplus
}
#endif

