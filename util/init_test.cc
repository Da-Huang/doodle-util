#include "init.h"

#include <string>
#include <unordered_set>

#include "check.h"
#include "commandline_flag.h"
#include "logging.h"
#include "macro.h"
#include "string/string.h"

DEFINE_bool(b, true, "Test bool flag.");

DEFINE_char(c, 'C', "Test char flag.");

DEFINE_double(d, 123.456, "Test double flag.");

DEFINE_float(f, 12.3f, "Test float flag.");

DEFINE_int(i, 123, "Test int flag.");

DEFINE_size(size, 1234, "Test size flag.");

DEFINE_string(str, "abcdef", "Test string flag.");

DECLARE_int(backtrace_buffer_size);

namespace util {
namespace {

void TestInitCase(int argc, const char* argv[], const char* help[],
                  int help_size) {
  char** dynamic_argv = new char* [argc];
  for (int i = 0; i < argc; ++i) {
    dynamic_argv[i] = new char[Strlen(argv[i]) + 1];
    Strcpy(dynamic_argv[i], argv[i]);
  }
  Init(argv[0], argc, dynamic_argv);
  for (int i = 0; i < argc; ++i) {
    delete[] dynamic_argv[i];
  }
  delete[] dynamic_argv;

  std::unordered_set<std::string> help_set;
  for (int i = 0; i < help_size; ++i) {
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
  static const char* argv1[] = {
      "test", "--i=10", "--c=K", "--d=5.67", "--backtrace_buffer_size=50",
      "--f", "3.4", "--b", "false", "--str=a b c",
  };
  static const char* help1[] = {
      "b: Test bool flag. [false]", "c: Test char flag. [K]",
      "d: Test double flag. [5.67]", "f: Test float flag. [3.4]",
      "i: Test int flag. [10]", "size: Test size flag. [1234]",
      "str: Test string flag. [a b c]", "help: Show help information. [false]",
      "backtrace_buffer_size: The buffer size for backtrace. [50]",
      "v: Log level. [3]",
  };
  TestInitCase(ARRAY_SIZE(argv1), argv1, help1, ARRAY_SIZE(help1));

  static const char* argv2[] = {
      "test", "--size=11", "--c", "P", "--d", "1.67", "--backtrace_buffer_size",
      "20", "--f=5.4", "--b", "--str= a b c",
  };
  static const char* help2[] = {
      "b: Test bool flag. [true]", "c: Test char flag. [P]",
      "d: Test double flag. [1.67]", "f: Test float flag. [5.4]",
      "i: Test int flag. [10]", "size: Test size flag. [11]",
      "str: Test string flag. [ a b c]", "help: Show help information. [false]",
      "backtrace_buffer_size: The buffer size for backtrace. [20]",
      "v: Log level. [3]",
  };
  TestInitCase(ARRAY_SIZE(argv2), argv2, help2, ARRAY_SIZE(help2));
}

}  // namespace
}  // namespace util

int main(int argc, char** argv) {
  ::util::Init(argv[0], argc, argv);
  ::util::Test();
  LOG(INFO) << "PASS";
  return 0;
}
