#include "io.h"

#include <iostream>
#include <string>
#include <vector>

namespace util {

// Basic IO.
template <typename Type>
void Write(std::ostream* out, const Type& item) {
  out->write((const char*)&item, sizeof(Type));
}

template <typename Type>
void Read(std::istream* in, Type* item) {
  in->read((char*)item, sizeof(Type));
}

// Vector IO.
template <typename Type>
void Write(std::ostream* out, const std::vector<Type>& v) {
  size_t v_size = v.size();
  Write(out, v_size);
  for (const Type& item : v) {
    Write(out, item);
  }
}

template <typename Type>
void Read(std::istream* in, std::vector<Type>* v) {
  size_t v_size;
  Read(in, &v_size);
  v->resize(v_size);
  for (size_t i = 0; i < v_size; ++i) {
    Read(in, &(*v)[i]);
  }
}

}  // namespace util
