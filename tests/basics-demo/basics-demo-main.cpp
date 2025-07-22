
#include "../../src/compile-tests/code-compile-testset.h"

#include <libassert/assert.h>

// Copyright (c) 2021-2025 Jeremy Rifkin under the MIT license
// https://github.com/jeremy-rifkin/libassert

#include <iostream>
#include <format>

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


	template <class T>
	static constexpr size_t countof(T &&arr) {
		return sizeof(arr) / sizeof(arr[0]);
	}

	static inline std::string repeat(const std::string &src, unsigned int count) {
		std::string dst;
		for (; count > 0; count--) {
			dst += src;
		}
		return dst;
	}


	// --------------------------------------------------------------------

	static unsigned int hit_counts[5 /* assert_type has 5 types */] = {0};

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
			LIBASSERT_BREAKPOINT_IF_DEBUGGING_ON_FAIL();
			hit_counts[static_cast<int>(info.type)]++;
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
	LIBASSERT_ASSUME(my_failure_handler == 0);			// fails --> count it!
	LIBASSERT_ASSUME(my_failure_handler != nullptr);    // succeeds: NOT counted!

	::libassert::set_failure_handler(0);

	std::cerr << "\n\n\n========================================================\n"
		"The total number of observed assertion failures (vs. expected):\n"
		"\n";

	static const char *types[] = {
		"debug_assertion",
		"assertion",
		"assumption",
		"panic",
		"unreachable"
	};

	static const unsigned int expected_counts[] = {
		168,
		280,
		1,
		0,
		0
	};

	unsigned int sums[2] = {0};
	for (int i = 0; i < countof(hit_counts); i++) {
		std::cerr << std::format("  {:<20}: {:>4} / {:>4}\n", types[i], hit_counts[i], expected_counts[i]);
		sums[0] += hit_counts[i];
		sums[1] += expected_counts[i];

		LIBASSERT_DEBUG_ASSERT(hit_counts[i] == expected_counts[i], "for index {}", i);
	}
	std::cerr << std::format("  {}  {}\n", repeat(std::string(" "), 20), repeat(std::string("-"), 4+3+4));
	std::cerr << std::format("  {:<20}: {:>4} / {:>4}\n", "Totals", sums[0], sums[1]);

	LIBASSERT_ASSERT(sums[0] == sums[1], "number of observed assertion failures does not match our expectation!");

	return 0;
}

