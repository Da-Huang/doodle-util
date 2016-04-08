#ifndef UTIL_CHECK_H_
#define UTIL_CHECK_H_

// This file specifies interfaces for checking data.

#include <ostream>

#include "logging.h"
#include "stream/rotate_output_stream.h"
#include "string.h"

// Checks whether condition is true.
//
// Outputs infomation and fails, if condition is false.
#define CHECK(condition)                                              \
  ::util::Logger(!(condition), ::util::Logger::Level::FATAL).stream() \
      << "C:" << DEBUG_MESSAGE

// Checks whether expect is equal to actual.
//
// Outputs infomation and fails, if they are not equal.
#define CHECK_EQ(expect, actual)                                               \
  ((RotateOutputStream&)(RotateOutputStream(                                   \
                             &(::util::Logger(!(expect == actual),             \
                                              ::util::Logger::Level::FATAL)    \
                                   .stream()                                   \
                               << "C:" << DEBUG_MESSAGE))                      \
                         << std::endl                                          \
                         << "Check failed: " #expect " != " #actual            \
                         << std::endl                                          \
                         << "Expect " #expect ": " << ::util::ToString(expect) \
                         << std::endl                                          \
                         << "Actual " #actual ": " << ::util::ToString(actual) \
                         << std::endl)).OutputFront()

// Checks whether predicate(target) is true.
//
// Outputs infomation and fails, if it is false.
#define CHECK_THAT(target, predicate)                                          \
  ((RotateOutputStream&)(RotateOutputStream(                                   \
                             &(::util::Logger(!(predicate(target)),            \
                                              ::util::Logger::Level::FATAL)    \
                                   .stream()                                   \
                               << "C:" << DEBUG_MESSAGE))                      \
                         << std::endl                                          \
                         << "Check failed: !" #predicate " " #target           \
                         << std::endl                                          \
                         << "Target " #target ": " << ::util::ToString(target) \
                         << std::endl)).OutputFront()

#endif  // UTIL_CHECK_H_
