#include <bicycle/executors/manual_executor.hpp>

namespace bicycle::executors {

void ManualExecutor::Submit(TaskBase* task) { task_queue_.PushBack(task); }

bool ManualExecutor::RunNext() { return RunAtMost(1) == 1; }

std::size_t ManualExecutor::RunAtMost(std::size_t limit) {
  std::size_t task_executed = 0;

  while (limit > 0 && HasTasks()) {
    auto task = task_queue_.Front();
    task_queue_.PopFront();
    task->Run();
    ++task_executed;
  }

  return task_executed;
}

std::size_t ManualExecutor::Drain() { return RunAtMost(TaskCount()); }

std::size_t ManualExecutor::TaskCount() const { return task_queue_.Size(); }

bool ManualExecutor::HasTasks() const { return TaskCount() != 0; }

}  // namespace bicycle::executors