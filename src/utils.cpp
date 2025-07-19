#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <regex>
#include <string_view>
#include <string>
#include <utility>
#include <vector>

#include <libassert/assert.hpp>

#if defined(__has_include) && __has_include(<cpptrace/basic.hpp>)
 #include <cpptrace/basic.hpp>
 #include <cpptrace/exceptions.hpp>
#else
 #include <cpptrace/cpptrace.hpp>
#endif

#include "utils.hpp"
#include "microfmt.hpp"

#include <libassert/assert.hpp>

LIBASSERT_BEGIN_NAMESPACE
namespace detail {
	LIBASSERT_ATTR_COLD LIBASSERT_EXPORT
		void primitive_assert_impl(
			libassert::assert_type normal_assert,
			const char* expression,
			const char* signature,
			source_location location,
			const char* message
		) {
		// Make sure a catcher for uncaught exceptions is always available: either the application-specified one, or ours!
		setup_default_handler_for_uncaught_exceptions();

		assert_static_parameters params{
		.macro_name = signature, // name,
		.type = normal_assert,
		.expr_str = expression,
		.location = location,
		.args_strings = {}
		};
		assertion_info info(&params, detail::generate_trace(), 0);
		set_message(info, message);

		// send off
		fail(info);
		if (info.type != assert_type::debug_assertion) {
			LIBASSERT_PRIMITIVE_PANIC("PANIC/UNREACHABLE failure handler returned");
		}
	}

    [[noreturn]] LIBASSERT_ATTR_COLD LIBASSERT_EXPORT
    void primitive_panic_impl(
        const char* signature,
        source_location location,
        const char* message
    ) {
		// Make sure a catcher for uncaught exceptions is always available: either the application-specified one, or ours!
		setup_default_handler_for_uncaught_exceptions();

		assert_static_parameters params{
		.macro_name = signature, // name,
		.type = assert_type::panic,
		//.expr_str = expression,
		.location = location,
		.args_strings = {}
		};
		assertion_info info(&params, detail::generate_trace(), 0);
		set_message(info, message);

		// send off
		fail(info);

#if 0
		// warning C4717: 'libassert::v1::detail::primitive_panic_impl': recursive on all control paths, function will cause runtime stack overflow
		LIBASSERT_PRIMITIVE_PANIC("PANIC/UNREACHABLE failure handler returned");
#else
		// should never get here... unless the fail handler returns to caller anyway, despite the assert_type being set to `assert::panic`.
		std::abort();
#endif
	}

    /*
     * string utilities
     */

    LIBASSERT_ATTR_COLD LIBASSERT_EXPORT_TESTING
    std::vector<std::string_view> split(std::string_view s, std::string_view delims) {
        std::vector<std::string_view> vec;
        size_t old_pos = 0;
        size_t pos = 0;
        while((pos = s.find_first_of(delims, old_pos)) != std::string::npos) {
            vec.emplace_back(s.substr(old_pos, pos - old_pos));
            old_pos = pos + 1;
        }
        vec.emplace_back(s.substr(old_pos));
        return vec;
    }

    LIBASSERT_ATTR_COLD
    std::string_view trim(const std::string_view s) {
        const size_t l = s.find_first_not_of(whitespace_chars);
        if(l == std::string_view::npos) {
            return "";
        }
        const size_t r = s.find_last_not_of(whitespace_chars) + 1;
        return s.substr(l, r - l);
    }

    LIBASSERT_ATTR_COLD
    void replace_all_dynamic(std::string& str, std::string_view text, std::string_view replacement) {
        std::string::size_type pos = 0;
        while((pos = str.find(text.data(), pos, text.length())) != std::string::npos) {
            str.replace(pos, text.length(), replacement.data(), replacement.length());
            // advancing by one rather than replacement.length() in case replacement leads to
            // another replacement opportunity, e.g. folding > > > to >> > then >>>
            pos++;
        }
    }

    LIBASSERT_ATTR_COLD LIBASSERT_EXPORT_TESTING
    void replace_all(std::string& str, const std::regex& re, std::string_view replacement) {
        std::smatch match;
        std::size_t i = 0;
        // NOLINTNEXTLINE(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
        while(std::regex_search(str.cbegin() + i, str.cend(), match, re)) {
            str.replace(i + match.position(), match.length(), replacement);
            i += match.position() + replacement.length();
        }
    }

    LIBASSERT_ATTR_COLD LIBASSERT_EXPORT_TESTING
    void replace_all(std::string& str, std::string_view substr, std::string_view replacement) {
        std::string::size_type pos = 0;
        // NOLINTNEXTLINE(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
        while((pos = str.find(substr.data(), pos, substr.length())) != std::string::npos) {
            str.replace(pos, substr.length(), replacement.data(), replacement.length());
            pos += replacement.length();
        }
    }

    LIBASSERT_ATTR_COLD
    void replace_all_template(std::string& str, const std::pair<std::regex, std::string_view>& rule) {
        const auto& [re, replacement] = rule;
        std::smatch match;
        std::size_t cursor = 0;
        // NOLINTNEXTLINE(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
        while(std::regex_search(str.cbegin() + cursor, str.cend(), match, re)) {
            // find matching >
            const std::size_t match_begin = cursor + match.position();
            std::size_t end = match_begin + match.length();
            for(int c = 1; end < str.size() && c > 0; end++) {
                if(str[end] == '<') {
                    c++;
                } else if(str[end] == '>') {
                    c--;
                }
            }
            // make the replacement
            str.replace(match_begin, end - match_begin, replacement);
            cursor = match_begin + replacement.length();
        }
    }

    LIBASSERT_ATTR_COLD
    std::string indent(const std::string_view str, size_t depth, char c, bool ignore_first) {
        size_t i = 0;
        size_t j;
        std::string output;
        while((j = str.find('\n', i)) != std::string::npos) {
            if(i != 0 || !ignore_first) { output.insert(output.end(), depth, c); }
            output.insert(output.end(), str.begin() + i, str.begin() + j + 1);
            i = j + 1;
        }
        if(i != 0 || !ignore_first) { output.insert(output.end(), depth, c); }
        output.insert(output.end(), str.begin() + i, str.end());
        return output;
    }

	LIBASSERT_ATTR_COLD
	[[noreturn]] void generic_handler_for_uncaught_exceptions(void) {
		try {
			std::rethrow_exception(std::current_exception());
		}
		catch (const std::exception &e) {
			std::cerr << "Unhandled exception: " << e.what() << "\n";
		}
		catch (...) {
			std::cerr << "Unhandled exception: UNKNOWN TYPE\n";
		}
		std::abort();
	}

	// typedef void (__CRTDECL* terminate_handler )(void);

	static std::terminate_handler u_ex_handler = nullptr;
	static std::terminate_handler original_u_ex_handler = nullptr;

	extern "C"
	[[noreturn]] void __CRTDECL libassert_terminate_handler(void) {
		if (!u_ex_handler) {
			generic_handler_for_uncaught_exceptions();
		}
		else {
			u_ex_handler();
		}
	}

	LIBASSERT_ATTR_COLD
	void setup_handler_for_uncaught_exceptions(std::terminate_handler handler) {
		auto old_app_f = std::get_terminate();
		if (old_app_f != libassert_terminate_handler) {
			// our handler wrapper has not been installed yet!
			original_u_ex_handler = old_app_f;
			std::set_terminate(libassert_terminate_handler);
		}
		// now we can be sure our unknown-exception-handler-wrapper has been installed.
		// 
		// No need to check if we have already registered a handling functor:
		// if we have, we DO NOT OVERWRITE that one!
		// You must invoke `deinit_handler_for_uncaught_exceptions()` first, before you
		// are allowed to set a new handler.
		if (!u_ex_handler || u_ex_handler == original_u_ex_handler) {
			u_ex_handler = handler;
		}
	}

	LIBASSERT_ATTR_COLD
	void deinit_handler_for_uncaught_exceptions(void) {
		// 'de-init' means: reset callback to original as specified by the application:
		u_ex_handler = nullptr;
		auto old_app_f = original_u_ex_handler;
		if (!old_app_f) {
			old_app_f = std::get_terminate();
		}
		setup_handler_for_uncaught_exceptions(old_app_f);
	}

	LIBASSERT_ATTR_COLD
	void setup_default_handler_for_uncaught_exceptions(void) {
		setup_handler_for_uncaught_exceptions(generic_handler_for_uncaught_exceptions);
	}

	LIBASSERT_EXPORT void libassert_detail_primitive_assert_implpp(::libassert::assert_type mode, const char *expr, const char *signature, const char *file, const int line, const char *function, const char *message) {
		using namespace ::libassert;

		source_location location{function, file, line};
		detail::primitive_assert_impl(mode, expr, signature, location, message);
	}

}
LIBASSERT_END_NAMESPACE

