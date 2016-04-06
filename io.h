#ifndef UTIL_IO_H_
#define UTIL_IO_H_

// This file specifies uniform serialization and deserialization for different
// types.

#include <iostream>
#include <string>
#include <vector>

namespace util {

// Basic IO.
//
// Serializes and deserializes basic types and basic structures.
// E.g. int, float, etc.
template <typename Type>
void Write(std::ostream* out, const Type& item);
template <typename Type>
void Read(std::istream* in, Type* item);

// String IO.
//
// Serializes and deserializes std::string.
template <>
void Write<std::string>(std::ostream* out, const std::string& str);
template <>
void Read<std::string>(std::istream* in, std::string* str);

// Vector IO.
//
// Serializes and deserializes std::vector. Element type of the vector should be
// supported by the Write/Read interface.
template <typename Type>
void Write(std::ostream* out, const std::vector<Type>& v);
template <typename Type>
void Read(std::istream* in, std::vector<Type>* v);

// Input for std::vector<bool>.
//
// Deserializes std::vector<bool>.
template <>
void Read<bool>(std::istream* in, std::vector<bool>* v);

}  // namespace util

#include "io.incl.h"

#endif  // UTIL_IO_H_
