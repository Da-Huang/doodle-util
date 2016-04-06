#include "commandline_flag.h"

#include <string>
#include <unordered_set>

#include "check.h"
#include "init.h"
#include "logging.h"
#include "macro.h"

DEFINE_bool(b, true, "Test bool flag.");

DEFINE_char(c, 'C', "Test char flag.");

DEFINE_double(d, 123.456, "Test double flag.");

DEFINE_float(f, 12.3f, "Test float flag.");

DEFINE_int(i, 123, "Test int flag.");

DEFINE_size(size, 1234, "Test size flag.");

DEFINE_string(str, "abcdef", "Test string flag.");

DECLARE_int(backtrace_buffer_size);

DECLARE_bool(help);

DECLARE_int(v);

namespace util {
namespace {

void TestDefault() {
  CHECK_EQ(true, FLAG_b);
  CHECK_EQ('C', FLAG_c);
  CHECK_EQ(123.456, FLAG_d);
  CHECK_EQ(12.3f, FLAG_f);
  CHECK_EQ(123, FLAG_i);
  CHECK_EQ(1234, FLAG_size);
  CHECK_EQ("abcdef", FLAG_str);

  CHECK_EQ(100, FLAG_backtrace_buffer_size);
  CHECK_EQ(false, FLAG_help);
  CHECK_EQ(int(Logger::Level::INFO), FLAG_v);
}

void TestHelp() {
  static const char* help[] = {
      "b: Test bool flag. [true]", "c: Test char flag. [C]",
      "d: Test double flag. [123.456]", "f: Test float flag. [12.3]",
      "i: Test int flag. [123]", "size: Test size flag. [1234]",
      "str: Test string flag. [abcdef]", "help: Show help information. [false]",
      "backtrace_buffer_size: The buffer size for backtrace. [100]",
      "v: Log level. [3]",
  };
  std::unordered_set<std::string> help_set;
  for (size_t i = 0; i < ARRAY_SIZE(help); ++i) {
    help_set.insert(help[i]);
  }
  CHECK_EQ(help_set.size(), AbstractCommandlineFlag::mutable_flags()->size());
  for (const AbstractCommandlineFlag* flag :
       *AbstractCommandlineFlag::mutable_flags()) {
    CHECK_THAT(*flag, [&help_set](const AbstractCommandlineFlag& flag) {
      return help_set.find(ToString(flag)) != help_set.end();
    });
  }
}

void Test() {
  TestDefault();
  TestHelp();
}

}  // namespace
}  // namespace util

int main(int argc, char** argv) {
  ::util::Init(argv[0], argc, argv);
  ::util::Test();
  LOG(INFO) << "PASS";
  return 0;
}
