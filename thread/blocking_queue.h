#ifndef UTIL_THREAD_BLOCKING_QUEUE_H_
#define UTIL_THREAD_BLOCKING_QUEUE_H_

#include <condition_variable>
#include <mutex>
#include <queue>

namespace util {

// A thread-safe blocking queue.
template <typename Type>
class BlockingQueue final {
 public:
  explicit BlockingQueue(size_t max_size) : max_size_(max_size) {}
  BlockingQueue(const BlockingQueue& queue) = delete;
  virtual ~BlockingQueue() = default;

  // Pushes an item to this queue.
  //
  // If this queue is full, the caller will be blocked until any item is popped.
  // If this queue has been stopped, it crashes.
  void Push(const Type& item);

  // Pops an item from this queue.
  //
  // Returns false, if no more item should be expected.
  //
  // If this queue is empty but not stopped, the caller will be blocked until
  // any item is pushed or it is stopped.
  bool Pop(Type* item);

  // Stops pushing items into this queue.
  void Stop();

  size_t size() const { return queue_.size(); }

 private:
  std::queue<Type> queue_;
  // Maximum size of queue.
  size_t max_size_;

  // Flag to stop pushing.
  bool stop_ = false;

  // Condition variable for pusher to wait for not being full.
  std::condition_variable push_cv_;
  // Condition variable for popper to wait for being stopped or nonempty.
  std::condition_variable pop_cv_;

  // Mutex to lock any manipulation on this queue.
  std::mutex mutex_;
};

}  // namespace util

#include "blocking_queue.incl.h"

#endif  // UTIL_THREAD_BLOCKING_QUEUE_H_
