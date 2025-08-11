#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS // for fopen
#endif

#define LIBASSERT_PREFIX_ASSERTIONS
#define LIBASSERT_LOWERCASE

#include <algorithm>
#include <array>
#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <string_view>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include <libassert/assert.h>
#include <libassert/version.hpp>

#ifdef _MSC_VER
 // disable unsafe use of bool warning msvc
 #pragma warning(disable: 4806)
#endif

#include "monolithic_examples.h"

#define ESC "\033["
#define RED ESC "1;31m"
#define GREEN ESC "1;32m"
#define BLUE ESC "1;34m"
#define CYAN ESC "1;36m"
#define PURPL ESC "1;35m"
#define DARK ESC "1;30m"
#define RESET ESC "0m"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define ASSERT_EQ(e1, e2, ...)		debug_assert(((e1) == (e2)), "ASSERT_EQ assertion failed: {} == {} fails.", (e1), (e2) __VA_OPT__(,) __VA_ARGS__)
#define ASSERT_NEQ(e1, e2, ...)		debug_assert(((e1) != (e2)), "ASSERT_NE assertion failed: {} != {} fails.", (e1), (e2) __VA_OPT__(,) __VA_ARGS__)

#define ASSERT_GTEQ(e1, e2, ...)		debug_assert(((e1) >= (e2)), "ASSERT_GTEQ assertion failed: {} >= {} fails.", (e1), (e2) __VA_OPT__(,) __VA_ARGS__)
#define ASSERT_LTEQ(e1, e2, ...)		debug_assert(((e1) <= (e2)), "ASSERT_LTEQ assertion failed: {} <= {} fails.", (e1), (e2) __VA_OPT__(,) __VA_ARGS__)

#define ASSERT_AND(e1, e2, ...)		debug_assert(((e1) && (e2)), "ASSERT_AND assertion failed: {} && {} fails.", (e1), (e2) __VA_OPT__(,) __VA_ARGS__)
#define ASSERT_OR(e1, e2, ...)		debug_assert(((e1) || (e2)), "ASSERT_OR assertion failed: {} || {} fails.", (e1), (e2) __VA_OPT__(,) __VA_ARGS__)

void qux();
void wubble();

namespace {

bool custom_fail(const libassert::assertion_info& assertion) {
    std::cerr<<assertion.to_string(libassert::terminal_width(libassert::stderr_fileno))<<std::endl<<std::endl;
	return false;
}

int garple() {
    return 2;
}

static void rec(int n) {
    if(n == 0) ASSERT(false);
    else rec(n - 1);
}

static void recursive_a(int), recursive_b(int);

static void recursive_a(int n) {
    if(n == 0) ASSERT(false);
    else recursive_b(n - 1);
}

static void recursive_b(int n) {
    if(n == 0) ASSERT(false);
    else recursive_a(n - 1);
}

static auto min_items() {
    return 10;
}

static void zoog(const std::map<std::string, int>& map) {
	DEBUG_ASSERT(map.size() > 0);

#if __cplusplus >= 202002L
     ASSERT(map.contains("foo"), "expected key not found", map);
#else
     ASSERT(map.count("foo") != 1, "expected key not found", map);
#endif
    ASSERT(map.at("bar") >= 0, "unexpected value for foo in the map", map);
}

#define O_RDONLY 0
static int open(const char*, int) {
    return -1;
}

static std::optional<float> get_param() {
    return {};
}

static int get_mask() {
    return 0b00101101;
}

namespace demo {

    void basic() {
        ASSERT(1 == 2);
        DEBUG_ASSERT(1 == 2);
        assert(1 == 2);
        debug_assert(1 == 2);
        ASSERT(1 == 2, "Messages");
        // PANIC();
    }

    void numbers() {
        ASSERT(18446744073709551606ULL == -10);
        ASSERT(get_mask() == 0b00001101);
        ASSERT(0xf == 16);
        long long x = -9'223'372'036'854'775'807;
        ASSERT(x & 0x4);
        ASSERT(!x and true == 2);
    }

    void strings() {
        std::string s = "test\n";
        int i = 0;
        ASSERT(s == "test");
        ASSERT(s[i] == 'c', "", s, i);
    }

    void recursion() {
        rec(10);
        recursive_a(10);
    }

    void containers() {
        std::set<int> a = { 2, 2, 4, 6, 10 };
        std::set<int> b = { 2, 2, 5, 6, 10 };
        std::vector<double> c = { 1.2, 2.44, 3.15159, 5.2 };
        ASSERT(a == b, c);
        ASSERT(a == b, ([&] {
            std::vector<int> diff;
            std::set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(diff));
            return diff;
        } ()));
        std::map<std::string, int> m0 = {
            {"foo", 2},
            {"bar", -2}
        };
        ASSERT(false, m0);
        std::map<std::string, std::vector<int>> m1 = {
            {"foo", {1, -2, 3, -4}},
            {"bar", {-100, 200, 400, -800}}
        };
        ASSERT(false, m1);
        auto t = std::make_tuple(1, 0.1 + 0.2, "foobars");
        ASSERT(false, t);
        std::array<int, 10> arr = {1,2,3,4,5,6,7,8,9,10};
        ASSERT(false, arr);
        std::map<int, int> map {{1,1}};
        ASSERT(map.count(1) == 2);
        ASSERT(map.count(1) >= 2 * garple(), "Error while doing XYZ");
        zoog({
            //{ "foo", 2 },
            { "bar", -2 },
            { "baz", 20 }
        });
        std::vector<int> vec = {2, 3, 5, 7, 11, 13};
        ASSERT(vec.size() > min_items(), "vector doesn't have enough items", vec);
        std::optional<float> parameter;
        if(auto i = *ASSERT_VAL(parameter)) {
            static_assert(std::is_same<decltype(i), float>::value);
        }
        [[maybe_unused]] float f = *assert_val(get_param());
        auto x = [&] () -> decltype(auto) { return ASSERT_VAL(parameter); };
        static_assert(std::is_same<decltype(x()), std::optional<float>&>::value);
    }

    void cerrno() {
        const char* path = "/home/foobar/baz";
        ASSERT(open(path, O_RDONLY) >= 0, "Internal error with foobars", errno, path);
        [[maybe_unused]] int fd = open(path, O_RDONLY);
        ASSERT(fd >= 0, "Internal error with foobars", errno, path);
        [[maybe_unused]] FILE* f = ASSERT_VAL(fopen(path, "r") != nullptr, "Internal error with foobars", errno, path);
    }

    void misc() {
        wubble();
        std::string s = "h1eLlo";
        [[maybe_unused]] auto it = std::find_if(
            s.begin(),
            s.end(),
            [](char c) {
                ASSERT(not isdigit(c), c);
                return c >= 'A' and c <= 'Z';
            }
        );
        ASSERT(true ? false : true == false);
        ASSERT(true ? false : true, "pffft");
        ASSERT(0, 2 == garple());
    }

    void diff() {
        libassert::set_diff_highlighting(true);
        std::string s1 = "Lorem ipsum sit amet";
        std::string s2 = "Lorem ipsum dolor sit amet";
        ASSERT(s1 == s2);
        auto a = std::nextafter(0.3, 0.4);
        auto b = std::nextafter(a, 0.4);
        ASSERT(a == b);
        libassert::set_diff_highlighting(false);
    }
}

void foo() {
    demo::basic();
    demo::numbers();
    demo::strings();
    demo::recursion();
    demo::containers();
    demo::cerrno();
    demo::misc();
    demo::diff();
}

class foo2 {
public:
    template<typename> void bar([[maybe_unused]] std::pair<int, int> x) {
        baz();
    }

    void baz() {
        puts("");
        // General demos
        {
            zoog({
                //{ "foo", 2 },
                { "bar", -2 },
                { "baz", 20 }
            });
            std::vector<int> vec = {2, 3, 5, 7, 11, 13};
            debug_assert(vec.size() > min_items(), "vector doesn't have enough items");
        }
        const char* path = "/home/foobar/baz";
        {
            int fd = open(path, O_RDONLY);
            debug_assert(fd >= 0, "Internal error with foobars", errno, path);
            (void)fd;
        }
        {
            debug_assert(open(path, O_RDONLY) >= 0, "Internal error with foobars", errno, path);
        }
        {
			FILE* f = fopen(path, "r");
			assert(f != nullptr, "Internal error with foobars", errno, path);
            (void)f;
        }
        debug_assert(false, "Error while doing XYZ");
        debug_assert(false);
        DEBUG_ASSERT((puts("DEBUG_ASSERT called") && false));

        {
            std::map<int, int> map {{1,1}};
            DEBUG_ASSERT(map.count(1) == 2);
            debug_assert(map.count(1) >= 2 * garple(), "Error while doing XYZ");
        }
        debug_assert((!!0, 2 == garple()));
        {
            std::optional<float> parameter;
             if(auto i = *(parameter)) {
                 static_assert(std::is_same<decltype(i), float>::value);
             }
             float f = *(get_param());
             (void)f;

			 auto x = [&] () -> decltype(auto) { 
				return (parameter); 
			};
            static_assert(std::is_same<decltype(x()), std::optional<float>&>::value);
        }

        qux();

        {
            M() < 2;
            puts("----");
            debug_assert(M() < 2);
            puts("----");
            M m;
            puts("----");
            debug_assert(m < 2);
            puts("----");
        }


        debug_assert(true ? false : true == false);
        debug_assert(true ? false : true, "pffft");

        wubble();

        rec(10);

        recursive_a(10);

        ASSERT(18446744073709551606ULL == -10);

        ASSERT(get_mask() == 0b00001101);
        debug_assert(0xf == 16);

        {
            std::string s = "test\n";
            int i = 0;
            debug_assert(s == "test");
            ASSERT(s[i] == 'c', "", s, i);
        }
        {
            debug_assert(S<S<int>>(2) == S<S<int>>(4));
            S<void> e, f;
            debug_assert(e == f);
        }

        long long x = -9'223'372'036'854'775'807;
        debug_assert(0 != (x & 0x4));

        debug_assert(!x and true == 2);
        debug_assert((puts("A"), false) && (puts("B"), false));

        {
            #if defined(__GNUC__) || defined(__GNUG__) // gcc/clang
             #pragma GCC diagnostic ignored "-Wshadow"
            #endif
            std::string s = "h1eLlo";
            debug_assert(std::find_if(s.begin(), s.end(), [](char c) {
                debug_assert(not isdigit(c), "{}", c);
                return c >= 'A' and c <= 'Z';
            }) == s.end());
        }

        {
            std::set<int> a = { 2, 2, 4, 6, 10 };
            std::set<int> b = { 2, 2, 5, 6, 10 };
            std::vector<double> c = { 1.2, 2.44, 3.15159, 5.2 };
            debug_assert(a == b);
            std::map<std::string, int> m0 = {
                {"foo", 2},
                {"bar", -2}
            };
            debug_assert(m0.empty());
            std::map<std::string, std::vector<int>> m1 = {
                {"foo", {1, -2, 3, -4}},
                {"bar", {-100, 200, 400, -800}}
            };
            debug_assert(m1.empty());
            auto t = std::make_tuple(1, 0.1 + 0.2, "foobars");
            //debug_assert(t);
            std::array<int, 10> arr = {1,2,3,4,5,6,7,8,9,10};
            debug_assert(arr.empty());
        }

        // Numeric
        // Tests useful during development
	  {
        debug_assert(.1f == .1);
        debug_assert(1.0 == 1.0 + std::numeric_limits<double>::epsilon());
		debug_assert(((0x12p2) == (12)), "ASSERT_EQ assertion failed", (0x12p2), (12));
        ASSERT_EQ(0x12p2, 12, "+ user message...", 25.0f, -42);
        ASSERT_EQ(0x12p2, 0b10);
        debug_assert(0b1000000 == 0x3);
        debug_assert(.1 == 2);
        debug_assert(true == false);
        debug_assert(true ? false : true == false);
        debug_assert(0b100 == 0x3);

        debug_assert(0 == +(2 == garple())); // add unary + operator or you'll get this warning (with subsequent errors) --> `LIBASSERT_GEN_OP_BOILERPLATE(eq,   ==)` @ expression-decomposition.hpp(58,9): warning C4805: '==': unsafe mix of type 'B' and type 'A' in operation
		std::map<int, int> map{{1,1}};
		ASSERT_GTEQ(map.count(1 == 1), 2);
        ASSERT_EQ(map.count(1), 2, "Error while doing XYZ");
        ASSERT_GTEQ(map.count(2 * garple()), 2, "Error while doing XYZ");
        debug_assert(S<S<int>>(2) == S<S<int>>(4));
        S<S<int>> a(1), b(2);
#if 0
		ASSERT_EQ(a, b);
        const S<S<int>> c(4), d(8);
        ASSERT_EQ(c, d);
        S<void> g, h;
        ASSERT_EQ(g, h);
        ASSERT_EQ(1, 2);
        //ASSERT_EQ(&a, nullptr);    --> this one freaks out std::format()
		debug_assert(&a == nullptr);
		ASSERT_EQ((uintptr_t)&a, 0ULL & 0ULL);
        //ASSERT_AND(&a, nullptr);   // --> ditto
		debug_assert(&a && nullptr);
		ASSERT_AND(nullptr && nullptr, nullptr);
        ASSERT_AND(&a, nullptr && nullptr);
        ASSERT_AND((bool)nullptr && (bool)nullptr, (bool)nullptr);
        ASSERT_AND((uintptr_t)&a, (bool)nullptr && (bool)nullptr); // FIXME: parentheses
        //ASSERT_EQ(foo, (int*)nullptr);
#endif

LIBASSERT_WARNING_PRAGMA_PUSH
        debug_assert(0 == +(2  ==  garple()));
#pragma warning(disable: 4805) // '==': unsafe mix of type 'int' and type 'int' in operation
		debug_assert(0 == (2 == garple()));
		debug_assert(0 == 2 == garple());
LIBASSERT_WARNING_PRAGMA_POP

        debug_assert(true ? false : true, "pffft");
        {
            std::string x = "aa";
            std::string y = "bb";
            debug_assert(x == y);
        }
		using P = std::array<std::string, 2>;
        {
            P x {"aa"};
            P y {"bb"};
            debug_assert(x == y);
        }
        {
            P x {"aa"};
            debug_assert(x == P {"bb"});
        }
		{
			P x{"aa", "bb"};
			debug_assert((x == P{"bb", "aa"}));  // double braces?!?! Trouble With The Comma(tm) -- the movie? ;-)  nah, jus' da us'l preprocessor woes for ye. *sigh* 
		}
		{
            const P x {"aa"};
            debug_assert(x == P {"bb"});
        }
        debug_assert((42 & 3U) == 1UL);

        debug_assert([](int a, int b) {
            return a + b;
        } (10, 32) not_eq 42);
        debug_assert([](){return 42;}() not_eq 42);
        debug_assert([&]<typename T>(T a, T b){return a+b;}(10, 32) not_eq 42);
        ASSERT_NEQ([](int a, int b) {
            return a + b;
        } (10, 32), 42);
        debug_assert('\n' == '\t');
        debug_assert(<:](){return 42;%>() not_eq 42);

        debug_assert(&a == nullptr);

        {
            std::string s = "h1ello";
            debug_assert(std::find_if(s.begin(), s.end(), [](char c) {
                if(c == '1') debug_assert(c != '1');
                //debug_assert(!isdigit(c), c);
                return c == 'e';
            }) == s.end());
        }

        debug_assert(0.1 == 0.2);
        debug_assert(.1 == 0.2);
        debug_assert(.1f == 0.2);

        debug_assert(true); // this should lead to another debug_assert(false) because we're in demo mode
	  }
    }
};

} // anonymous namespace


#if defined(BUILD_MONOLITHIC)
#define main    assert_demo_main
#endif

extern "C"
int main(void) {
    libassert::enable_virtual_terminal_processing_if_needed();
    libassert::set_failure_handler(custom_fail);
    
	foo();
	
    foo2 f;
    f.bar<int>({});

	return 0;
}
