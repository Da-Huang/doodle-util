#include "commandline_flag.h"

#include <string>
#include <vector>

#include "string.h"

namespace util {

std::vector<AbstractCommandlineFlag*>*
AbstractCommandlineFlag::mutable_flags() {
  static std::vector<AbstractCommandlineFlag*> flags;
  return &flags;
}

std::string AbstractCommandlineFlag::ToString() const {
  return ::util::ToString(name_) + ": " + usage_ + " [" + value() + "]";
}

}  // namespace util
