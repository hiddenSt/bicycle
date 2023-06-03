#pragma once

#include <bicycle/executors/export.h>
#include <bicycle/executors/task.hpp>

namespace bicycle::executors {

/// Abstracts underlying resources, where work physically executes.
class BICYCLE_EXPORT Executor {
 public:
  /// Submits \a task for execution in a "fire and forget"-style.
  virtual void Submit(TaskBase* task) = 0;

  /// Virtual destructor, must be overriden in subclasses.
  virtual ~Executor() = default;
};

}  // namespace bicycle::executors