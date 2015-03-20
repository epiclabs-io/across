// ACross cross-compile development toolkit
// Author: Javier Peletier <jm@friendev.com>
// Summary: ACross allows you to build your Arduino projects using Visual Studio.
// Your Arduino code is cross - compiled and runs in your PC, which enables
// step - by - step debugging
//
// Copyright (c) 2015 All Rights Reserved, http://friendev.com
//
// This source is subject to the GPLv2 license.
// Please see the License.txt file for more information.
// All other rights reserved.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#ifndef _ACLOG_H_
#define _ACLOG_H_
// do not include this in another .h, include directly in .cpp


/* log levels inspired by user ecodans from stack overflow 
http://stackoverflow.com/questions/7839565/logging-levels-logback-rule-of-thumb-to-assign-log-levels
error: the system is in distress, customers are probably being affected (or will soon be) and the fix probably requires human intervention. The "2AM rule" applies here- if you're on call, do you want to be woken up at 2AM if this condition happens? If yes, then log it as "error".
warn: an unexpected technical or business event happened, customers may be affected, but probably no immediate human intervention is required. On call people won't be called immediately, but support personnel will want to review these issues asap to understand what the impact is. Basically any issue that needs to be tracked but may not require immediate intervention.
info: things we want to see at high volume in case we need to forensically analyze an issue. System lifecycle events (system start, stop) go here. "Session" lifecycle events (login, logout, etc.) go here. Significant boundary events should be considered as well (e.g. database calls, remote API calls). Typical business exceptions can go here (e.g. login failed due to bad credentials). Any other event you think you'll need to see in production at high volume goes here.
debug: just about everything that doesn't make the "info" cut... any message that is helpful in tracking the flow through the system and isolating issues, especially during the development and QA phases. We use "debug" level logs for entry/exit of most non-trivial methods and marking interesting events and decision points inside methods.
trace: we don't use this often, but this would be for extremely detailed and potentially high volume logs that you don't typically want enabled even during normal development. Examples include dumping a full object hierarchy, logging some state during every iteration of a large loop, etc.
*/



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
