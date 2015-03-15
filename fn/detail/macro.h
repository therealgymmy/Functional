#ifndef __FN_DETAIL_MACRO__
#define __FN_DETAIL_MACRO__

#define REQUIRES(...) typename std::enable_if<(__VA_ARGS__), int>::type = 0

#define X_TO_STRING(s) TO_STRING(s)
#define TO_STRING(s) #s

#define CONCAT(a,b) CONCAT_HIDDEN(a,b)
#define CONCAT_HIDDEN(a,b) a ## b

#endif
