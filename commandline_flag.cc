#include "commandline_flag.h"

#include <string>
#include <vector>

namespace util {

std::vector<AbstractCommandlineFlag*>*
AbstractCommandlineFlag::mutable_flags() {
  static std::vector<AbstractCommandlineFlag*> flags;
  return &flags;
};

std::string AbstractCommandlineFlag::ToString() const {
  return std::string(name_) + ": " + usage_ + " [" + value() + "]";
}

}  // namespace util
