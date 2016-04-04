// This file specifies general serialization and deserialization for any type.
//
// The following types are supported.
// * All basic types, e.g. int, float, etc.
// * Undynamic data-in structs.
// * std::string.
// * std::vector of supported types.

#ifndef UTIL_IO_H_
#define UTIL_IO_H_

#include <iostream>
#include <string>
#include <vector>

namespace util {

template <typename Type>
void Write(std::ostream* out, const Type& item);

template <typename Type>
void Read(std::istream* in, Type* item);

}  // namespace util

#include "io.incl.h"

#endif  // UTIL_IO_H_
