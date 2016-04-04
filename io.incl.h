#include "io.h"

#include <iostream>
#include <vector>

namespace util {

// General IO.
template <typename Type>
void Write(std::ostream* out, const Type& item) {
  out->write((const char*)&item, sizeof(Type));
}

template <typename Type>
void Read(std::istream* in, Type* item) {
  in->read((char*)item, sizeof(Type));
}

// String IO.
template <>
void Write<std::string>(std::ostream* out, const std::string& str) {
  out->write(str.c_str(), str.size() + 1);
}

template <>
void Read<std::string>(std::istream* in, std::string* str) {
  std::getline(*in, *str, '\0');
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
