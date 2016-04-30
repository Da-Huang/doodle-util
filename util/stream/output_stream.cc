#include "output_stream.h"

#include <ostream>

namespace util {

OutputStream& OutputStream::operator<<(std::ostream& (*item)(std::ostream&)) {
  *GetOutputStream() << item;
  return *this;
}

}  // namespace util
