#ifndef UTIL_STREAM_OUTPUT_STREAM_H_
#define UTIL_STREAM_OUTPUT_STREAM_H_

#include <ostream>

namespace util {

// This class provides abstract interfaces for manipulating std::ostream.
class OutputStream {
 public:
  OutputStream() = default;
  OutputStream(const OutputStream& out) = delete;
  virtual ~OutputStream() = default;

  template <typename Type>
  OutputStream& operator<<(const Type& item);

  // Outputs something like std::endl.
  OutputStream& operator<<(std::ostream& (*item)(std::ostream&));

 protected:
  virtual std::ostream* GetOutputStream() = 0;
};

}  // namespace util

#include "output_stream.incl.h"

#endif  // UTIL_STREAM_OUTPUT_STREAM_H_
