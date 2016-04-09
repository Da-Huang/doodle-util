#include "producer_consumer.h"

#include <atomic>
#include <vector>

#include "check.h"
#include "init.h"
#include "logging.h"
#include "thread/blocking_queue.h"

namespace util {
namespace {

void TestCase(const std::vector<int>& v) {
  ProducerConsumer<int> pc(3);

  // Adds consumers.
  std::atomic_int actual_sum(0);
  auto consume = [&actual_sum](const int& i) {
    actual_sum.fetch_add(i, std::memory_order_relaxed);
  };
  pc.AddConsumer(consume);
  pc.AddConsumer(consume);
  pc.AddConsumer(consume);

  // Adds producer.
  int expect_sum = 0;
  pc.AddProducer([&v, &expect_sum](BlockingQueue<int>* queue) {
    for (size_t i = 0; i < v.size(); ++i) {
      expect_sum += v[i];
      queue->Push(v[i]);
    }
    queue->Stop();
  });

  pc.Join();
  CHECK_EQ(expect_sum, actual_sum.load());
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
