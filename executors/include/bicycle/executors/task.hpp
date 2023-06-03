#pragma once

#include <bicycle/container/intrusive_linked_list.hpp>

#include <bicycle/executors/export.h>

namespace bicycle::executors {

class BICYCLE_EXPORT Task {
 public:
  virtual void Run() noexcept = 0;
};

struct BICYCLE_EXPORT TaskBase : public Task, public container::intrusive::ListNode<TaskBase> {};

}  // namespace bicycle::executors
