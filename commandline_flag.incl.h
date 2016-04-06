#include "commandline_flag.h"

#include <string>

#include "string.h"

namespace util {

template <typename Type>
CommandlineFlag<Type>::CommandlineFlag(const char* name, const char* usage,
                                       Type* value)
    : AbstractCommandlineFlag(name, usage), value_(value) {
  mutable_flags()->push_back(this);
}

template <typename Type>
void CommandlineFlag<Type>::set_value(const std::string& value) {
  FromString(value, value_);
}

template <typename Type>
std::string CommandlineFlag<Type>::value() const {
  return ::util::ToString(*value_);
}

}  // namespace util
