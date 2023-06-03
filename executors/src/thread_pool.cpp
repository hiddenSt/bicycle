#include <bicycle/executors/thread_pool.hpp>

#include <bicycle/core/contracts.hpp>

namespace bicycle::executors {

ThreadPool::ThreadPool(std::size_t worker_count) {
  workers_.reserve(worker_count);

  for (std::size_t i = 0; i < worker_count; ++i) {
    workers_.emplace_back([this]() mutable { WorkerRoutine(); });
  }
}

ThreadPool::~ThreadPool() { StopImpl(); }

void ThreadPool::Submit(TaskBase* task) { task_queue_.Put(task); }

void ThreadPool::Stop() { StopImpl(); }

void ThreadPool::WaitIdle() {}

void ThreadPool::WorkerRoutine() {
  while (true) {
    auto task = task_queue_.Take();

    if (task == nullptr) {
      break;
    }

    task->Run();
  }
}

void ThreadPool::StopImpl() {
  task_queue_.Close();
  for (auto& worker : workers_) {
    worker.join();
  }
}

ThreadPool* ThreadPool::Current() { return nullptr; }

}  // namespace bicycle::executors