# `libassert` Critique

This is my (= Ger Hobbelt) evaluation of the library / codebase.

First off, I really like the concept and the way it's been pulled off. 10 out of 10.


## However...(designer goals)

given my own goals with an "over-engineered assertion library" like this is *slightly* different:

1. maximize power in C++ build mode (like the original `libassert` does)
2. provide the same (or at least, a very similar) interface for C code (which `libassert` does not)


## However...(developer experience: `__VAR_ARGS__`)

While I coded an experimental, basic, implementation which supports both C++ and C build modes -- with only a rudimentary `assert()` available in C build mode --
it turned out that the `__VAR_ARGS__` preprocessor handling is quite brittle: that's not a design/coding problem, but 99.995% another MSVC2022 compiler/preprocessor issue.

Anyhow, I had to fiddle around with judiciously applying `__VAR_OPT(,)__ __VAR_ARGS__` incantations to correctly deal with assertions, both with and *without* extra comment/message arguments.

Given this implementation issue, I now favor a work-around:
providing different (fixed argument count) assertion macros for both scenarios, e.g.

       assert(expr);                     // no message argument(s)
	   assert_w_msg(expr, "message");    // with message argument: a plain string
	   assert_w_msg(expr, fmt.format("message {} {}", arg1, arg2) );
                                    	 // with message argument: a formatted string,
										 // carrying additional parameters, using the
										 // `fmt::format` type-safe modern C++ simile 
										 // of classic `sprintf`.
	   assert_w_msg(expr, assert_printf("message %d %s", arg1, arg2) );
	                                     // same as the above, but for C build mode,
										 // where a specially crafted `assert_printf`
										 // wrapper is required to produce a (heap-allocated)
										 // formatted message string.


## However...(developer experience: `DEBUG_ASSERT_VAL` et al)

While I like the idea of an expression-based assertion, which transparently produces the asserted value (`ASSERT_VAL()`) next to a statement-based assertion (`ASSERT()`), 
I don't think the way it currently works in `libassert` is a good API for production software:

once you have read the relevant documentation, everything is honky dory while you apply it to reasonably simple expressions, e.g.

       auto rv = DEBUG_ASSERT_VAL(BigFatFunctionCall(arg) >= 42);  // barf when B.F.F.C. returns any value < 42
	   
as `libassert`s answer to the question how to deal with the dichotomy of 

1. returning the typed expression value we're interested in and need to proceed (in this case, the return value of `BigFatFunctionCall(arg)`)

2. testing that return value against some postcondition, thus producing a *boolean assertion expression* which is necessary for `DEBUG_ASSERT_VAL(expr)` to work as expected 
   (in this case, the extra boolean expression phrase is `<= 42`)
   
As `libassert` includes some very fancy logic to split the `BigFatFunctionCall(arg) >= 42` into `left partial expr`, `comparison operator` and `right partial expr` chunks, this works.

However! I fear the human isn't always as smart as that bit of automaton: when the expression as a whole becomes more complex, it becomes quite hard to easily spot which the critical
comparison operator for the assertion must be: imagine, f.e., a multi-line expression with multiple comparison operators thrown in at both sides of the fence: you now have to be
in top form every time you read this code to spot which part of the evaluation is the "left side" that `libassert` will take to produce the return value for `DEBUG_ASSERT_VAL()`.


Combining this minor gripe with the desire to have an (over-engineered) assertion library for both C++ and C build modes, I imagine the shortest and fastest answer to dealing with this is to *drop* 
the compile-time expression parser/splitter and use a more old skool macro approach instead (as can be found in many test libraries and elsewhere):

		// assertion statement: BigFatFunctionCall(arg) >= 42
        ASSERT_GE(BigFatFunctionCall(arg), 42)

		// assertion expression: BigFatFunctionCall(arg) [ >= 42 ]
        autp rv = ASSERT_GE_VAL(BigFatFunctionCall(arg), 42);  // returns value of first expression

i.e. provide a set of assertion macros a la googletest/Catch2/others, where the comparison operator is encoded in the name of the assertion macro:

- ASSERT_EQ  // ==
- ASSERT_NE  // !=
- ASSERT_LT  // <
- ASSERT_LE  // <=
- ASSERT_GT  // >
- ASSERT_GE  // >=


## Additional Considerations (advanced floating point handling & checks...)

What `libassert`'s `_VAL()` value expression assertions don't answer is the question how to deal with IEEE754 floating point equality checks and other complex comparisons/checks 
that must take FP accuracy and their ilk into account to deliver a desirable assertion, e.g. something like `ASSERT_EQ_APPROX(f1, f2)` which deals with the inaccuracies in preceding calculations by
checking `f1 ~= f2` by way of `fabs(f2 - f1) <= SOME_CONTEXT_DEPENDENT_EPSILON)`.

Okay, nobody I've seen has a nicely readable coded answer to this one (myself included), but in old skool code it invariably resulted in using specialized comparison functions / methods for such checks.

> Do note the float_compare C++ repository, which offers these floating point comparison functions in a nice little wrapper!

Attempting to incorporate this into `libassert`'s way of doing things makes reading the *combination* of such comparisons and `ASSERT_VAL()`-style value-forwarding assertion expressions 
very hard to read for both John Doe and the original author (after some calendar time has passed), no matter how we code this sort of thing...

Hence, for this class of checks at least, I believe the best answer is to stick with the current state of affairs: *no combining of check and expression value forwarding ops*, i.e. 
*no `_VAL()` macro support for this scenario*.


Ok. But that promptly leads to the next thought:

While `_VAL()` et al are a cool addition to the assertion library, *technically speaking*, how about we do without them *entirely*? 

This results in an extra line of code, as it would have taken in any classic implementation, but I'm *fine* with that: negligible code reading cost. 

One can take and stretch that 'negligible' argument to test multiple assertions = multiple extra lines: the cost now is non-negligible, but still minor enough that
I rather suffer from the latter scenario than scrunching multiple `_VAL(expr)` value assertions into a single statement. Thus we backpedal from:

        autp rv = ASSERT_GE_VAL(BigFatFunctionCall(arg), 42);

to

        autp rv = BigFatFunctionCall(arg);
        ASSERT_GE(rv, 42);

as any classic assertion library would expect you to code.



## Conclusion

I think `libassert` is marvelous and a beautiful product, but my own goals/desires, particularly the availability of (most of) the same assertion macros in C code, preclude my use of this library as-is.

Given the woes with MSVC2022 handling of the `__VAR_ARGS__` tail parameters passing when I was busy constructing wrapping assertion macros and attempting to tweak the `libassert` ones, the advice there seems to be 
to stay away from passing `__VAR_ARGS__` down a long chain of preprocessor macros and opt for a solution instead where the additional, *optional*, message string is entirely produced via function call or other means 
before entering the assertion macros.

The C++ & C mode support requirement implies that a `libassert`-style reporting of the compared values demands the use of dedicated assertion macros: one per comparison operator: `ASSERT_EQ`, `ASSERT_GT`, etc.

A further library simplification is considered, where the `ASSERT_VAL()` and related expression value forwarding assertion expression macros are to be discarded: we would then only accept assertion *statements*.

The stacktrace and value reporting facilities of `libassert` are grand and should be kept, but I belive I'll fare better with a slightly more classic approach to an assertions library in production code.



## However/Post.Scriptum...(conclusion)

My own argument for using format string based approaches for both C++ and C build mode holds no water: C++ uses `{fmt}`/`std::format` which has `{}` markers for value injection, while C uses `%d/%s/%xyz...` for the same:
that's two very different format string specs for the same thing, so C++ and C code assertions won't ever be *exactly* the same.

So the question to ask here is:
when we have two different string formatting approaches anyway, what's the real problem with one having *no* format string approach (C++ with original libassert) and the C code still using its 'classic' printf-style approach? NIH?

After a short while running with my original opinion, I have to say: it does not matter, not for me at least, when it comes to the number of typing/coding mistakes made in any assertion "extra data" tail.
In fact, Jeremy's approach (*no format string what-so-ever*) is slightly better in that regard as there you cannot fuck up the std::format string, as there's nothing to *specify*; *iff* you want/need special
formatting of one or more of those Extra Parameters, you can always go and run it through a local `std::format() -> std::string` transformation while feeding it to the libassert macros!

... backpedaling on/reverting my earlier decision re C++: re-introducing Jeremy's Extra Parameters approach for C++ at least. (Yes, it won't fly for C, so we have those printf()-style format strings there, but that's tolerable:
limitations of the language...)





