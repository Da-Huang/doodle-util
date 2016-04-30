#include "string.h"

#include <string>
#include <vector>

#include "util/logging.h"

namespace util {

// Default stringification. It supposes that item is a class with ToString
// function.
template <typename Type>
std::string ToString(const Type& item) {
  return item.ToString();
}

// Default destringification. It is unimplemented.
template <typename Type>
void FromString(const std::string& str, Type* item) {
  LOG(FATAL) << "Unimplemented function.";
}

template <typename Type>
std::string ToString(const std::vector<Type>& v) {
  if (v.empty()) {
    return "[]";
  }
  std::string ans = "[" + ToString(v[0]);
  for (size_t i = 1; i < v.size(); ++i) {
    ans += ", " + ToString(v[i]);
  }
  return ans + "]";
}

}  // namespace util
