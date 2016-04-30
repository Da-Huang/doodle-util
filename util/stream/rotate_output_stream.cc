#include "rotate_output_stream.h"

#include <ostream>

namespace util {

RotateOutputStream::~RotateOutputStream() { *front_out_ << back_out_.str(); }

RotateOutputStream& RotateOutputStream::OutputFront() {
  output_front_ = true;
  return *this;
}

std::ostream* RotateOutputStream::GetOutputStream() {
  return output_front_ ? front_out_ : &back_out_;
}

}  // namespace util
