
#include "../../src/compile-tests/code-compile-testset.h"

#include <libassert/assert.h>

// Copyright (c) 2021-2025 Jeremy Rifkin under the MIT license
// https://github.com/jeremy-rifkin/libassert

#include <iostream>

#include "common.hpp"
#include "utils.hpp"
#include "microfmt.hpp"
#include "analysis.hpp"
#include "platform.hpp"
#include "paths.hpp"
#include "printing.hpp"

#if defined(BUILD_MONOLITHIC)
#define main    assert_basics_demo_main
#endif

namespace {

	using namespace ::libassert;

	bool my_failure_handler(const assertion_info& info) {
		enable_virtual_terminal_processing_if_needed(); // for terminal colors on windows
		std::string message = info.to_string(
			terminal_width(STDERR_FILENO),
			isatty(STDERR_FILENO) ? get_color_scheme() : color_scheme::blank
		);
		std::cerr << message << std::endl;
		switch (info.type) {
		case assert_type::debug_assertion:
		case assert_type::assertion:
		case assert_type::assumption:
		case assert_type::panic:
		case assert_type::unreachable:
			(void)fflush(stderr);
			//LIBASSERT_BREAKPOINT_IF_DEBUGGING();
			// the special trick of this type of assertion is: it allows the application to continue unimpeded for ALL assertion types!
			return false;

		default:
			LIBASSERT_PRIMITIVE_PANIC("Unknown assertion type in assertion failure handler");
		}
		return true;
	}

}

int main(void) {
	::libassert::set_failure_handler(my_failure_handler);

	compile_tests_conglomerate_test();

	::libassert::set_failure_handler(0);

	return 0;
}

