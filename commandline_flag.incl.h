#include "commandline_flag.h"

#include <string>

namespace util {

template <>
class CommandlineFlag<std::string> final : public AbstractCommandlineFlag {
 public:
  CommandlineFlag(const char* name, const char* usage, std::string* value)
      : AbstractCommandlineFlag(name, usage), value_(value) {
    mutable_flags()->push_back(this);
  }

  void set_value(const std::string& value) override { *value_ = value; }

  std::string value() const override { return *value_; }

 private:
  std::string* const value_;
};

template <>
class CommandlineFlag<int> final : public AbstractCommandlineFlag {
 public:
  CommandlineFlag(const char* name, const char* usage, int* value)
      : AbstractCommandlineFlag(name, usage), value_(value) {
    mutable_flags()->push_back(this);
  }

  void set_value(const std::string& value) override {
    *value_ = std::stod(value);
  }

  std::string value() const override { return std::to_string(*value_); }

 private:
  int* const value_;
};

template <>
class CommandlineFlag<float> final : public AbstractCommandlineFlag {
 public:
  CommandlineFlag(const char* name, const char* usage, float* value)
      : AbstractCommandlineFlag(name, usage), value_(value) {
    mutable_flags()->push_back(this);
  }

  void set_value(const std::string& value) override {
    *value_ = std::stof(value);
  }

  std::string value() const override { return std::to_string(*value_); }

 private:
  float* const value_;
};

template <>
class CommandlineFlag<double> final : public AbstractCommandlineFlag {
 public:
  CommandlineFlag(const char* name, const char* usage, double* value)
      : AbstractCommandlineFlag(name, usage), value_(value) {
    mutable_flags()->push_back(this);
  }

  void set_value(const std::string& value) override {
    *value_ = std::stod(value);
  }

  std::string value() const override { return std::to_string(*value_); }

 private:
  double* const value_;
};

template <>
class CommandlineFlag<size_t> final : public AbstractCommandlineFlag {
 public:
  CommandlineFlag(const char* name, const char* usage, size_t* value)
      : AbstractCommandlineFlag(name, usage), value_(value) {
    mutable_flags()->push_back(this);
  }

  void set_value(const std::string& value) override {
    *value_ = std::stoull(value);
  }

  std::string value() const override { return std::to_string(*value_); }

 private:
  size_t* const value_;
};

template <>
class CommandlineFlag<bool> final : public AbstractCommandlineFlag {
 public:
  CommandlineFlag(const char* name, const char* usage, bool* value)
      : AbstractCommandlineFlag(name, usage), value_(value) {
    mutable_flags()->push_back(this);
  }

  void set_value(const std::string& value) override {
    *value_ = !(value.empty() || value == "false" || value == "0");
  }

  std::string value() const override { return *value_ ? "true" : "false"; }

 private:
  bool* const value_;
};

template <>
class CommandlineFlag<char> final : public AbstractCommandlineFlag {
 public:
  CommandlineFlag(const char* name, const char* usage, char* value)
      : AbstractCommandlineFlag(name, usage), value_(value) {
    mutable_flags()->push_back(this);
  }

  void set_value(const std::string& value) override {
    *value_ = std::stoull(value);
  }

  std::string value() const override { return std::to_string(*value_); }

 private:
  char* const value_;
};

};  // namespace util
