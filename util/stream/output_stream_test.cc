#include "output_stream.h"

#include <ostream>
#include <sstream>

#include "util/check.h"
#include "util/init.h"
#include "util/logging.h"

namespace util {
namespace {

class FakeOutputStream : public OutputStream {
 public:
  explicit FakeOutputStream(std::ostream* out) : out_(out) {}

 protected:
  std::ostream* GetOutputStream() override { return out_; }

 private:
  std::ostream* out_;
};

void Test() {
  std::ostringstream oss;
  FakeOutputStream fos(&oss);
  fos << "Abc" << '?' << std::endl
      << 4;

  std::ostringstream expect;
  expect << "Abc" << '?' << std::endl
         << 4;
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
