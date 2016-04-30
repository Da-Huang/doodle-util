#include "blocking_queue.h"

#include <thread>
#include <vector>

#include "util/check.h"
#include "util/init.h"
#include "util/logging.h"

namespace util {
namespace {

void TestCase(const std::vector<int>& v) {
  BlockingQueue<int> queue(3);

  // Sets up consumers.
  std::thread consumer([&queue, &v] {
    int i = 0;
    int item;
    while (queue.Pop(&item)) {
      CHECK_EQ(v[i], item);
      ++i;
    }
  });

  // Sets up producer.
  std::thread producer([&queue, &v] {
    for (int item : v) {
      queue.Push(item);
    }
    queue.Stop();
  });

  consumer.join();
  producer.join();

  CHECK_EQ(0, queue.size());
  int i;
  CHECK_EQ(false, queue.Pop(&i));
}

void Test() { TestCase({4, 3, 5, 9, 6, 2, 3, 4, 1, 2}); }

}  // namespace
}  // namespace util

int main(int argc, char** argv) {
  ::util::Init(argv[0], argc, argv);
  ::util::Test();
  LOG(INFO) << "PASS";
  return 0;
}
