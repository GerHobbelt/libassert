#ifndef ASSERT_CATCH2_HPP
#define ASSERT_CATCH2_HPP

#define LIBASSERT_PREFIX_ASSERTIONS
#include <libassert/assert.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

class LibassertMatcher : public Catch::Matchers::MatcherBase<int> {
    std::string message;

public:
    LibassertMatcher() = default;
    LibassertMatcher(std::string message_) : message(std::move(message_)) {}

    bool match(const int&) const override {
        return message.empty();
    }

    virtual std::string describe() const override {
        return message;
    }
};

// #define CHECK(...) do { try { LIBASSERT_ASSERT(__VA_ARGS__); CHECK_THAT(1, LibassertMatcher()); } catch(std::exception& e) { CHECK_THAT(false, LibassertMatcher(e.what())); } } while(false)
// #define REQUIRE(...) do { try { LIBASSERT_ASSERT(__VA_ARGS__); REQUIRE_THAT(1, LibassertMatcher()); } catch(std::exception& e) { REQUIRE_THAT(false, LibassertMatcher(e.what())); } } while(false)
#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL != 0
 #error "Libassert integration does not work with MSVC's non-conformant preprocessor. /Zc:preprocessor must be used."
#endif
#define ASSERT(...) do { try { LIBASSERT_ASSERT(__VA_ARGS__); REQUIRE_THAT(1, LibassertMatcher()); } catch(std::exception& e) { REQUIRE_THAT(false, LibassertMatcher(e.what())); } } while(false)

inline void libassert_failure_handler(const libassert::assertion_info& info) {
    std::string message = "";
    // catch line wrapping has issues with ansi sequences https://github.com/catchorg/Catch2/issues/2833
    throw std::runtime_error(info.header(0, libassert::color_scheme::blank));
}

inline auto libassert_pre_main = [] () {
    libassert::set_failure_handler(libassert_failure_handler);
    return 1;
} ();

#endif
