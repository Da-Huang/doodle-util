#ifndef UTIL_COMMANDLINE_FLAG_H_
#define UTIL_COMMANDLINE_FLAG_H_

// This file provides macros of defining and declaring commandline flags.

#include <string>
#include <vector>

// Defines a flag.
#define DEFINE_flag(name, type, default_value, usage)                   \
  type FLAG##_##name = default_value;                                   \
  ::util::CommandlineFlag<type> COMMANDLINE_FLAG##_##name(#name, usage, \
                                                          &FLAG##_##name)

// Declares a flag.
#define DECLARE_flag(name, type) extern type FLAG##_##name

// bool
#define DEFINE_bool(name, default_value, usage) \
  DEFINE_flag(name, bool, default_value, usage)
#define DECLARE_bool(name) DECLARE_flag(name, bool)

// char
#define DEFINE_char(name, default_value, usage) \
  DEFINE_flag(name, char, default_value, usage)
#define DECLARE_char(name) DECLARE_flag(name, char)

// double
#define DEFINE_double(name, default_value, usage) \
  DEFINE_flag(name, double, default_value, usage)
#define DECLARE_double(name) DECLARE_flag(name, double)

// float
#define DEFINE_float(name, default_value, usage) \
  DEFINE_flag(name, float, default_value, usage)
#define DECLARE_float(name) DECLARE_flag(name, float)

// int
#define DEFINE_int(name, default_value, usage) \
  DEFINE_flag(name, int, default_value, usage)
#define DECLARE_int(name) DECLARE_flag(name, int)

// size_t
#define DEFINE_size(name, default_value, usage) \
  DEFINE_flag(name, size_t, default_value, usage)
#define DECLARE_size(name) DECLARE_flag(name, size_t)

// std::string
#define DEFINE_string(name, default_value, usage) \
  DEFINE_flag(name, std::string, default_value, usage)
#define DECLARE_string(name) DECLARE_flag(name, std::string)

namespace util {

// This class provides interfaces for manipulating commandline flag.
class AbstractCommandlineFlag {
 public:
  AbstractCommandlineFlag(const char* name, const char* usage)
      : name_(name), usage_(usage) {}
  AbstractCommandlineFlag(const AbstractCommandlineFlag& flag) = delete;
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

// Commandline flag of concrete types.
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

#endif  // UTIL_COMMANDLINE_FLAG_H_
