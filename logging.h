#ifndef UTIL_LOGGING_H_
#define UTIL_LOGGING_H_

// This file specifies an advanced logging system.

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#define DEBUG_MESSAGE __FILE__ << ":" << __LINE__ << ":" << __func__ << ": "

// Logs under a specific severity.
#define LOG(severity)                                            \
  ::util::Logger(true, ::util::Logger::Level::severity).stream() \
      << #severity[0] << ":" << DEBUG_MESSAGE

namespace util {

class Logger {
 public:
  enum Level {
    FATAL = 0,  // Under this level, it fails.
    ERROR = 1,
    WARNING = 2,
    INFO = 3,
    DEBUG = 4,
  };

 public:
  Logger(bool should_log, Level level)
      : should_log_(should_log), level_(level) {}
  virtual ~Logger();

  std::ostream& stream() { return ostr_; }

 protected:
  // Handles this log, if should_log_ is true.
  bool should_log_;
  // Log level. Handles this log, if it is not larger than Flag_v.
  Level level_;
  // Output buffer.
  std::ostringstream ostr_;
};

}  // namespace util

#endif  // UTIL_LOGGING_H_
