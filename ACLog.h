#ifndef _ACLOG_H_
#define _ACLOG_H_
// do not include this in another .h, include directly in .cpp

#define AC_LOG(...)
#define AC_ASSERT(...)
#define AC_ERROR(...)
#define AC_WARN(...)
#define AC_DEBUG(...)
#define AC_INFO(...)
#define AC_TRACE(...)

#if _DEBUG && AC_LOGLEVEL
#undef AC_LOG
#define AC_LOG(...) __VA_ARGS__

#if AC_LOGLEVEL >= 1
#undef AC_ASSERT	
#define AC_ASSERT(...) AC_LOG(__VA_ARGS__)
#endif

#if AC_LOGLEVEL >= 2
#undef AC_ERROR	
#define AC_ERROR(...) AC_LOG(__VA_ARGS__)
#endif

#if AC_LOGLEVEL >=3
#undef AC_WARN
#define AC_WARN(...) AC_LOG(__VA_ARGS__)
#endif

#if AC_LOGLEVEL >=4
#undef AC_DEBUG
#define AC_DEBUG(...) AC_LOG(__VA_ARGS__)
#endif

#if AC_LOGLEVEL >=5
#undef AC_INFO
#define AC_INFO(...) AC_LOG(__VA_ARGS__)
#endif

#if AC_LOGLEVEL >=6
#undef AC_TRACE
#define AC_TRACE(...) AC_LOG(__VA_ARGS__)
#endif

#endif

#define AC_LOGFUNC(level,fmt,...) ACross::log( (level),  AC_MODULE_NAME_STR,F((fmt)),##__VA_ARGS__)
#define ACASSERT(condition, fmt,...) AC_ASSERT(if(!(condition)) AC_LOGFUNC(0,  fmt,##__VA_ARGS__));
#define ACERROR(fmt,...) AC_ERROR(AC_LOGFUNC( 1, fmt,##__VA_ARGS__));
#define ACWARN(fmt,...) AC_WARN(AC_LOGFUNC( 2,  fmt,##__VA_ARGS__));
#define ACDEBUG(fmt,...) AC_DEBUG(AC_LOGFUNC(3,  fmt,##__VA_ARGS__));
#define ACINFO(fmt,...) AC_INFO(AC_LOGFUNC( 4, fmt,##__VA_ARGS__));
#define ACTRACE(fmt,...) AC_TRACE(AC_LOGFUNC(5,fmt,##__VA_ARGS__));

#ifdef _MSC_VER 
#define ACBREAK(condition, fmt,...) AC_ASSERT(if(!(condition)) {AC_LOGFUNC(0,  fmt,##__VA_ARGS__);__debugbreak();});
#else
#define ACBREAK(condition,fmt,...) ACASSERT(condition,fmt,##__VA_ARGS__);
#endif


//defines a module name for logging.
//This must be used in every file that uses the AC* logging functions
//Use only in .cpp files!
#define ACROSS_MODULE(name) AC_LOG(static const char AC_MODULE_NAME_STR[] PROGMEM = name);




#endif
