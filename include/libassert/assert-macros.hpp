
// Copyright (c) 2021-2025 Jeremy Rifkin under the MIT license
// https://github.com/jeremy-rifkin/libassert

#if !defined(LIBASSERT_HPP)

#include <libassert/assert.hpp>

#ifndef LIBASSERT_PHASE_3_ALL_DONE
#error "libassert/assert-macros.hpp driver failed to properly initialize the libassert library."
#endif

// ------------------------------------------------------------------

#elif !defined(LIBASSERT_PHASE_1_PRODUCE_MACROS_ONLY) && !defined(LIBASSERT_PHASE_2_DEFINE_CPP_TEMPLATES) && !defined(LIBASSERT_PHASE_3_ALL_DONE)

#define LIBASSERT_PHASE_1_PRODUCE_MACROS_ONLY  // --> start pahse 1: define only preprocessor macros, so those are 'up' when we hit magic_enum.h & friends at the top of stringification.hpp
// kill the assert.hpp include guard as we must parse that one again, while *inside* its first load/parse!
#undef LIBASSERT_HPP

#include <libassert/assert.hpp>

#undef LIBASSERT_PHASE_1_PRODUCE_MACROS_ONLY  // --> start of phase 2: re-parse the 'parent' instance of assert.hpp to get the libassert C++ code + namespace + templates.
#define LIBASSERT_PHASE_2_DEFINE_CPP_TEMPLATES

#elif defined(LIBASSERT_PHASE_2_DEFINE_CPP_TEMPLATES)

#define LIBASSERT_PHASE_3_ALL_DONE
#undef LIBASSERT_PHASE_2_DEFINE_CPP_TEMPLATES

#endif
