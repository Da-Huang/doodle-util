#ifndef UTIL_STRING_H_
#define UTIL_STRING_H_

// This file specifies uniform interfaces related to string.

#include <string>
#include <vector>

namespace util {

// Uniform stringification and destringification for common data types.

// Stringifies item.
//
// By default, it returns item.ToString().
template <typename Type>
std::string ToString(const Type& item);

// Destringifies str to item.
//
// By default, it fails, due to unimplementation.
//
// Crashes, if fails.
template <typename Type>
void FromString(const std::string& str, Type* item);

// Stringifies some common basic data types.
#define DECLARE_TO_STRING_FUNCTION(type) \
  template <>                            \
  std::string ToString<type>(const type& item)

DECLARE_TO_STRING_FUNCTION(bool);
DECLARE_TO_STRING_FUNCTION(char);
DECLARE_TO_STRING_FUNCTION(double);
DECLARE_TO_STRING_FUNCTION(float);
DECLARE_TO_STRING_FUNCTION(int);
DECLARE_TO_STRING_FUNCTION(size_t);
DECLARE_TO_STRING_FUNCTION(std::string);

// Destringifies for some common basic data types. Crashes, if fails.
#define DECLARE_FROM_STRING_FUNCTION(type) \
  template <>                            \
  void FromString<type>(const std::string& str, type* item)

DECLARE_FROM_STRING_FUNCTION(bool);
DECLARE_FROM_STRING_FUNCTION(char);
DECLARE_FROM_STRING_FUNCTION(double);
DECLARE_FROM_STRING_FUNCTION(float);
DECLARE_FROM_STRING_FUNCTION(int);
DECLARE_FROM_STRING_FUNCTION(size_t);
DECLARE_FROM_STRING_FUNCTION(std::string);

// Stringifies vector.
// E.g.
//   [1, 3, 5, 7]
template <typename Type>
std::string ToString(const std::vector<Type>& v);

// Stringfies const char*.
std::string ToString(const char* item);

// Common string utils.

// Gets length of a string.
size_t Strlen(const char* str);

// Copies string from src to dest.
//
// `dest` should provide enough space and cannot be overlapped with `src`.
void Strcpy(char* dest, const char* src);

}  // namespace util

#include "string.incl.h"

#endif // UTIL_STRING_H_
