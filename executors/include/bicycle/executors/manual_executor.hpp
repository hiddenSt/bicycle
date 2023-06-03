#pragma once

#include <cstdint>
#include <queue>

#include <bicycle/container/intrusive_linked_list.hpp>

#include <bicycle/executors/export.h>
#include <bicycle/executors/executor.hpp>
#include <bicycle/executors/task.hpp>

namespace bicycle::executors {

class BICYCLE_EXPORT ManualExecutor : public Executor {
 public:
  void Submit(TaskBase* task) override;

  bool RunNext();
  std::size_t RunAtMost(std::size_t limit);
  std::size_t Drain();
  std::size_t TaskCount() const;
  bool HasTasks() const;

 private:
  container::intrusive::LinkedList<TaskBase> task_queue_;
};

}  // namespace bicycle::executors