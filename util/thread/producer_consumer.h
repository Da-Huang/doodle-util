#ifndef UTIL_THREAD_PRODUCER_CONSUMER_H_
#define UTIL_THREAD_PRODUCER_CONSUMER_H_

#include <thread>
#include <vector>

#include "util/thread/blocking_queue.h"

namespace util {

// This class specifies producer-consumer model.
template <typename ResourceType>
class ProducerConsumer final {
 public:
  explicit ProducerConsumer(size_t queue_size) : queue_(queue_size) {}
  ProducerConsumer(const ProducerConsumer& pc) = delete;

  // Destructor which will automatically join all workers.
  ~ProducerConsumer();

  // Adds producer who produces resource to a blocking queue.
  //
  // `produce` looks like: void produce(BlockingQueue<ResourceType>*);
  template <typename Function>
  void AddProducer(Function&& produce);

  // Adds consumer who repeatedly consumes resource from blocking queue until
  // the queue is stopped.
  //
  // `consume` looks like: void consume(const ResourceType&));
  template <typename Function>
  void AddConsumer(Function&& consume);

  // Joins all workers.
  void Join();

 private:
  // Blocking resource queue.
  BlockingQueue<ResourceType> queue_;
  std::vector<std::thread*> producers_, consumers_;  // ELEMENTS OWNED
};

}  // namespace util

#include "producer_consumer.incl.h"

#endif  // UTIL_THREAD_PRODUCER_CONSUMER_H_
