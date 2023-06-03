#pragma once

#include <mutex>
#include <queue>

#include <bicycle/container/intrusive_linked_list.hpp>

#include <bicycle/executors/export.h>
#include <bicycle/executors/executor.hpp>
#include <bicycle/executors/task.hpp>

namespace bicycle::executors {

/// Asynchronous mutex.
class BICYCLE_EXPORT Strand : public Executor {
 public:
  /// \param underlying The executor which is wrapped by strand.
  explicit Strand(Executor& underlying);

  /// Submits \a task to strand for sequential execution.
  void Submit(TaskBase* task) override;

 private:
  Executor& underlying_;
  container::intrusive::LinkedList<TaskBase> queue_;
};

}  // namespace bicycle::executors