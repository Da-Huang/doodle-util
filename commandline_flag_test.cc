#include "commandline_flag.h"

#include "check.h"
#include "init.h"
#include "logging.h"

DEFINE_bool(b, true, "Test bool flag.");

DEFINE_char(c, 'C', "Test char flag.");

DEFINE_double(d, 123.456, "Test double flag.");

DEFINE_float(f, 12.3f, "Test float flag.");

DEFINE_int(i, 123, "Test int flag.");

DEFINE_size(size, 1234, "Test size flag.");

DEFINE_string(str, "abcdef", "Test string flag.");

DECLARE_int(backtrace_buffer_size);

DECLARE_int(v);

namespace util {

void Test() {
  CHECK_EQ(true, FLAG_b);
  CHECK_EQ('C', FLAG_c);
  CHECK_EQ(123.456, FLAG_d);
  CHECK_EQ(12.3f, FLAG_f);
  CHECK_EQ(123, FLAG_i);
  CHECK_EQ(1234, FLAG_size);
  CHECK_EQ("abcdef", FLAG_str);

  CHECK_EQ(100, FLAG_backtrace_buffer_size);
  CHECK_EQ(int(Logger::Level::INFO), FLAG_v);
}

}  // namespace util

int main(int argc, char** argv) {
  ::util::Init(argv[0], argc, argv);
  ::util::Test();
  LOG(INFO) << "PASS";
  return 0;
}
