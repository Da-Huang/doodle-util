#include "string.h"

#include <string>
#include <vector>

#include "check.h"
#include "init.h"
#include "logging.h"

namespace util {
namespace {

void TestBasicToString() {
  CHECK_EQ("true", ToString(true));
  CHECK_EQ("C", ToString('C'));
  CHECK_EQ("123.456", ToString(double(123.456)));
  CHECK_EQ("12.3", ToString(float(12.3)));
  CHECK_EQ("123", ToString(int(123)));
  CHECK_EQ("1234", ToString(size_t(1234)));
  CHECK_EQ("abcdef", ToString(std::string("abcdef")));
  CHECK_EQ("abcdef", ToString("abcdef"));
}

void TestBasicFromString() {
  bool b;
  FromString("true", &b);
  CHECK_EQ(true, b);
  char c;
  FromString("C", &c);
  CHECK_EQ('C', c);
  double d;
  FromString("123.456", &d);
  CHECK_EQ(123.456, d);
  float f;
  FromString("12.3", &f);
  CHECK_EQ(12.3f, f);
  int i;
  FromString("123", &i);
  CHECK_EQ(123, i);
  size_t size;
  FromString("1234", &size);
  CHECK_EQ(1234, size);
  std::string str;
  FromString("abcdef", &str);
  CHECK_EQ("abcdef", str);
}

void TestVectorString() {
  CHECK_EQ("[]", ToString(std::vector<int>{}));
  CHECK_EQ("[1, 2, 3]", ToString(std::vector<size_t>{1, 2, 3}));
  CHECK_EQ("[abc, ef, , ghij]",
           ToString(std::vector<std::string>{"abc", "ef", "", "ghij"}));
  CHECK_EQ("[[abc, ef], [], [ghij]]",
           ToString(std::vector<std::vector<std::string>>{
               {"abc", "ef"}, {}, {"ghij"}}));
}

void Test() {
  TestBasicToString();
  TestBasicFromString();

  TestVectorString();
}

}  // namespace
}  // namespace util

int main(int argc, char** argv) {
  ::util::Init(argv[0], argc, argv);
  ::util::Test();
  LOG(INFO) << "PASS";
  return 0;
}
