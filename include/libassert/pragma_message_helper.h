
// https://stackoverflow.com/questions/5966594/how-can-i-use-pragma-message-so-that-the-message-points-to-the-filelineno
//
// See also: http://www.highprogrammer.com/alan/windev/visualstudio.html
//
// Statements like:
// 
// #pragma message(LIBASSERT_PM_REMINDER "Fix this problem!")
// 
// Which will cause messages like:
// 
// C:\Source\Project\main.cpp(47): REMINDER: Fix this problem!
// 
// to show up during compiles. Note that you can NOT use the
// words "error" or "warning" in your reminders, since it will
// make the IDE think it should abort execution. You can double
// click on these messages and jump to the line in question.

#define LIBASSERT_STRINGIZE(L)       #L 
#define LIBASSERT_MAKESTRING(M, L)   M(L)
#define $LIBASSERT_LINE LIBASSERT_MAKESTRING( LIBASSERT_STRINGIZE, __LINE__ )
#define LIBASSERT_PM_REMINDER __FILE__ "(" $LIBASSERT_LINE ") : REMINDER: "
#define LIBASSERT_PM_TODO     __FILE__ "(" $LIBASSERT_LINE ") : TODO: "
#define LIBASSERT_PM_WARNING  __FILE__ "(" $LIBASSERT_LINE ") : WARNING: "
