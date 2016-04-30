#include "string.h"

#include <sstream>
#include <string>

namespace util {

// Stringification.
template <>
std::string ToString<bool>(const bool& item) {
  return item ? "true" : "false";
}

template <>
std::string ToString<char>(const char& item) {
  return std::string(1, item);
}

template <>
std::string ToString<double>(const double& item) {
  std::ostringstream oss;
  oss << item;
  return oss.str();
}

template <>
std::string ToString<float>(const float& item) {
  std::ostringstream oss;
  oss << item;
  return oss.str();
}

template <>
std::string ToString<int>(const int& item) {
  return std::to_string(item);
}

template <>
std::string ToString<size_t>(const size_t& item) {
  return std::to_string(item);
}

template <>
std::string ToString<std::string>(const std::string& item) {
  return item;
}

// Destringification.
template <>
void FromString<bool>(const std::string& str, bool* item) {
  *item = !(str.empty() || str == "false" || str == "0");
}

template <>
void FromString<char>(const std::string& str, char* item) {
  *item = str[0];
}

template <>
void FromString<double>(const std::string& str, double* item) {
  *item = std::stod(str);
}

template <>
void FromString<float>(const std::string& str, float* item) {
  *item = std::stof(str);
}

template <>
void FromString<int>(const std::string& str, int* item) {
  *item = std::stoi(str);
}

template <>
void FromString<size_t>(const std::string& str, size_t* item) {
  *item = std::stoull(str);
}

template <>
void FromString<std::string>(const std::string& str, std::string* item) {
  *item = str;
}

std::string ToString(const char* item) {
  return item;
}

size_t Strlen(const char* str) {
  size_t i = 0;
  while (str[i]) ++i;
  return i;
}

void Strcpy(char* dest, const char* src) {
  size_t i = 0;
  while (src[i]) {
    dest[i] = src[i];
    ++i;
  }
  dest[i] = 0;
}

}  // namespace util
