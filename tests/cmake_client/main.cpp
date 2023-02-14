#include "assert.hpp"


#if defined(BUILD_MONOLITHIC)
#define main    assert_cmake_client_main
#endif

auto main() -> int {
  VERIFY(true);
  ASSUME(true);
  ASSERT(true);

  return 0;
}
