#ifndef MACRO_H
#define MACRO_H

#include <iostream>

// ---------------------------------------------------------------------
// CONFIGURATION ZONE
// ---------------------------------------------------------------------
//
// toggle comment to enable/disable TRACE messages
//#define ENABLE_TRACE
//
// toggle comment to enable/disable DEBUG messages
//#define ENABLE_DEBUG
//
// ---------------------------------------------------------------------
//  MACRO ZONE
// ---------------------------------------------------------------------

// -- always defined
#define STDERR std::cerr
#define STDOUT std::cout
#define LOG(out, lvl, clas, func, msg) out<<"["<<lvl<<"] - "<<clas<<"::"<<func<<": "<<msg<<std::endl
#define INFO(clas, func, msg) LOG(STDOUT, "INFO", clas, func, msg)
#define ERROR(clas, func, msg) LOG(STDERR, "ERROR", clas, func, msg)
#define ABORT(clas, func, msg, code) ERROR(clas, func, msg); exit(code)

// conditionnal defines

#ifdef ENABLE_DEBUG
#   define DEBUG(clas, func, msg) LOG(STDOUT, "DEBUG", clas, func, msg)
#else
#   define DEBUG(clas, func, msg)
#endif

#ifdef ENABLE_TRACE
#   define TRACE(clas, func, msg) LOG(STDOUT, "TRACE", clas, func, msg)
#else
#   define TRACE(clas, func, msg)
#endif

#endif // MACRO_H

