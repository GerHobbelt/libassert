
#include <catch2/catch_session.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_config_wchar.hpp>
#include <catch2/internal/catch_leak_detector.hpp>
#include <catch2/internal/catch_platform.hpp>

#include <stdio.h>
#include <stdlib.h>


namespace Catch {
	CATCH_INTERNAL_START_WARNINGS_SUPPRESSION
		CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS
		static LeakDetector leakDetector;
	CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION
}


// Standard C/C++ main entry point
extern "C"
int main(int argc, const char** argv) {

	// We want to force the linker not to discard the global variable
	// and its constructor, as it (optionally) registers leak detector
	(void)&Catch::leakDetector;

	return Catch::Session().run(argc, argv);
}

