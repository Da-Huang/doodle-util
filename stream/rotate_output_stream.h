#ifndef UTIL_STREAM_ROTATE_OUTPUT_STREAM_H_
#define UTIL_STREAM_ROTATE_OUTPUT_STREAM_H_

#include <ostream>
#include <sstream>

#include "stream/output_stream.h"

namespace util {

// This class outputs data in rotated order.
//
// When it is initialized, it outputs back data. After OutputFront() is called,
// it outputs front data.
//
// E.g.
//   ((RotateOutputStream&)(RotateOutputStream(std::cout) << "AB"))
//           .OutputFront()
//       << "CD";
//   Outputs: CDAB
class RotateOutputStream final : public OutputStream {
 public:
  RotateOutputStream(std::ostream* out) : front_out_(out) {}
  ~RotateOutputStream() override;

  // Sets this object to output front data.
  RotateOutputStream& OutputFront();

 protected:
  std::ostream* GetOutputStream() override;

 private:
  // Flag of whether it outputs front data or back data.
  bool output_front_ = false;
  // Stream to output data.
  std::ostream* front_out_;
  // Stream taken as buffer to output back data.
  std::ostringstream back_out_;
};

}  // namespace util

#endif  // UTIL_STREAM_ROTATE_OUTPUT_STREAM_H_
