#include "rotate_output_stream.h"

#include <ostream>
#include <sstream>

#include "util/check.h"
#include "util/init.h"
#include "util/logging.h"

namespace util {
namespace {

void Test() {
  std::ostringstream oss;
  ((RotateOutputStream&)(RotateOutputStream(&oss) << "AB")).OutputFront()
      << std::endl
      << 5;

  std::ostringstream expect;
  expect << std::endl << 5 << "AB";
  CHECK_EQ(expect.str(), oss.str());
}

}  // namespace
}  // namespace util

int main(int argc, char** argv) {
  ::util::Init(argv[0], argc, argv);
  ::util::Test();
  LOG(INFO) << "PASS";
  return 0;
}
