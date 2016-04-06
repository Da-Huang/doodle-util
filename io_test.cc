#include "io.h"

#include <sstream>
#include <string>
#include <vector>

#include "check.h"
#include "init.h"
#include "logging.h"

namespace util {
namespace {

void TestUsualIO() {
  std::ostringstream oss;

  // Writes basic data.
  bool b = true;
  Write(&oss, b);
  char c = ';';
  Write(&oss, c);
  double d = 123.45;
  Write(&oss, d);
  float f = 123.45f;
  Write(&oss, f);
  int i = 123;
  Write(&oss, i);
  size_t size = 6789;
  Write(&oss, size);

  // Writes string.
  std::string str = "abcd\nefg";
  Write(&oss, str);

  // Writes vector.
  std::vector<int> vi = {7, 6, 5, 4};
  Write(&oss, vi);
  std::vector<bool> vb = {true, false, true, true, false};
  Write(&oss, vb);

  // Creates input stream from output stream.
  std::istringstream iss(oss.str());

  // Compares between basic data.
  bool b2;
  Read(&iss, &b2);
  CHECK_EQ(b, b2);
  char c2;
  Read(&iss, &c2);
  CHECK_EQ(c, c2);
  double d2;
  Read(&iss, &d2);
  CHECK_EQ(d, d2);
  float f2;
  Read(&iss, &f2);
  CHECK_EQ(f, f2);
  int i2;
  Read(&iss, &i2);
  CHECK_EQ(i, i2);
  size_t size2;
  Read(&iss, &size2);
  CHECK_EQ(size, size2);

  // Compares between string.
  std::string str2;
  Read(&iss, &str2);
  CHECK_EQ(str, str2);

  // Compares between vector.
  std::vector<int> vi2;
  Read(&iss, &vi2);
  CHECK_EQ(vi, vi2);
  std::vector<bool> vb2;
  Read(&iss, &vb2);
  CHECK_EQ(vb, vb2);
}

void TestComplexVectorIO() {
  std::ostringstream oss;

  // Writes vector.
  std::vector<std::vector<double>> vvi = {
      {1.0, 2.0}, {}, {3.0, 4.0, 5.0},
  };
  Write(&oss, vvi);
  std::vector<std::vector<std::string>> vvstr = {
      {}, {"a", "b", "\n"}, {","}, {"c", "d"},
  };
  Write(&oss, vvstr);
  std::vector<std::vector<bool>> vvb = {
      {true, false, false}, {}, {false},
  };
  Write(&oss, vvb);

  // Creates input stream from output stream.
  std::istringstream iss(oss.str());

  // Compares between vector.
  std::vector<std::vector<double>> vvi2;
  Read(&iss, &vvi2);
  CHECK_EQ(vvi, vvi2);
  std::vector<std::vector<std::string>> vvstr2;
  Read(&iss, &vvstr2);
  CHECK_EQ(vvstr, vvstr2);
  std::vector<std::vector<bool>> vvb2;
  Read(&iss, &vvb2);
  CHECK_EQ(vvb, vvb2);
}

void Test() {
  TestUsualIO();
  TestComplexVectorIO();
}

}  // namespace
}  // namespace util

int main(int argc, char** argv) {
  ::util::Init(argv[0], argc, argv);
  ::util::Test();
  LOG(INFO) << "PASS";
  return 0;
}
