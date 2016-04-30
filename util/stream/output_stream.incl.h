#include "output_stream.h"

namespace util {

template <typename Type>
OutputStream& OutputStream::operator <<(const Type& item) {
  *GetOutputStream() << item;
  return *this;
}

}  // namespace util
