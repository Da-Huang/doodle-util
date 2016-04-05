#include "io.h"

#include <sstream>
#include <string>
#include <vector>

#include "logging.h"

namespace util {
namespace {

void TestUsualIO() {
  std::ostringstream oss;

  // Writes basic data.
  int i = 123;
  Write(&oss, i);
  float f = 123.45;
  Write(&oss, f);
  double d = 123.45;
  Write(&oss, d);
  size_t size = 789;
  Write(&oss, size);
  bool b = true;
  Write(&oss, b);
  char c = ';';
  Write(&oss, c);

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
  int i2;
  Read(&iss, &i2);
  CHECK_EQ(i, i2) << "i2 mismatched.";
  float f2;
  Read(&iss, &f2);
  CHECK_EQ(f, f2) << "f2 mismatched.";
  double d2;
  Read(&iss, &d2);
  CHECK_EQ(d, d2) << "d2 mismatched.";
  size_t size2;
  Read(&iss, &size2);
  CHECK_EQ(size, size2) << "size2 mismatched.";
  bool b2;
  Read(&iss, &b2);
  CHECK_EQ(b, b2) << "b2 mismatched.";
  char c2;
  Read(&iss, &c2);
  CHECK_EQ(c, c2) << "c2 mismatched.";

  // Compares between string.
  std::string str2;
  Read(&iss, &str2);
  CHECK_EQ(str, str2) << "str2 mismatched.";

  // Compares between vector.
  std::vector<int> vi2;
  Read(&iss, &vi2);
  CHECK_EQ(vi.size(), vi2.size()) << "Size of vi2 mismatched.";
  for (size_t i = 0; i < vi.size(); ++i) {
    CHECK_EQ(vi[i], vi2[i]) << "vi2[" << i << "] mismatched.";
  }
  std::vector<bool> vb2;
  Read(&iss, &vb2);
  CHECK_EQ(vb.size(), vb2.size()) << "Size of vb2 mismatched.";
  for (size_t i = 0; i < vb.size(); ++i) {
    bool vbi = vb[i];
    bool vb2i = vb2[i];
    CHECK_EQ(vbi, vb2i) << "vb2[" << i << "] mismatched.";
  }
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
  std::vector<std::vector<std::string>> vvstr2;
  Read(&iss, &vvstr2);
  std::vector<std::vector<bool>> vvb2;
  Read(&iss, &vvb2);

  // TODO: Apply new logging system test.
}

void TestIO() {
  TestUsualIO();
  TestComplexVectorIO();
}

}  // namespace
}  // namespace util

int main(int argc, char** argv) {
  ::util::TestIO();
  LOG(INFO) << "PASS";
  return 0;
}
