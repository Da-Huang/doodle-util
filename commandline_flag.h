// This file provides macros for defining and declaring commandline flags.
//
// The following types of flag are supported.
// * std::string
// * int
// * float
// * double
// * size_t
// * bool
// * char

#ifndef UTIL_COMMAND_LINE_FLAG_H_
#define UTIL_COMMAND_LINE_FLAG_H_

#include <string>
#include <vector>

// Defines and declares an flag.
#define DEFINE_flag(name, type, default_value, usage)                   \
  type FLAG##_##name = default_value;                                  \
  ::util::CommandlineFlag<type> COMMANDLINE_FLAG##_##name(#name, usage, \
                                                          &FLAG##_##name);
#define DECLARE_flag(name, type) extern type FLAG##_##name;

// std::string
#define DEFINE_string(name, default_value, usage) \
  DEFINE_flag(name, std::string, default_value, usage)
#define DECLARE_string(name) DECLARE_flag(name, std::string)

// int
#define DEFINE_int(name, default_value, usage) \
  DEFINE_flag(name, int, default_value, usage)
#define DECLARE_int(name) DECLARE_flag(name, int)

// float
#define DEFINE_float(name, default_value, usage) \
  DEFINE_flag(name, float, default_value, usage)
#define DECLARE_float(name) DECLARE_flag(name, float)

// double
#define DEFINE_double(name, default_value, usage) \
  DEFINE_flag(name, double, default_value, usage)
#define DECLARE_double(name) DECLARE_flag(name, double)

// size_t
#define DEFINE_size(name, default_value, usage) \
  DEFINE_flag(name, size_t, default_value, usage)
#define DECLARE_size(name) DECLARE_flag(name, size_t)

// bool
#define DEFINE_bool(name, default_value, usage) \
  DEFINE_flag(name, bool, default_value, usage)
#define DECLARE_bool(name) DECLARE_flag(name, bool)

// char
#define DEFINE_char(name, default_value, usage) \
  DEFINE_flag(name, char, default_value, usage)
#define DECLARE_char(name) DECLARE_flag(name, char)

namespace util {

class AbstractCommandlineFlag {
 public:
  AbstractCommandlineFlag(const char* name, const char* usage)
      : name_(name), usage_(usage) {}
  virtual ~AbstractCommandlineFlag() = default;

  virtual void set_value(const std::string& value) = 0;
  virtual std::string value() const = 0;

  const char* name() const { return name_; }
  const char* usage() const { return usage_; }

  std::string ToString() const;

 public:
  // Gets mutable flag vector to store/fetch flags.
  static std::vector<AbstractCommandlineFlag*>* mutable_flags();

 protected:
  const char* const name_;
  const char* const usage_;
};

template <typename Type>
class CommandlineFlag final : public AbstractCommandlineFlag {
 public:
  CommandlineFlag(const char* name, const char* usage, Type* value);

  void set_value(const std::string& value) override;
  std::string value() const override;

 private:
  Type* const value_;
};

};  // namespace util

#include "commandline_flag.incl.h"

#endif  // UTIL_COMMAND_LINE_FLAG_H_
