#pragma once

#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
#include <vector>

#include <bicycle/executors/export.h>
#include <bicycle/executors/detail/mpmc_blocking_queue.hpp>
#include <bicycle/executors/executor.hpp>
#include <bicycle/executors/task.hpp>

namespace bicycle::executors {

/// \brief Thread pool executor.
/// Starts a fixed number of threads, which executes user-provided tasks.
class BICYCLE_EXPORT ThreadPool : public Executor {
 public:
  explicit ThreadPool(std::size_t worker_count = std::thread::hardware_concurrency());
  ~ThreadPool();

  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;

  ThreadPool(ThreadPool&&) = delete;
  ThreadPool& operator=(ThreadPool&&) = delete;

  void Submit(TaskBase* task) override;
  void Stop();
  void WaitIdle();

  static ThreadPool* Current();

 private:
  void WorkerRoutine();
  void StopImpl();

 private:
  std::vector<std::thread> workers_;
  detail::MPMCUnboundedQueue<TaskBase> task_queue_;
};

}  // namespace bicycle::executors