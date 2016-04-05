#include "io.h"

#include <iostream>
#include <string>
#include <vector>

namespace util {

// String IO.
template <>
void Write<std::string>(std::ostream* out, const std::string& str) {
  out->write(str.c_str(), str.size() + 1);
}

template <>
void Read<std::string>(std::istream* in, std::string* str) {
  std::getline(*in, *str, '\0');
}

// Input for std::vector<bool>.
template <>
void Read<bool>(std::istream* in, std::vector<bool>* v) {
  size_t v_size;
  Read(in, &v_size);
  v->resize(v_size);
  for (size_t i = 0; i < v_size; ++i) {
    bool item;
    Read(in, &item);
    (*v)[i] = item;
  }
}

}  // namespace util
