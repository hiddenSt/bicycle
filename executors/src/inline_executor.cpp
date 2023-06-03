#include <bicycle/executors/inline_executor.hpp>

namespace bicycle::executors {

void InlineExecutor::Submit(TaskBase* task) { task->Run(); }

}  // namespace bicycle::executors