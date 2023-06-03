#pragma once

#include <condition_variable>
#include <mutex>
#include <optional>

#include <bicycle/container/intrusive_linked_list.hpp>

namespace bicycle::executors::detail {

template <typename T>
class MPMCUnboundedQueue {
 public:
  bool Put(T* item) {
    {
      std::lock_guard lock(mutex_);

      if (closed_) {
        return false;
      }

      queue_.PushBack(item);
    }

    is_not_empty_.notify_all();

    return true;
  }

  T* Take() {
    std::unique_lock lock{mutex_};

    while (queue_.IsEmpty() && !closed_) {
      is_not_empty_.wait(lock);
    }

    T* item = nullptr;

    if (closed_) {
      return item;
    }

    item = queue_.Front();
    queue_.PopFront();

    return item;
  }

  void Close() {
    std::lock_guard lock{mutex_};
    closed_ = true;
  }

  void Cancel() {
    std::lock_guard lock{mutex_};
    closed_ = true;

    while (!queue_.Empty()) {
      queue_.PopBack();
    }
  }

 private:
  container::intrusive::LinkedList<T> queue_;
  std::mutex mutex_;
  std::condition_variable is_not_empty_;
  bool closed_{false};
};

}  // namespace bicycle::executors::detail