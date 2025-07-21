//
// Defines the assert macro and related functionality.
//
// NOTE: this header file OVERRIDES any system/library-defined `assert()` macro and replaces it with the libassert one.
// *Also* introduced is the use of C++-based functionality underneath this macro/function to ensure userland code
// only feeds **boolean expressions** to the assert macro: arbitrary assert argument expressions which *assume*
// *implicit* conversion to boolean (i.e. implicit non-null test) SHOULD cause a compiler error!
//

// ----------------------------------------------------------------------
// WARNING: No include guard. This was done intentionally. See below.
// ----------------------------------------------------------------------

#undef assert

#define LIBASSERT_OFFER_SYSTEM_ASSERT_REPLACEMENT    1
#include <libassert/assert.h>
