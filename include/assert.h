//
// assert.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Defines the assert macro and related functionality.
//
// NOTE: this header file OVERRIDES any system/library-defined `assert()` macro and replaces it with the libassert one.
// *Also* introduced is the use of C++-based functionality underneath this macro/function to ensure userland code
// only feeds **boolean expressions** to the assert macro: arbitrary assert argument expressions which *assume*
// *implicit* conversion to boolean (i.e. implicit non-null test) SHOULD cause a compiler error!
//

// NOTE: no include guard

#undef assert

#define LIBASSERT_OFFER_SYSTEM_ASSERT_REPLACEMENT
#include <libassert/assert.hpp>

