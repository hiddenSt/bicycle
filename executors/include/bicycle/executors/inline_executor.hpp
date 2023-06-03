#pragma once

#include <bicycle/executors/export.h>
#include <bicycle/executors/executor.hpp>
#include <bicycle/executors/task.hpp>

namespace bicycle::executors {

class BICYCLE_EXPORT InlineExecutor : public Executor {
 public:
  void Submit(TaskBase* task) override;
};

}  // namespace bicycle::executors