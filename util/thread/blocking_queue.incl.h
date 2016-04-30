#include "thread/blocking_queue.h"

#include <mutex>

#include "check.h"

namespace util {

template <typename Type>
void BlockingQueue<Type>::Push(const Type& item) {
  CHECK(!stop_) << "Unable to push item to stopped queue.";
  std::unique_lock<std::mutex> lock(mutex_);
  push_cv_.wait(lock, [this] { return queue_.size() < max_size_; });
  queue_.push(item);
  lock.unlock();
  pop_cv_.notify_one();
}

template <typename Type>
bool BlockingQueue<Type>::Pop(Type* item) {
  std::unique_lock<std::mutex> lock(mutex_);
  pop_cv_.wait(lock, [this] { return stop_ || !queue_.empty(); });
  if (queue_.empty()) {
    return false;
  }
  *item = queue_.front();
  queue_.pop();
  lock.unlock();
  push_cv_.notify_one();
  return true;
}

template <typename Type>
void BlockingQueue<Type>::Stop() {
  std::unique_lock<std::mutex> lock(mutex_);
  stop_ = true;
  lock.unlock();
  pop_cv_.notify_all();
}

}  // namespace util
